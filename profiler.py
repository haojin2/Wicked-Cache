import numpy as np
import matplotlib.pyplot as plt
import sys
import os
if __name__ == '__main__':
	all_logs = os.listdir('%s/' % sys.argv[2])
	num_of_processors = int(sys.argv[1])
	processors = ['g' for i in range(num_of_processors)]
	proc_read_hit = [0 for i in range(num_of_processors)]
	proc_write_hit = [0 for i in range(num_of_processors)]
	proc_read_total = [0 for i in range(num_of_processors)]
	proc_write_total = [0 for i in range(num_of_processors)]
	proc_blocked_cycle = [0 for i in range(num_of_processors)]
	proc_last_blocked_cycle = [0 for i in range(num_of_processors)]
	for sin_log in all_logs:
		# plt.clf()
		num_of_processors = int(sys.argv[1])
		processors = ['g' for i in range(num_of_processors)]
		proc_read_hit = [0 for i in range(num_of_processors)]
		proc_write_hit = [0 for i in range(num_of_processors)]
		proc_read_total = [0 for i in range(num_of_processors)]
		proc_write_total = [0 for i in range(num_of_processors)]
		proc_blocked_cycle = [0 for i in range(num_of_processors)]
		with open('%s/%s' % (sys.argv[2], sin_log),'r') as log_file:
			count = 0
			time = []
			for lines in log_file:
				# print count
				entries = lines.split(':')
				# print entries
				prev_count = count
				# for j in range(count, int(entries[0].split(' ')[1])):
				# 	# time.append(count)
				# 	count += 1
				# 	# for i in range(num_of_processors):
				# 	# 	# pe[i].append(processors[i])
				# for i in range(num_of_processors):
				# 	plt.plot([count,int(entries[0].split(' ')[1]) - 1], [i + 1, i + 1], c = processors[i], linewidth = 10)
				count = int(entries[0].split(' ')[1])
				# print count
				if len(entries[1]) != 1:
					info = entries[1].rstrip('\n').split(' ')
					# print info
					CPUID = int(info[1])
					if len(info) > 4:
						if info[2] == 'read':
							processors[CPUID] = 'g'
						if info[2] == 'write':
							processors[CPUID] = 'g'
						proc_blocked_cycle[CPUID] += (count - proc_last_blocked_cycle[CPUID])
					else:
						if info[2] == 'read':
							proc_read_total[CPUID] += 1
							if info[3] == 'miss':
								processors[CPUID] = 'r'
								proc_last_blocked_cycle[CPUID] = count
							if info[3] == 'hit':
								proc_read_hit[CPUID] += 1
								processors[CPUID] = 'g'
						if info[2] == 'write':
							proc_write_total[CPUID] += 1
							if info[3] == 'miss':
								processors[CPUID] = 'm'
								proc_last_blocked_cycle[CPUID] = count
							if info[3] == 'hit':
								proc_write_hit[CPUID] += 1
								processors[CPUID] = 'g'
						if info[2] == 'finished':
							processors[CPUID] = 'w'
		# plt.ylim([0,5])
		# plt.xlabel('cycles')
		# plt.ylabel('processor ID')
		# plt.title('visualized processor utilization')
		# plt.savefig('%s.png' % sin_log)
		print sin_log
		print "hit rate:",((sum(proc_write_hit) + sum(proc_read_hit)) * 1. / (sum(proc_write_total) + sum(proc_read_total))) * 100,"%"
		print "read hit rate:",(sum(proc_read_hit) * 1. / sum(proc_read_total)) * 100,"%"
		print "write hit rate:",(sum(proc_write_hit) * 1. / sum(proc_write_total)) * 100,"%"
		print "read hit number:", sum(proc_read_hit) * 1.
		print "write hit number:", sum(proc_write_hit) * 1.
		print "read miss number:", sum(proc_read_total) - sum(proc_read_hit)
		print "write miss number:", sum(proc_write_total) - sum(proc_write_hit)
		print "total blocked cycle: ", sum(proc_blocked_cycle) / 4.
		print
						