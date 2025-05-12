#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <functional>
#include <algorithm>

using namespace std;
using namespace std::chrono;

struct Task {
    function<void()> callback;
    int interval_ms;           // Task runs every `interval_ms` milliseconds
    int priority;              // Lower number = higher priority
    steady_clock::time_point next_run;

    Task(function<void()> cb, int interval, int prio)
        : callback(cb), interval_ms(interval), priority(prio) {
        next_run = steady_clock::now() + milliseconds(interval_ms);
    }
};

// Compare tasks by next_run time and priority
bool taskComparator(const Task &a, const Task &b) {
    if (a.next_run == b.next_run)
        return a.priority < b.priority;
    return a.next_run < b.next_run;
}

class TaskScheduler {
    vector<Task> tasks;

public:
    void addTask(function<void()> callback, int interval_ms, int priority) {
        tasks.emplace_back(callback, interval_ms, priority);
    }

    void run() {
        while (true) {
            sort(tasks.begin(), tasks.end(), taskComparator);
            auto now = steady_clock::now();

            for (auto &task : tasks) {
                if (now >= task.next_run) {
                    task.callback();
                    task.next_run = now + milliseconds(task.interval_ms);
                }
            }

            this_thread::sleep_for(milliseconds(1));  // Minimal CPU usage
        }
    }
};

// Sample task functions
void taskA() { cout << "Task A running every 1s\n"; }
void taskB() { cout << "Task B running every 2s\n"; }
void taskC() { cout << "Task C running every 3s\n"; }

int main() {
    TaskScheduler scheduler;

    scheduler.addTask(taskA, 1000, 1);  // High priority
    scheduler.addTask(taskB, 2000, 2);
    scheduler.addTask(taskC, 3000, 3);  // Low priority

    cout << "Starting Real-Time Task Scheduler...\n";
    scheduler.run();  // Infinite loop

    return 0;
}