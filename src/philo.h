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

/**
 * @struct s_fork
 * @brief Represents a fork in the dining philosophers problem
 *
 * @var mutex Mutex for controlling access to the fork
 */
typedef struct s_fork {
	long last_used;
	pthread_mutex_t mutex;
} t_fork;

/**
 * @struct s_philo
 * @brief Represents a philosopher in the dining philosophers problem
 *
 * @var id Unique identifier for the philosopher
 * @var data Pointer to the shared data structure
 * @var times_eaten Number of times the philosopher has eaten
 * @var last_meal_time Timestamp of the philosopher's last meal
 * @var full Boolean indicating if the philosopher is full
 * @var dead Boolean indicating if the philosopher has died
 * @var thread Thread handle for the philosopher
 * @var mutex Mutex for controlling access to the philosopher's data
 */
typedef struct s_philo {
	int id;
	t_data *data;
	long	times_eaten;
	long	last_meal_time;
	bool	full;
	bool	dead;
	pthread_t thread;
	pthread_mutex_t mutex;
} t_philo;

/**
 * @struct s_data
 * @brief Contains shared data for the dining philosophers simulation
 *
 * @var forks Array of forks
 * @var start_mutex Mutex for controlling the start of the simulation
 * @var num_philosophers Number of philosophers
 * @var time_to_die Time limit for a philosopher to eat before dying
 * @var time_to_eat Time it takes for a philosopher to eat
 * @var time_to_sleep Time a philosopher spends sleeping
 * @var max_meals Maximum number of meals before the simulation ends (optional)
 * @var end_simulation Flag to indicate the end of the simulation
 * @var start_time Timestamp when the simulation started
 * @var ready_count Counter for philosophers ready to start
 * @var start_flag Flag to indicate the start of the simulation
 * @var monitor_thread Thread handle for the monitoring thread
 * @var philosophers Array of philosopher structures
 */
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
/**
 * @brief Get the current timestamp in milliseconds
 * @return long Current timestamp in milliseconds
 */
long get_timestamp_in_ms();

/**
 * @brief Print a state change for a philosopher
 * @param philo Pointer to the philosopher structure
 * @param state String describing the new state
 */
void print_state_change(t_philo *philo, const char *state);

/**
 * @brief Simulate a philosopher thinking
 * @param philo Pointer to the philosopher structure
 */
void think(t_philo *philo);

/**
 * @brief Simulate a philosopher eating
 * @param philo Pointer to the philosopher structure
 */
long eat(t_philo *philo);

/**
 * @brief Simulate a philosopher sleeping
 * @param philo Pointer to the philosopher structure
 */
void sleep_philo(t_philo *philo);

/**
 * @brief Simulate a philosopher picking up forks
 * @param philo Pointer to the philosopher structure
 */
void pick_up_forks(t_philo *philo);

/**
 * @brief Simulate a philosopher putting down forks
 * @param philo Pointer to the philosopher structure
 */
void put_down_forks(t_philo *philo, long timestamp);

/**
 * @brief Determine the hungriest philosopher among the current philosopher and its two neighbors
 * @param data Pointer to the shared data structure
 * @param current_id The ID of the current philosopher
 * @return bool true if the current philosopher is the hungriest, false otherwise
 */
bool	hungriest_philosopher(t_data *data, int current_id);

// init_data.c
/**
 * @brief Initialize forks for the simulation
 * @param data Pointer to the shared data structure
 */
void	initialize_forks(t_data *data);

/**
 * @brief Create threads for each philosopher
 * @param data Pointer to the shared data structure
 */
void 	create_philosopher_threads(t_data *data);

/**
 * @brief Join all philosopher threads
 * @param data Pointer to the shared data structure
 */
void join_philosopher_threads(t_data *data);

/**
 * @brief Destroy all mutexes used in the simulation
 * @param data Pointer to the shared data structure
 */
void destroy_mutexes(t_data *data);

// simulation.c
/**
* @brief Main routine for single philosopher thread
* @param arg Pointer to the philosopher structure (cast to void*)
* @return void* Always returns NULL
*/
void *single_philo(void *arg);

/**
 * @brief Main routine for each philosopher thread
 * @param arg Pointer to the philosopher structure
 * @return void* Always returns NULL
 */
void *philosopher_routine(void *arg);

/**
 * @brief Routine for the monitor thread
 * @param arg Pointer to the shared data structure
 * @return void* Always returns NULL
 */
void *monitor_routine(void *arg);

// safe_functions.c
/**
 * @brief Safely get a boolean value
 * @param mutex Pointer to the mutex protecting the value
 * @param value Pointer to the boolean value
 * @return bool The retrieved boolean value
 */
bool	get_bool(pthread_mutex_t *mutex, bool *value);

/**
 * @brief Safely set a boolean value
 * @param mutex Pointer to the mutex protecting the value
 * @param value Pointer to the boolean value to be set
 * @param new_value The new boolean value
 */
void	set_bool(pthread_mutex_t *mutex, bool *value, bool new_value);

/**
 * @brief Safely get a long value
 * @param mutex Pointer to the mutex protecting the value
 * @param value Pointer to the long value
 * @return long The retrieved long value
 */
long	get_long(pthread_mutex_t *mutex, long *value);

/**
 * @brief Safely set a long value
 * @param mutex Pointer to the mutex protecting the value
 * @param value Pointer to the long value to be set
 * @param new_value The new long value
 */
void	set_long(pthread_mutex_t *mutex, long *value, long new_value);

#endif
