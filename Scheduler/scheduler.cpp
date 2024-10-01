#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Structure to represent a task
struct Task {
    int pid;           // Process ID
    int arrival_time;  // Arrival time in milliseconds
    int burst_time;    // Burst time in milliseconds
    int remaining_time; // Remaining time (for preemptive scheduling)
    int start_time;    // Time when process starts for the first time
    int completion_time; // Time when the process completes
    int waiting_time;  // Waiting time
    int turnaround_time; // Turnaround time
    bool finished;     // Indicates if the task is finished

    Task(int p, int a, int b) {
        pid = p;
        arrival_time = a;
        burst_time = b;
        remaining_time = b;
        start_time = -1; // Indicates the process has not started yet
        completion_time = 0;
        waiting_time = 0;
        turnaround_time = 0;
        finished = false;
    }
};

// Function prototypes for scheduling algorithms
void FCFS(vector<Task>& tasks);
void RR(vector<Task>& tasks, int time_quantum);
void SJF(vector<Task>& tasks);

// Function to read tasks from input file
vector<Task> readTasks(string filename) {
    vector<Task> tasks;
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: could not open file " << filename << endl;
        exit(1);
    }

    int pid, arrival_time, burst_time;
    while (infile >> pid >> arrival_time >> burst_time) {
        tasks.push_back(Task(pid, arrival_time, burst_time));
    }

    return tasks;
}

// Function to simulate FCFS scheduling algorithm
void FCFS(vector<Task>& tasks) {
    int time = 0;
    int total_waiting_time = 0, total_turnaround_time = 0;
    int total_tasks = tasks.size();

    cout << "Scheduling algorithm: FCFS" << endl;
    cout << "Total " << total_tasks << " tasks are read. Press 'Enter' to start..." << endl;
    cin.get(); // Wait for user to press enter

    for (int i = 0; i < total_tasks; i++) {
        if (time < tasks[i].arrival_time) {
            // If CPU is idle
            while (time < tasks[i].arrival_time) {
                cout << "<system time " << time << "> idle" << endl;
                time++;
            }
        }

        tasks[i].start_time = time;
        cout << "<system time " << time << "> process " << tasks[i].pid << " is running" << endl;

        // Simulate task execution
        while (time < tasks[i].start_time + tasks[i].burst_time) {
            cout << "<system time " << time << "> process " << tasks[i].pid << " is running" << endl;
            time++;
        }

        tasks[i].completion_time = time;
        tasks[i].turnaround_time = tasks[i].completion_time - tasks[i].arrival_time;
        tasks[i].waiting_time = tasks[i].turnaround_time - tasks[i].burst_time;

        total_waiting_time += tasks[i].waiting_time;
        total_turnaround_time += tasks[i].turnaround_time;

        cout << "<system time " << time << "> process " << tasks[i].pid << " is finished" << endl;
    }

    cout << "<system time " << time << "> All processes finished..." << endl;

    // Calculate and display average waiting time, turnaround time, and CPU usage
    double avg_waiting_time = (double)total_waiting_time / total_tasks;
    double avg_turnaround_time = (double)total_turnaround_time / total_tasks;
    double cpu_usage = 100.0; // For FCFS, we assume 100% CPU usage.

    cout << "============================================================" << endl;
    cout << "Average CPU usage: " << cpu_usage << " %" << endl;
    cout << "Average waiting time: " << avg_waiting_time << endl;
    cout << "Average turnaround time: " << avg_turnaround_time << endl;
    cout << "============================================================" << endl;
}

// Function to simulate RR scheduling algorithm
void RR(vector<Task>& tasks, int time_quantum) {
    int time = 0;
    int total_waiting_time = 0, total_turnaround_time = 0;
    int total_tasks = tasks.size();
    queue<Task*> ready_queue;
    vector<Task*> pending_tasks;

    cout << "Scheduling algorithm: Round Robin (Time Quantum = " << time_quantum << " ms)" << endl;
    cout << "Total " << total_tasks << " tasks are read. Press 'Enter' to start..." << endl;
    cin.get(); // Wait for user to press enter

    // Add all tasks to pending tasks list
    for (Task& task : tasks) {
        pending_tasks.push_back(&task);
    }

    while (!pending_tasks.empty() || !ready_queue.empty()) {
        // Move tasks that have arrived into the ready queue
        for (auto it = pending_tasks.begin(); it != pending_tasks.end();) {
            if ((*it)->arrival_time <= time) {
                ready_queue.push(*it);
                it = pending_tasks.erase(it);
            }
            else {
                ++it;
            }
        }

        if (ready_queue.empty()) {
            // If no task is ready, the CPU is idle
            cout << "<system time " << time << "> idle" << endl;
            time++;
            continue;
        }

        // Pick the next task from the ready queue
        Task* current_task = ready_queue.front();
        ready_queue.pop();

        if (current_task->start_time == -1) {
            current_task->start_time = time;
        }

        // Run the task for the time quantum or until it finishes
        int runtime = min(time_quantum, current_task->remaining_time);
        for (int t = 0; t < runtime; t++) {
            cout << "<system time " << time << "> process " << current_task->pid << " is running" << endl;
            time++;
        }

        current_task->remaining_time -= runtime;

        if (current_task->remaining_time > 0) {
            // If the task is not finished, add it back to the ready queue
            ready_queue.push(current_task);
        }
        else {
            // Task is finished
            current_task->completion_time = time;
            current_task->turnaround_time = current_task->completion_time - current_task->arrival_time;
            current_task->waiting_time = current_task->turnaround_time - current_task->burst_time;

            total_waiting_time += current_task->waiting_time;
            total_turnaround_time += current_task->turnaround_time;

            cout << "<system time " << time << "> process " << current_task->pid << " is finished" << endl;
        }
    }

    cout << "<system time " << time << "> All processes finished..." << endl;

    // Calculate and display average waiting time, turnaround time, and CPU usage
    double avg_waiting_time = (double)total_waiting_time / total_tasks;
    double avg_turnaround_time = (double)total_turnaround_time / total_tasks;
    double cpu_usage = 100.0; // We assume 100% CPU usage as Round Robin keeps switching tasks

    cout << "============================================================" << endl;
    cout << "Average CPU usage: " << cpu_usage << " %" << endl;
    cout << "Average waiting time: " << avg_waiting_time << endl;
    cout << "Average turnaround time: " << avg_turnaround_time << endl;
    cout << "============================================================" << endl;
}

