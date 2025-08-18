
# Philosophers 
Simple code that tackles the dining philosophers problem, take forks → eat → sleep → think, while enforcing timing constraints, avoiding deadlocks, and stopping on death or after each philosopher has eaten a required number of times.


## Usage

`make`

`./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`

## Output format

`<timestamp_ms> <philo_id> <message>`

## Recommended tests

### 1) Single philosopher must die
./philo 1 800 200 200

### 2) No deaths for a while with two philosophers
./philo 2 800 200 200

### 3) Meal quota: program exits when each ate 7 times
./philo 5 800 200 200 7

### 4) Tight death window: someone should die ~310 ms
./philo 5 310 200 100

### 5) Stress test
./philo 200 610 200 200
