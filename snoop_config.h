// cache coherence protocol
#include "msi.h"
#include "cache.h"

#define CACHE_SIZE 64
#define CACHE_NUM_WAYS 2
#define CACHE_BLOCK_SIZE 16

// system specifications
#define NUM_PROCESSORS 4

// bus & memory delays
#define BUS_REQUEST_DELAY 5
#define BUS_RESPONSE_DELAY 5
#define BUS_WRITEBACK_DELAY 10
#define MEM_DELAY 20

typedef msi PROTOCOL_TYPE;

// cache specifications
typedef LRU CACHE_TYPE;
