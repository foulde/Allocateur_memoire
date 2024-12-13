# MyMalloc Application

This repository contains a custom memory allocator implementation (`mymalloc`) along with tests and benchmarks to evaluate its performance. The project also includes visualization tools for performance analysis.

## Project Structure

- **`src/mymalloc.c`**: The core implementation of the custom memory allocator.
- **`src/test.c`**: Unit tests to verify the correctness of `mymalloc`.
- **`src/benchmark.c`**: Benchmarks to measure the performance of `mymalloc`.
- **`plotting.py`**: A Python script for visualizing benchmark results.

## Build and Run Instructions

The project can be built and run using the provided `Makefile`. Below are the available targets:

### 1. `all`
Builds and runs both the test and benchmark programs:
```bash
make all
```

### 2. `visualize `
Once all have been run or benchmarks you should get `benchmarks.txt` in your 
working directory

enter this command to vizualize the result obtained :
```bash
make visualize
