<p align="center">
  <img src="https://github.com/thaisnishimoto/42-project-badges/blob/main/badges/philosophersm.png" alt="Philosophers bonus"/>
</p>

<h1 align=center>
	<b>Philosophers</b>
</h1>

<p align="center"><i>"In this project, you will learn the basics of threading a process. You will see how to create threads and you will discover mutexes."</i></p>  

<h2>
 Status
</h2>

**Finished:**  2024, May 13th <br>
**Grade:** 125/100

<h2>
Content
</h2>

[About the Project](https://github.com/thaisnishimoto/42sp_09_Philosophers?tab=readme-ov-file#about-the-project---dining-philosophers-problem)

[Mandatory Part](https://github.com/thaisnishimoto/42sp_09_Philosophers?tab=readme-ov-file#mandatory-part---philosophers-with-threads-and-mutexes)

[Bonus Part](https://github.com/thaisnishimoto/42sp_09_Philosophers?tab=readme-ov-file#bonus-part---philosophers-with-processes-and-semaphores)

[Usage](https://github.com/thaisnishimoto/42sp_09_Philosophers?tab=readme-ov-file#usage)

<h2>
About the Project - Dining Philosophers Problem
</h2>

The Dining Philosophers Problem is a classic synchronization problem in computer science and concurrent programming. It illustrates the challenges of a multi-threaded or multi-process environment. <br>

The problem showcases a scenario where a group of philosophers sit around a circular table, and the philosophers alternatively eat, think, or sleep. There are as many forks on the table as philosophers. To eat, a philosopher needs two forks. However, forks are shared among them, and only one philosopher can hold a fork at a time. <br>

When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation, or when they have all finished eating a given number of times.

The challenge is to design a solution that prevents deadlock (where each philosopher is holding one fork and waiting for the other, thus none can proceed), data racing (access to a shared resource without protection, leading to unpredictable behavior), and starvation (where a philosopher is perpetually denied access to the forks). <br>

The program will display a log of every state change of a philosopher, formatted as follows:
```
[timestamp_in_ms] [ID] has taken a fork
[timestamp_in_ms] [ID] is eating
[timestamp_in_ms] [ID] is sleeping
[timestamp_in_ms] [ID] is thinking
[timestamp_in_ms] [ID] died
```

<h2>
Mandatory Part - Philosophers with threads and mutexes
</h2>
In the mandatory part, there is one fork between each pair of philosophers and a philosopher needs both forks adjacent to them to start eating. Each philosopher should be a thread and each fork should be protected by a mutex.

### Important concepts:
* **Threads** represent individual execution units within a process. They allow programs to perform multiple tasks concurrently, with each thread executing independently, but sharing the same memory space and resources of the parent process. Threads enable parallelism and multitasking within a program, facilitating tasks such as responsive user interfaces, parallel processing, and asynchronous operations.
* **Concurrency vs. parallelism** While concurrency is about structuring programs to handle multiple tasks efficiently in overlapping time periods, by switching between threads (_dealing_ with lots of things at once), parallelism is about executing tasks simultaneously to achieve faster execution times, by leveraging multiple processing units (_doing_ with lots of things at once).
* **Mutex**, short for mutual exclusion, is used in concurrent programming to prevent multiple threads from simultaneously accessing shared resources such as variables or data structures. It ensures that only one thread can access a critical section of code at any given time, preventing race conditions and maintaining data integrity.

<h2>
Bonus Part - Philosophers with processes and semaphores
</h2>
In the bonus part, the program behaves the same way. However, the implementation is modified: each philosopher should be a process and all the forks are put in the middle of the table. The number of available forks is represented by a counting semaphore.

<h2>
Usage
</h2>

Clone the repository:
```sh
git clone git@github.com:thaisnishimoto/42sp_09_Philosophers.git
```
Go to either `philo` or `philo_bonus` directory:
```sh
cd philo
```
Compile:
```sh
make
```
To check for possible data racing, compiling with flag -fsanitize=thread:
```sh
make race
```
Run `philo` or `philo_bonus` program:
```
./philo <num_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> [times_each_must_eat]
```
