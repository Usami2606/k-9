import matplotlib.pyplot as plt

threads = [1, 2, 4, 8, 16, 32, 64, 128, 256]
average_times = [
    0.500329,  # 1 thread
    0.251863,  # 2 threads
    0.126366,  # 4 threads
    0.064117,  # 8 threads
    0.032827,  # 16 threads
    0.029930,  # 32 threads
    0.024809,  # 64 threads
    0.025234,  # 128 threads
    0.022579   # 256 threads
]

plt.figure(figsize=(10, 6))
plt.plot(threads, average_times, marker='o', linestyle='-', color='blue')

plt.xlabel("Number of Threads")
plt.ylabel("Average Time (seconds)")
plt.title("Thread Scaling Performance(mat_ompsum.c)")

plt.grid(True)
plt.xscale('log', base=2)  # 対数スケール
plt.xticks(threads, threads, rotation=0)  # 目盛りそのまま表示
plt.tight_layout()

plt.xlim(left=0)
plt.ylim(bottom=0)

plt.show()
