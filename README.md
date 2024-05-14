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

[About the Project](https://github.com/thaisnishimoto/42sp_08_Minishell?tab=readme-ov-file#about-the-project)

[Functionality](https://github.com/thaisnishimoto/42sp_08_Minishell?tab=readme-ov-file#functionality)

[Usage](https://github.com/thaisnishimoto/42sp_08_Minishell?tab=readme-ov-file#usage)

<h2>
About the Project
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
