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

The Dining Philosophers Problem is a classic synchronization problem in computer science and concurrent programming. It illustrates the challenges of resource allocation and the prevention of deadlock in a multi-threaded or multi-process environment. <br>

A group of philosophers sit around a circular table, each philosopher is either eating, sleeping, or thinking. Between each philosopher, there is a single fork. To eat, a philosopher needs both forks adjacent to them. However, only one philosopher can hold a fork at a time. <br>

The challenge is to design a solution that prevents deadlock (where each philosopher is holding one fork and waiting for the other, thus none can proceed) and starvation (where a philosopher is perpetually denied access to the forks). <br>

<h2>
Mandatory Part - Philosophers with threads and mutexes
</h2>

<h2>
Bonus Part - Philosophers with processes and semaphores
</h2>

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
