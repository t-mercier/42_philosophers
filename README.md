# Philosopher 

This project was developed as part of the 42 school curriculum. The Philosopher project aims to simulate the Dining Philosophers problem, a classic synchronization problem in computer science, to better understand the principles of multithreading and concurrency. 

The program is exceptionally fast, primarily due to the implementation of non-locking logging for philosopher status. This is achieved through the use of internal locking mechanisms within the printf function, ensuring that concurrent access to shared resources is safely managed, ultimately resulting in efficient and concurrent execution.


## Overview

The Dining Philosophers problem consists of a round table with `n` philosophers sitting around it, each with a fork between them. They spend their time thinking and eating. In order to eat, a philosopher must have both forks, one from the left and one from the right. However, the philosophers must also be careful not to create a deadlock or a starving philosopher.

The purpose of this project is to implement a solution to the Dining Philosophers problem using multiple threads and synchronization mechanisms such as mutexes, semaphores, or condition variables.

## Installation

To get started with the Philosopher project, clone the repository:
`git clone https://github.com/t-mercier/42_philosophers.git`

Before compiling the project, make sure your system has the required dependencies:

- A C compiler (e.g., GCC, Clang)
- A POSIX threads library (e.g., pthreads)

To compile the project, navigate to the cloned repository and run the following command:
`make`

This will produce an executable named `philo`.

## Usage

To run the Philosopher simulation, execute the following command:
`./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]`

- `<number_of_philosophers>`: The number of philosophers sitting around the table.
- `<time_to_die>`: The time in milliseconds a philosopher can spend without eating before dying.
- `<time_to_eat>`: The time in milliseconds a philosopher takes to eat.
- `<time_to_sleep>`: The time in milliseconds a philosopher takes to sleep after eating.
- `[number_of_times_each_philosopher_must_eat]` (optional): The number of times each philosopher must eat before the simulation ends.

Exemple: ./philosopher 5 800 200 200 10
This will run a simulation with 5 philosophers, where each philosopher has 800 milliseconds to eat before dying, takes 200 milliseconds to eat, 200 milliseconds to sleep, and must eat 10 times.

Thank you for your interest in the Philosopher project! If you have any questions or need assistance, please don't hesitate to reach out.


