import pandas as pd
import matplotlib.pyplot as plt

# Load benchmark data
data = pd.read_csv("benchmark_results.csv")

# Graph 1: Performance vs Allocation Size
for iterations in data['Iterations'].unique():
    subset = data[data['Iterations'] == iterations]
    plt.figure()
    plt.plot(subset['Allocation Size'], subset['Default Time (s)'], label='Default malloc/free', marker='o')
    plt.plot(subset['Allocation Size'], subset['Custom Time (s)'], label='Custom mymalloc/myfree', marker='o')
    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Allocation Size (bytes)')
    plt.ylabel('Time (seconds)')
    plt.title(f'Performance vs Allocation Size (Iterations: {iterations})')
    plt.legend()
    plt.grid()
    plt.savefig(f"performance_vs_size_{iterations}.png")
    plt.show()

# Graph 2: Performance vs Number of Iterations
for size in data['Allocation Size'].unique():
    subset = data[data['Allocation Size'] == size]
    plt.figure()
    plt.plot(subset['Iterations'], subset['Default Time (s)'], label='Default malloc/free', marker='o')
    plt.plot(subset['Iterations'], subset['Custom Time (s)'], label='Custom mymalloc/myfree', marker='o')
    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Number of Iterations')
    plt.ylabel('Time (seconds)')
    plt.title(f'Performance vs Iterations (Allocation Size: {size} bytes)')
    plt.legend()
    plt.grid()
    plt.savefig(f"performance_vs_iterations_{size}.png")
    plt.show()

# Summary Graph: Highlighting Key Findings
plt.figure()
plt.plot(data['Allocation Size'], data['Default Time (s)'], label='Default malloc/free', marker='o', linestyle='--')
plt.plot(data['Allocation Size'], data['Custom Time (s)'], label='Custom mymalloc/myfree', marker='o', linestyle='--')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Allocation Size (bytes)')
plt.ylabel('Time (seconds)')
plt.title('Overall Performance: Default vs Custom malloc')
plt.legend()
plt.grid()
plt.savefig("summary_performance.png")
plt.show()
