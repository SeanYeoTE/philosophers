# 🧠 Philosophers

A C implementation of the classic Dining Philosophers problem. This project explores concurrent programming concepts, focusing on thread synchronization and mutexes to prevent deadlocks and ensure proper resource sharing among threads.

## 📖 Project Overview

The Dining Philosophers problem is a synchronization problem that illustrates the challenges of allocating shared resources among multiple processes without causing deadlocks. In this simulation:

- Philosophers sit around a table with a fork between each pair.
- Each philosopher alternates between thinking, eating, and sleeping.
- To eat, a philosopher needs to pick up both adjacent forks.
- The simulation must prevent deadlocks and starvation.

## 🚀 Features

- **Multithreading**: Each philosopher is represented by a separate thread.
- **Mutexes**: Forks are protected using mutexes to prevent simultaneous access.
- **Precise Timing**: Accurate tracking of time to manage philosopher states and detect starvation.
- **Custom Logging**: Thread-safe logging to monitor philosopher actions.
- **Error Handling**: Robust checks for system call failures and invalid inputs.

## 🛠️ Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/SeanYeoTE/philosophers.git
   ```
2. **Navigate to the project directory**:
   ```bash
   cd philosophers
   ```
3. **Compile the project**:
   ```bash
   make
   ```

## 🧪 Usage

Run the program with the following arguments:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: Total number of philosophers.
- `time_to_die`: Time (in milliseconds) a philosopher can go without eating before dying.
- `time_to_eat`: Time (in milliseconds) a philosopher spends eating.
- `time_to_sleep`: Time (in milliseconds) a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat` (optional): Simulation ends when each philosopher has eaten this many times.

**Example**:

```bash
./philo 5 800 200 200
```

This starts a simulation with 5 philosophers, where each dies if they don't eat within 800ms, spends 200ms eating, and 200ms sleeping.

## 📁 Project Structure

```
philosophers/
├── includes/         # Header files
├── src/              # Source files
├── Makefile          # Build script
└── README.md         # Project documentation
```

## 📚 Lessons Learned

Throughout the development of this project, several key insights and skills were acquired:

- **Concurrent Programming**: Gained a deep understanding of multithreading and mutexes to manage concurrent access to shared resources.
- **Deadlock Prevention**: Learned strategies to prevent deadlocks, such as ordering resource acquisition and ensuring philosophers don't all pick up the same fork first.
- **Resource Management**: Emphasized the importance of proper allocation and deallocation of resources to prevent leaks and ensure stability.
- **Precise Timing**: Understood the challenges of accurate time measurement in concurrent environments and implemented solutions to manage philosopher states effectively.
- **Timestamp Accuracy**: Learned that when timestamps are required, it is important to account for processing time before issuing commands like `usleep()`. Failing to do so introduces time drift, which is unacceptable in real-world systems that depend on precise timing.
- **Robust Error Handling**: Improved skills in detecting and handling errors gracefully, ensuring the program can recover or exit safely under unexpected conditions.
- **Project Planning**: Recognized that thorough planning and task breakdown significantly reduce development time and improve code quality.
