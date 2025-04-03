# philosophers

The dining philosophers problem in C, with threads and mutexes. A few philosophers sit at a round table with a fork between each of them. To eat they need two forks, and if one of them goes too long without eating, he dies. The program has to keep them all alive, with no data races, and print what each one is doing.

## Run it

```bash
make
./philo <philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [meals]
```

Times are in milliseconds. A few cases to try:

```bash
./philo 5 800 200 200       # nobody dies
./philo 5 800 200 200 7     # stops when everyone has eaten 7 times
./philo 4 310 200 100       # one philosopher dies
./philo 1 800 200 200       # only one fork: he dies at 800
```
