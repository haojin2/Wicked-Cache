# for (int i = 0; i < N; ++i)
# 	for (int j = 0; j < N; ++j)
# 		for (int k = 0; k < N; ++k)
# 			c[i][j] += a[i][k] * b[k][j];

import sys

row = int(sys.argv[1])
col = int(sys.argv[2])

N = 128
data_size = 8
addrA = 0x1000000000000000
addrB = 0x2000000000677a38
addrC = 0x300000000019f72c

for i in range(row * N/2, row * N/2 + N/2):
	for j in range(col * N/2, col * N/2 + N/2):
		for k in range(N):
			print "10 1 %x" %(addrA + data_size * (i * N + k))
			print "5 1 %x" %(addrB + data_size * (j * N + k))
			print "8 1 %x" %(addrC + data_size * (i * N + j))
			print "20 2 %x" %(addrC + data_size * (i * N + j))