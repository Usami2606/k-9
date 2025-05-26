import matplotlib.pyplot as plt

# Number of threads
datasize = [2**i for i in range(8, 20)]


# Integer data
samecpu = [ 0.000552, 0.000813, 0.001327, 0.001092, 0.002118,
    0.003391, 0.003446, 0.005595, 0.010123, 0.019726,
    0.037821, 0.074693
]

# Double data
samenode = [ 0.000550, 0.000790, 0.000985, 0.001101, 0.001401,
    0.002076, 0.003469, 0.005289, 0.010450, 0.019378,
    0.038240, 0.075952
]

othernode = [
    0.008535, 0.011059, 0.011320, 0.009270, 0.009005,
    0.004894, 0.006530, 0.014610, 0.019354, 0.028285,
    0.041540, 0.080168
]

threads_new = datasize[:len(samecpu)]
threads_new2 = datasize[:len(samecpu)]

# Draw Figure
plt.figure(figsize=(10, 6))


# plot Integer data
plt.plot(datasize, samecpu, marker='o', linestyle='-', color='blue', label='samecpu')

# plot Double data
plt.plot(threads_new, samenode, marker='s', linestyle='-', color='red', label='samenode')

plt.plot(threads_new2, othernode, marker='s', linestyle='-', color='green', label='othernode')

plt.xlabel("DataSize(double)")
plt.ylabel("Average Time (seconds)")
plt.title("Communication time comparison(p2p)")

plt.grid(True)
plt.xticks(datasize, datasize)
plt.legend()

#plt.xscale('log', base=2)
plt.xticks(datasize, [r'$2^{%d}$' % i for i in range(8, 20)])
# 原点を左下に固定
plt.xlim(left=0)
plt.ylim(bottom=0)

plt.tight_layout()
plt.show()


