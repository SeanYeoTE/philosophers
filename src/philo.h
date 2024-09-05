#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_data {
	pthread_mutex_t *forks;
	pthread_t *philosophers;
	pthread_mutex_t start_mutex;
	int num_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_times_each_philosopher_must_eat;
	int end_simulation;
	long start_time;
	int ready_count;
	int start_flag;
} t_data;

typedef struct s_philo {
	int id;
	t_data *data;
	int times_eaten;
	long last_meal_time;
} t_philo;

long get_timestamp_in_ms();
void print_state_change(t_philo *philo, const char *state);
void think(t_philo *philo);
void eat(t_philo *philo);
void sleep_philo(t_philo *philo);
void pick_up_forks(t_philo *philo);
void put_down_forks(t_philo *philo);
void *philosopher_routine(void *arg);
void initialize_mutexes(t_data *data);
void create_philosopher_threads(t_data *data, t_philo *philosophers);
void join_philosopher_threads(t_data *data);
void destroy_mutexes(t_data *data);

#endif
