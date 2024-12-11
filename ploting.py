import matplotlib.pyplot as plt
import pandas as pd

# Load data from the file
file_path = 'benchmarks.txt'

# Read the file into a pandas DataFrame
df = pd.read_csv(file_path, sep=" ", header=None, names=["Size", "DefaultMalloc", "CustomMalloc"])

# Plot the data
plt.figure(figsize=(20, 6))
plt.plot(df["Size"], df["DefaultMalloc"], label="Default Malloc", marker='o')
plt.plot(df["Size"], df["CustomMalloc"], label="Custom Malloc", marker='s')

plt.title("Allocation Size vs Time")
plt.xlabel("Allocation Size")
plt.ylabel("Time (seconds)")
plt.xscale('log')

plt.legend()
plt.grid(True)
plt.show()