import matplotlib.pyplot as plt

# Number of threads
threads = [1, 2, 4, 8, 16, 32, 64, 128, 256]

# Integer data
average_times_int = [
    0.065246,  # 1 thread
    0.032054,  # 2 threads
    0.016074,  # 4 threads
    0.008104,  # 8 threads
    0.004073,  # 16 threads
    0.003139,  # 32 threads
    0.003883,  # 64 threads
    0.005740,  # 128 threads
    0.008043   # 256 threads
]

# Double data
average_times_double = [
    0.103141,  # 1 thread
    0.051322,  # 2 threads
    0.025561,  # 4 threads
    0.012862,  # 8 threads
    0.006514,  # 16 threads
    0.003903,  # 32 threads
    0.007697,  # 64 threads
    0.008726,  # 128 threads
    0.009743   # 256 threads
]

threads_new = threads[:len(average_times_int)]

# Draw Figure
plt.figure(figsize=(10, 6))


# plot Integer data
plt.plot(threads, average_times_int, marker='o', linestyle='-', color='blue', label='Integer Data')

# plot Double data
plt.plot(threads_new, average_times_double, marker='s', linestyle='-', color='red', label='Double Data')

plt.xlabel("Number of Threads")
plt.ylabel("Average Time (seconds)")
plt.title("Thread Scaling Performance Comparison")

plt.grid(True)
plt.xscale('log', base=2)
plt.xticks(threads, threads)
plt.legend()

# 原点を左下に固定
plt.xlim(left=0)
plt.ylim(bottom=0)

plt.tight_layout()
plt.show()
