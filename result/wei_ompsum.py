import matplotlib.pyplot as plt

threads = [1, 2, 4, 8, 16, 32, 64, 128, 256]
average_times = [
    0.309785,  # 1 thread
    0.154567,  # 2 threads
    0.077641,  # 4 threads
    0.039162,  # 8 threads
    0.019901,  # 16 threads
    0.011318,  # 32 threads
    0.012803,  # 64 threads
    0.015289,  # 128 threads
    0.014042   # 256 threads
]

plt.figure(figsize=(10, 6))
plt.plot(threads, average_times, marker='o', linestyle='-', color='blue')

plt.xlabel("Number of Threads")
plt.ylabel("Average Time (seconds)")
plt.title("Thread Scaling Performance(wei_ompsum.c)")

plt.grid(True)
plt.xscale('log', base=2)  # 対数スケール
plt.xticks(threads, threads, rotation=0)  # 目盛りそのまま表示
plt.tight_layout()

plt.xlim(left=0)
plt.ylim(bottom=0)

plt.show()
