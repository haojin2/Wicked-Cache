// cache coherence protocol
#include "msi.h"
typedef msi PROTOCOL_TYPE

// cache specifications
typedef LRU CACHE_TYPE
#define CACHE_SIZE 64
#define CACHE_NUM_WAYS 2
#define CACHE_BLOCK_SIZE 16

// system specifications
#define NUM_PROCESSORS 4

// bus specifications
#define BUS_DELAY 5
#define MEM_DELAY 20
