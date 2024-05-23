# CPU-Scheduling-Simulation-in-OS
Simulate CPU scheduling with semaphores in C++. This project creates multiple processes and manages CPU allocation using semaphore synchronization. Experience process execution, CPU availability control, and efficient resource management in an OS-like environment. Ideal for learning and teaching CPU scheduling concepts.
This project simulates a CPU scheduling environment using semaphores to manage process execution and CPU availability. It includes two main components: processes and CPUs. Processes are created and added to a ready queue, from which they request and release CPU time. Semaphores are used to ensure proper synchronization between processes and CPUs.

## Files

- `cpuSchedulingSimulation.cpp`: Contains the CPU scheduling simulation with semaphores.

## CPU Scheduling Simulation

### Overview

This simulation demonstrates how multiple processes can be scheduled to run on a limited number of CPUs using semaphores. It includes:

- Creation of a specified number of processes.
- Management of CPU availability using semaphores.
- Execution of processes in a synchronized manner.

### Features

- **Semaphore-based synchronization**: Ensures proper access control to shared resources (CPUs).
- **Randomized process execution time**: Simulates real-world process execution times.
- **Scalable**: Allows user to specify the number of processes and CPUs.

### How to Use

1. **Compile**: Use a C++ compiler to compile the `cpuSchedulingSimulation.cpp` file.
    ```sh
    g++ -pthread cpuSchedulingSimulation.cpp -o cpuSchedulingSimulation
    ```
2. **Execute**: Run the compiled executable.
    ```sh
    ./cpuSchedulingSimulation
    ```
3. **Input**: Provide the number of processes and CPUs as prompted.
4. **Output**: The program will display the process execution sequence, CPU allocation, and completion.

### Example

```sh
$ ./cpuSchedulingSimulation
Maximum number of processes can only be 25. Enter the number of processes and CPUs:
5
2
A solution to the CPU scheduling problem using semaphores.
Process 0 is executing.
Process 1 is executing.
Process 2 is executing.
Process 3 is executing.
Process 4 is executing.
The CPU is idle.
Process 0 has completed execution.
Process 0 added to the ready queue.
Process 0 requesting CPU.
The CPU is executing the process.
Process 1 has completed execution.
Process 1 added to the ready queue.
Process 1 requesting CPU.
Process 0 releases the CPU.
Process 1 releases the CPU.
...

## Code Explanation

- **Initialization**: Semaphores are initialized to manage the ready queue, CPU availability, and process completion.
- **Process Threads**: Each process thread simulates execution, waits for CPU availability, and releases the CPU after execution.
- **CPU Thread**: The CPU thread manages the execution of processes, simulating CPU time allocation.

## Functions

- `void *process(void *number)`: Simulates a process execution, manages ready queue and CPU requests.
- `void *cpu(void *junk)`: Manages CPU execution of processes, ensuring proper synchronization using semaphores.

## Semaphore Details

- `sem_t readyQueue`: Controls access to the ready queue.
- `sem_t cpuAvailable`: Manages CPU availability.
- `sem_t cpuBusy`: Indicates if the CPU is busy.
- `sem_t processComplete`: Signals process completion.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributions

Contributions are welcome! If you encounter any issues or have suggestions for improvements, feel free to open an issue or submit a pull request.
