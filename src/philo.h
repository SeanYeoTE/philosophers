#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_data t_data;

typedef struct s_fork {
    pthread_mutex_t mutex;
} t_fork;

typedef struct s_philo {
    int id;
    t_data *data;
    long	times_eaten;
    long	last_meal_time;
	bool	full;
    pthread_t thread;
    pthread_mutex_t mutex;
} t_philo;

typedef struct s_data {
    t_fork *forks;
    pthread_mutex_t start_mutex;
    long num_philosophers;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long max_meals;
    bool	end_simulation;
    long start_time;
    long ready_count;
    bool	start_flag;
    pthread_t monitor_thread;
    t_philo *philosophers;
} t_data;



// helpers.c
long get_timestamp_in_ms();
void print_state_change(t_philo *philo, const char *state);
void think(t_philo *philo);
void eat(t_philo *philo);
void sleep_philo(t_philo *philo);
void pick_up_forks(t_philo *philo);
void put_down_forks(t_philo *philo);

// init_data.c
void initialize_mutexes(t_data *data);
void create_philosopher_threads(t_data *data, t_philo *philosophers);
void join_philosopher_threads(t_data *data);
void destroy_mutexes(t_data *data);

// simulation.c
void *philosopher_routine(void *arg);
void *monitor_routine(void *arg);

// safe_functions.c
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_bool(pthread_mutex_t *mutex, bool *value, bool new_value);
long	get_long(pthread_mutex_t *mutex, long *value);
void	set_long(pthread_mutex_t *mutex, long *value, long new_value);

#endif
