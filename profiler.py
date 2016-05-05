import numpy as np
import matplotlib.pyplot as plt
import sys
if __name__ == '__main__':
	num_of_processors = int(sys.argv[1])
	processors = ['g' for i in range(num_of_processors)]
	plt.figure()
	with open('run_log','r') as log_file:
		count = 0
		time = []
		for lines in log_file:
			entries = lines.split(':')
			# print entries
			prev_count = count
			for j in range(count, int(entries[0])):
				# time.append(count)
				count += 1
				# for i in range(num_of_processors):
				# 	# pe[i].append(processors[i])
			for i in range(num_of_processors):
				plt.plot([prev_count,count], [i + 1, i + 1], c = processors[i], linewidth = 10)
			if len(entries[1]) != 1:
				info = entries[1].rstrip('\n').split(' ')
				if info[2][0] == 's':
					processors[int(info[1])] = 'g'
				if info[2][0] == 'b':
					processors[int(info[1])] = 'r'
				if info[2][0] == 'f':
					processors[int(info[1])] = 'w'
	plt.ylim([0,5])
	plt.xlabel('cycles')
	plt.ylabel('processor ID')
	plt.title('visualized processor utilization')
	plt.savefig('aa.png')
	print "miss rate: 100 %"
	print "read miss rate: 100 %"
	print "write miss rate: 100 %"
					