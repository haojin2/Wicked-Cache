#include "snoop.h"

Snoop::Run() {
	if (!bus.empty()) {
		if (bus.front().wait_cycles != 0) {
			bus.front().wait_cycles--;
		} else {
			bool served = false;
			for (int i = 0; i < NUM_PROCESSORS; ++i)
			{
				if ()
			}
		}
	}
}