// Function to simulate SJF scheduling algorithm (preemptive)
void SJF(vector<Task>& tasks) {
    int time = 0;
    int total_waiting_time = 0, total_turnaround_time = 0;
    int total_tasks = tasks.size();
    vector<Task*> ready_queue;
    vector<Task*> pending_tasks;

    cout << "Scheduling algorithm: Shortest Job First (Preemptive)" << endl;
    cout << "Total " << total_tasks << " tasks are read. Press 'Enter' to start..." << endl;
    cin.get(); // Wait for user to press enter

    // Add all tasks to pending tasks list
    for (Task& task : tasks) {
        pending_tasks.push_back(&task);
    }

    Task* current_task = nullptr;

    while (!pending_tasks.empty() || !ready_queue.empty() || current_task) {
        // Move tasks that have arrived into the ready queue
        for (auto it = pending_tasks.begin(); it != pending_tasks.end();) {
            if ((*it)->arrival_time <= time) {
                ready_queue.push_back(*it);
                it = pending_tasks.erase(it);
            }
            else {
                ++it;
            }
        }

        // Sort the ready queue based on remaining time (shortest job first)
        sort(ready_queue.begin(), ready_queue.end(), [](Task* a, Task* b) {
            return a->remaining_time < b->remaining_time;
            });

        // If there is no current task or if a new task with shorter remaining time arrives, preempt
        if (current_task == nullptr || (!ready_queue.empty() && ready_queue[0]->remaining_time < current_task->remaining_time)) {
            if (current_task != nullptr) {
                ready_queue.push_back(current_task);  // Preempt the current task
            }
            current_task = ready_queue[0];
            ready_queue.erase(ready_queue.begin());

            if (current_task->start_time == -1) {
                current_task->start_time = time;
            }
        }

        // Simulate task execution for 1 millisecond
        if (current_task != nullptr) {
            cout << "<system time " << time << "> process " << current_task->pid << " is running" << endl;
            current_task->remaining_time--;
            time++;

            if (current_task->remaining_time == 0) {
                // Task is finished
                current_task->completion_time = time;
                current_task->turnaround_time = current_task->completion_time - current_task->arrival_time;
                current_task->waiting_time = current_task->turnaround_time - current_task->burst_time;

                total_waiting_time += current_task->waiting_time;
                total_turnaround_time += current_task->turnaround_time;

                cout << "<system time " << time << "> process " << current_task->pid << " is finished" << endl;

                current_task = nullptr; // Reset current task after finishing
            }
        }
        else {
            // If no task is ready, the CPU is idle
            cout << "<system time " << time << "> idle" << endl;
            time++;
        }
    }

    cout << "<system time " << time << "> All processes finished..." << endl;

    // Calculate and display average waiting time, turnaround time, and CPU usage
    double avg_waiting_time = (double)total_waiting_time / total_tasks;
    double avg_turnaround_time = (double)total_turnaround_time / total_tasks;
    double cpu_usage = 100.0; // Assuming the CPU is always busy when a task is available

    cout << "============================================================" << endl;
    cout << "Average CPU usage: " << cpu_usage << " %" << endl;
    cout << "Average waiting time: " << avg_waiting_time << endl;
    cout << "Average turnaround time: " << avg_turnaround_time << endl;
    cout << "============================================================" << endl;
}

// Main function to select the scheduling algorithm based on input
int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " input_file [FCFS|RR|SJF] [time_quantum]" << endl;
        return 1;
    }

    string input_file = argv[1];
    string algorithm = argv[2];
    int time_quantum = 0;

    if (algorithm == "RR" && argc == 4) {
        time_quantum = stoi(argv[3]);
    }
    else if (algorithm == "RR" && argc < 4) {
        cerr << "Error: Round Robin requires a time quantum." << endl;
        return 1;
    }

    vector<Task> tasks = readTasks(input_file);

    if (algorithm == "FCFS") {
        FCFS(tasks);
    }
    else if (algorithm == "RR") {
        RR(tasks, time_quantum);
    }
    else if (algorithm == "SJF") {
        SJF(tasks);
    }
    else {
        cerr << "Error: Unknown scheduling algorithm: " << algorithm << endl;
        return 1;
    }

    return 0;
}
