#include "snoop.h"

Snoop::Run() {
	while (true) {
		if (!bus.empty()) {
			if (bus.front().wait_cycles != 0) {
				bus.front().wait_cycles--;
			} else if (bus.front().op == WRITEBACK) {
				
			} else if (bus.front().op == RESPONSE) {

			} else {
				bool served = false;
				for (int i = 0; i < NUM_PROCESSORS; ++i)
				{
					if ()
				}
			}
		}
	}
}