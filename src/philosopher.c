/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:08:26 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/04/10 22:55:26 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/philosopher.h"

static void	philosopher_init(struct s_philosopher *philosopher, \
const struct s_simulation *simulation, \
const struct s_simulation_settings *settings, unsigned int philosopher_id)
{
	*(unsigned int *) &philosopher->id = philosopher_id;
	philosopher->meals_eaten = 0;
	philosopher->last_meal_time = time_get_current();
	if (philosopher_id == 1)
		*(pthread_mutex_t *) &philosopher->right_fork = \
			simulation->forks[settings->amount_of_philosophers - 1];
	else
		*(pthread_mutex_t *) &philosopher->right_fork = \
			simulation->forks[philosopher_id - 1];
	*(pthread_mutex_t *) &philosopher->left_fork = \
		simulation->forks[philosopher_id];
	*(pthread_mutex_t *) &philosopher->is_printing = simulation->is_printing;
	*(t_milliseconds *) &philosopher->start_time = simulation->start_time;
	philosopher->simulation_settings = settings;
}

static void	*philosopher_routine(struct s_philosopher *philosopher)
{
	while (1)
	{
		philosopher_think(philosopher);
		philosopher_take_forks(philosopher);
		philosopher_eat(philosopher);
		philosopher_put_forks(philosopher);
	}
	free(philosopher);
	return (NULL);
}

t_simulation_status	simulation_spawn_philosopher(\
const struct s_simulation *simulation, \
const struct s_simulation_settings *settings, unsigned int philosopher_id)
{
	struct s_philosopher	*philosopher;

	philosopher = malloc(sizeof(struct s_philosopher));
	if (!philosopher)
		return (SIMULATION_FAILURE);
	philosopher_init(philosopher, simulation, settings, philosopher_id);
	if (pthread_create(&simulation->philosophers[philosopher_id - 1], NULL, \
		(void *(*)(void *)) philosopher_routine, (void *) philosopher))
	{
		free(philosopher);
		return (SIMULATION_FAILURE);
	}
	return (SIMULATION_SUCCESS);
}
