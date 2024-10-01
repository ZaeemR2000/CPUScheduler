# CPU Scheduling Simulation Project

## Overview

This project simulates three different CPU scheduling algorithms implemented in **C++**:

1. **First Come First Serve (FCFS)** 
2. **Round Robin (RR)** 
3. **Shortest Job First (SJF)**

The program reads task data from an input file and simulates the scheduling of tasks based on the selected algorithm. The output includes a Gantt-style schedule and statistics such as average waiting time, turnaround time, response time, and CPU usage.

## Features

- **FCFS**: Non-preemptive algorithm where tasks are executed in the order they arrive.
- **Round Robin (RR)**: Preemptive algorithm where each task is given a time slice (quantum) to execute before moving to the next task.
- **Shortest Job First (SJF)**: Preemptive algorithm that selects the task with the shortest burst time for execution.

## Technologies Used

- **Language**: C++
- **IDE**: Visual Studio 2022
- **Compiler**: Microsoft Visual C++ (MSVC)
- **Operating System**: Windows 10

## Project Structure

- `scheduler.cpp`: The main C++ file implementing the three scheduling algorithms.
- `input.1`: Example input file containing task data.
- Screenshots for each algorithm (FCFS, RR, SJF) showing execution and results.

## Compilation and Execution

### Compilation

To compile the project using **Visual Studio**:

1. Clone the repository.
2. Open the project in Visual Studio.
3. Ensure the `scheduler.cpp` file is in the **Source Files** folder.
4. Build the project:
   - Select **Build > Build Solution** or press `Ctrl + Shift + B`.

### Running the Program

The program expects the following command-line arguments:

```bash
scheduler.exe <input_file> [FCFS|RR|SJF] [time_quantum]
