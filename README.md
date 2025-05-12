# 🕒 Real-Time Cooperative Task Scheduler (Without OS)

This project implements a simple **real-time cooperative task scheduler** in C++ that runs **without any operating system**. It simulates an RTOS-like environment where multiple tasks are scheduled and executed based on timing and priority constraints.

## 🔧 Features

- Add tasks with customizable time intervals and priorities
- Tasks are sorted and executed based on next run time and priority
- Uses C++11 standard libraries for time handling and threading
- Cooperative multitasking model (no preemption)
- Lightweight and minimal CPU usage

## 📂 Project Structure

- `main.cpp`: Core logic for the task scheduler and example task functions

## 🧠 How It Works

1. Each task is defined by:
   - A **callback function**
   - A **time interval** in milliseconds
   - A **priority level** (lower number = higher priority)

2. The scheduler:
   - Sorts tasks based on the `next_run` time and priority
   - Executes tasks whose scheduled time has arrived
   - Updates the `next_run` time after each execution
   - Sleeps briefly to reduce CPU usage

## 🧪 Sample Output

```bash
Starting Real-Time Task Scheduler...
Task A running every 1s
Task B running every 2s
Task A running every 1s
Task C running every 3s
...
