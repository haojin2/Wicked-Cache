// cache coherence protocol
#include "msi.h"
typedef msi PROTOCOL_TYPE;

// cache specifications
typedef LRU CACHE_TYPE;
#define CACHE_SIZE 32
#define CACHE_NUM_WAYS 4
#define CACHE_BLOCK_SIZE 32

// system specifications
#define NUM_PROCESSORS 4

// bus & memory delays
#define BUS_REQUEST_DELAY 10
#define BUS_RESPONSE_DELAY 10
#define BUS_WRITEBACK_DELAY 50
#define MEM_DELAY 100
