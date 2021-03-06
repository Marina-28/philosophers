# philosophers
### The training projects for learn the basics of threading a process
## Description:
* One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
* The philosophers alternatively **eat**, **think**, or **sleep**.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
* There are also forks on the table. There are as many forks as philosophers.
* Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
* When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.
* Every philosopher needs to eat and should never starve.
* Philosophers don’t speak with each other.
* Philosophers don’t know if another philosopher is about to die.
* No need to say that philosophers should avoid dying!

## Rules:
* Program takes 4 arguments:
    * int number_of__philosophers;
    *  time_to_die (in milliseconds);
    *  time_to_eat (in milliseconds);
    *  time_to_sleep (in milliseconds);
    *  number_of_times_each_philosopher_must_eat (optional argument);
*  Any state change of a philosopher must be formatted as follows:
    * timestamp_in_ms X has taken a fork
    * timestamp_in_ms X is eating
    * timestamp_in_ms X is sleeping
    * timestamp_in_ms X is thinking
    * timestamp_in_ms X died
*Timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.*

## Mandatory part (philo):
* Each philosopher should be a thread.
* There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, there should be only one fork on the table.
* To prevent philosophers from duplicating forks, you should protect the forks state
with a mutex for each of them.

## Bonus part (philo_bonus):
* All the forks are put in the middle of the table.
* They have no states in memory but the number of available forks is represented by
a semaphore.
* Each philosopher should be a process. But the main process should not be a
philosopher.

## Launch:
```
%>make
%>./philo 4 310 200 200
```
*If you input this arguments, a philosopher should die!
Strangely enough, a philosopher can starve to death while eating.*
