// Add UPDATE busObj op type in the future
#include "snoop.h"

Snoop::BusObj::BusObj(int op, int wait_cycles, int src, int dest, long address,
					  bool exclusive_response = false) {
    this->op = op;
    this->wait_cycles = wait_cycles;
    this->src = src;
    this->dest = dest;
    this->address = address;
    this->exclusive_response = exclusive_response;
}

Snoop::Snoop(){
	cerr<<"Snoop constructor"<<endl;
	srand(time(0));
    ptc = new PROTOCOL_TYPE();
    for (int i = 0; i < NUM_PROCESSORS; ++i)
    {
        processor_ops.push_back(new MemOps("access_pattern_"+to_string((long long int)i)+".txt"));
        caches.push_back(new CACHE_TYPE(CACHE_SIZE, CACHE_NUM_WAYS, CACHE_BLOCK_SIZE));
        pending.push_back(false);
        random_selector.push_back(i);
    }
}

Snoop::~Snoop(){
    cerr<<"Snoop destructor"<<endl;
    delete ptc;
    for (int i = 0; i < NUM_PROCESSORS; ++i) {
        delete caches[i];
        delete processor_ops[i];
    }
}

void Snoop::Run() {
	unsigned long cycle = 0;
	int finished_processors = 0;
	while (finished_processors < NUM_PROCESSORS) {
		random_shuffle(random_selector.begin(), random_selector.end());
		
		if (!bus.empty()) {
			assert(bus.front().wait_cycles >= 0);
			if (bus.front().wait_cycles != 0) {
				bus.front().wait_cycles--;
			} else if (bus.front().op == WRITEBACK) {
				bus.pop();
			} else if (bus.front().op == RESPONSE) {
				BusObj & res = bus.front();
				MemOps * mem_op = processor_ops[res.dest];
				if (pending[res.dest] && mem_op->op == READ && mem_op->address == res.address) {
					resume(res.dest, res, res.exclusive_response);
					// LOG("cycle, res.dest read served by res.src")
					cout << "Cycle " << cycle << ": " << res.dest << " read miss serviced by " << res.src << endl;
				}
				bus.pop();
			} else {
				BusObj & req = bus.front();
				bool responded = false;
				bool exclusive = true;
				char state, new_state;
				queue< tuple<char, bool, bool> > bus_ops;
				for (int i, j = 0; j < NUM_PROCESSORS; ++j)
				{
					i = random_selector[j];
					if (i != req.src) {
						state = caches[i]->get_state((size_t)req.address);
						bus_ops.push(ptc->next_state(ptc->to_bus(req.op), state));
						new_state = get<0>(bus_ops.back());
						caches[i]->set_state((size_t)req.address, new_state);
						if (new_state != 'i')
							exclusive = false;
					}
				}
				for (int i, j = 0; j < NUM_PROCESSORS; ++j)
				{
					i = random_selector[j];
					if (i != req.src) {
						if (get<1>(bus_ops.front()))
							bus.push(BusObj(WRITEBACK, BUS_WRITEBACK_DELAY, i, -1, req.address));
						if (get<2>(bus_ops.front())) {
							responded = true;
							bus.push(BusObj(RESPONSE, BUS_RESPONSE_DELAY, i, req.src, req.address, exclusive));
						}
						bus_ops.pop();
					}
				}
				if (req.op == READ && !responded)
					bus.push(BusObj(RESPONSE, MEM_DELAY, MEM, req.src, req.address, exclusive));
				if (req.op == WRITE) {
					resume(req.src, req, exclusive);
					// LOG("cycle, req.src write returned")
					cout << "Cycle " << cycle << ": " << req.src << " write miss returned" << endl;
				}
				bus.pop();
			}
		}

		if (bus.empty() && !req_buffer.empty()) {
			int id = req_buffer.front();
			bus.push(BusObj(processor_ops[id]->op, BUS_REQUEST_DELAY, id, -1, processor_ops[id]->address));
			req_buffer.pop();
		}

		for (int i, j = 0; j < NUM_PROCESSORS; ++j)
		{
			i = random_selector[j];
			if (processor_ops[i]->wait_cycles == -1) {
				processor_ops[i]->wait_cycles = -2;
				// LOG("cycle, i finished")
				cout << "Cycle " << cycle << ": " << i << " finished" << endl;
				finished_processors++;
			} else if (pending[i] || processor_ops[i]->wait_cycles < 0) {
				continue;
			} else if (processor_ops[i]->wait_cycles > 0) {
				processor_ops[i]->wait_cycles--;
			} else {
				MemOps * mem_op = processor_ops[i];
				char state = caches[i]->get_state((size_t)mem_op->address);
				if (ptc->hit(mem_op->op, state)) {
					// LOG("cycle, i mem_op->op hit")
					// cout << "Cycle " << cycle << ": " << i << (mem_op->op==READ?" read":" write") << " hit" << endl;
					access_writeback_updatestate(i, mem_op->address, i);
					mem_op->get_next_op();
				} else {
					if (bus.empty())
						bus.push(BusObj(mem_op->op, BUS_REQUEST_DELAY, i, -1, mem_op->address));
					else
						req_buffer.push(i);
					pending[i] = true;
					// LOG("cycle, i blocked by mem_op->op miss")
					cout << "Cycle " << cycle << ": " << i << (mem_op->op==READ?" read":" write") << " miss" << endl;
				}
			}
		}

		cycle++;
	}
	// LOG("Total cycle")
	cout << "Finished. Total cycles elapsed: " << cycle << endl;
}

void Snoop::resume(int id, BusObj & bus_obj, bool exclusive) {
	if (processor_ops[id]->op == WRITE && !ptc->write_back_based_protocol) {
		bus.push(BusObj(WRITEBACK, BUS_WRITEBACK_DELAY, id, -1, bus_obj.address));
	} else {
		access_writeback_updatestate(id, bus_obj.address, bus_obj.src, exclusive);
	}
	pending[id] = false;
	processor_ops[id]->get_next_op();
}

void Snoop::access_writeback_updatestate(int id, long address, int src, bool exclusive) {
	pair<bool,char> result = caches[id]->access((size_t)address);
	if (!result.first && ptc->dirty(result.second)) {
		bus.push(BusObj(WRITEBACK, BUS_WRITEBACK_DELAY, id, -1, -1));
	}
	char state = result.first ? result.second : 'i';
	int op = ptc->to_proc(processor_ops[id]->op, src != MEM);
	caches[id]->set_state((size_t)address, get<0>(ptc->next_state(op, state, exclusive)));
}