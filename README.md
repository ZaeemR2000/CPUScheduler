# CPUScheduler
 
Overview
    This project implements a simulation of three CPU scheduling algorithms:

        First Come First Serve (FCFS)
        Round Robin (RR)
        Shortest Job First (SJF)

The simulator reads task information from an input file and uses the specified scheduling algorithm to simulate task execution. The results include a time-based Gantt-style output showing which task is executed at each time unit, along with key statistics such as average waiting time, turnaround time, response time, and CPU usage.

Usage Instructions
    Compilation
        The project is developed using C++ and has been tested in Visual Studio. Follow these steps to compile the project:

        Open the Project in Visual Studio.

        Ensure that the scheduler.cpp file is present in the Source Files folder within the Visual Studio project.
        Build the Project.

        Select Build > Build Solution or press Ctrl + Shift + B to compile the program.

Running the Program
    
    The program is executed with command-line arguments to specify the input file and the scheduling algorithm. The general format is as follows:
    scheduler.exe <input_file> [FCFS|RR|SJF] [time_quantum]

    input_file: A file containing process task details.
    [FCFS|RR|SJF]: The scheduling algorithm to use.
    time_quantum: The time slice for the Round Robin scheduling algorithm (only required for RR).

Example Commands:

    First Come First Serve (FCFS): scheduler.exe input.1 FCFS
    Round Robin (RR) with time quantum of 4 milliseconds: scheduler.exe input.1 RR 4
    Shortest Job First (SJF): scheduler.exe input.1 SJF

Input File Format

    The input file should contain task information in the following format:
    pid arrival_time burst_time
    pid: Process ID (an integer).
    arrival_time: Time when the task arrives in the system (in milliseconds).
    burst_time: The CPU time required by the task (in milliseconds).

Command-Line Arguments in Visual Studio

    Right-click the project name in Solution Explorer and select Properties.
    Navigate to Configuration Properties > Debugging.
    In the Command Arguments field, enter the required arguments. Example:

        For FCFS: C:\path\to\input.1 FCFS
        For RR: C:\path\to\input.1 RR 4
        For SJF: C:\path\to\input.1 SJF
    Click Apply and OK.

Execution Output
After running the program, it will display the Gantt-style task scheduling and the following statistics:
    Average CPU Usage
    Average Waiting Time
    Average Turnaround Time