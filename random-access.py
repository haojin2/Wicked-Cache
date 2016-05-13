# for (int i = 0; i < N; ++i)
# {
# 	read or write at [0x1000000000000000, 0x1000000000100000)
# }


import random
import time

N = 1000000
access_range = 1000000
read_ratio = 6 # over 10

random.seed(time.time())

for i in range(N):
	print "0 %d %x" %(random.randint(0,9) / 6 + 1, 0x1000000000000000 + random.randint(0, access_range-1))