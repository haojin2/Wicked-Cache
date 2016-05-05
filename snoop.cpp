#include "snoop.h"

void Snoop::Run() {
	unsigned long cycle = 0;
	int finished_processors = 0;
	while (finished_processors < NUM_PROCESSORS) {
		if (!bus.empty()) {
			assert(bus.front().wait_cycles >= 0);
			if (bus.front().wait_cycles != 0) {
				bus.front().wait_cycles--;
			} else if (bus.front().op == WRITEBACK) {
				bus.pop();
			} else if (bus.front().op == RESPONSE) {
				BusObj & res = bus.front();
				MemOps & mem_op = processor_ops[res.dest];
				if (pending[res.dest] && mem_op.op == READ && mem_op.address == res.address) {
					resume(res.dest, res);
					// LOG("cycle, res.dest read served by res.src")
				}
				bus.pop();
			} else {
				BusObj & req = bus.front();
				bool responded = false;
				bool exclusive = true;
				char state;
				tuple<char, bool, bool> new_state;
				for (int i = 0; i < NUM_PROCESSORS; ++i)
				{
					if (i != req.src) {
						state = caches[i]->get_state((size_t)req.address);
						new_state = ptc->next_state(ptc->to_bus(req.op), state);
						caches[i]->set_state((size_t)req.address, get<0>(new_state));
						if (get<0>(new_state) != 'i')
							exclusive = false;
						if (get<1>(new_state))
							bus.push(BusObj(WRITEBACK, BUS_WRITEBACK_DELAY, i, -1, req.address));
						if (get<2>(new_state)) {
							responded = true;
							bus.push(BusObj(RESPONSE, BUS_RESPONSE_DELAY, i, req.src, req.address));
						}
					}
				}
				if (req.op == READ && !responded)
					bus.push(BusObj(RESPONSE, MEM_DELAY, MEM, req.src, req.address));
				if (req.op == WRITE) {
					resume(req.src, req);
					// LOG("cycle, req.src write returned")
				}
				bus.pop();
			}
		}

		if (bus.empty() && !req_buffer.empty()) {
			int id = req_buffer.front();
			bus.push(BusObj(processor_ops[id].op, BUS_REQUEST_DELAY, id, -1, processor_ops[id].address));
			req_buffer.pop();
		}

		for (int i = 0; i < NUM_PROCESSORS; ++i)
		{
			if (processor_ops[i].wait_cycles == -1) {
				processor_ops[i].wait_cycles = -2;
				// LOG("cycle, i finished")
				finished_processors++;
			} else if (pending[i] || processor_ops[i].wait_cycles < 0) {
				continue;
			} else if (processor_ops[i].wait_cycles > 0) {
				processor_ops[i].wait_cycles--;
			} else {
				MemOps & mem_op = processor_ops[i];
				char state = caches[i]->get_state((size_t)mem_op.address);
				if (ptc->hit(mem_op.op, state)) {
					access_writeback_updatestate(i, mem_op.address, i);
				} else {
					if (bus.empty())
						bus.push(BusObj(mem_op.op, BUS_REQUEST_DELAY, i, -1, mem_op.address));
					else
						req_buffer.push(i);
					pending[i] = true;
					// LOG("cycle, i blocked by mem_op.op miss")
				}
			}
		}

		cycle++;
	}
	// LOG("Total cycle")
}

void Snoop::resume(int id, BusObj & bus_obj) {
	if (processor_ops[id].op == WRITE && !ptc->write_back_based_protocol) {
		bus.push(BusObj(WRITEBACK, BUS_WRITEBACK_DELAY, id, -1, bus_obj.address));
	} else {
		access_writeback_updatestate(id, bus_obj.address, bus_obj.src);
	}
	pending[id] = false;
	processor_ops[id].getNextOp();
}

void Snoop::access_writeback_updatestate(int id, long address, int src) {
	pair<bool,char> result = caches[id]->access((size_t)address);
	if (!result.first && ptc->dirty(result.second)) {
		bus.push(BusObj(WRITEBACK, BUS_WRITEBACK_DELAY, id, -1, -1));
	}
	char state = result.first ? result.second : 'i';
	int op = ptc->to_proc(processor_ops[id].op, src != MEM);
	caches[id]->set_state((size_t)address, get<0>(ptc->next_state(op, state)));
}