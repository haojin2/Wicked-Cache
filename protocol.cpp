#include "protocol.h"

Protocol::Protocol() {
	cout<<"protocol"<<endl;
}

int Protocol::to_proc(int op, bool from_cache = true) {
	if (op == READ) {
		return cache ? PROC_READ_FROM_CACHE : PROC_READ_FROM_MEM;
	} else if (op == WRITE) {
		return PROC_WRITE;
	} else {
		return -1;
	}
}

int Protocol::to_bus(int op) {
	if (op == READ) {
		return BUS_READ;
	} else if (op == WRITE) {
		return BUS_WRITE;
	} else {
		return -1;
	}
}