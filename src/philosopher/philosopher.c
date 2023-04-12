/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:08:26 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/04/12 23:06:55 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/philosopher.h"
#include <stdio.h>

void	philosopher_init(struct s_philosopher *philosopher, \
struct s_simulation *simulation, const struct s_simulation_settings *settings, \
unsigned int philosopher_id)
{
	*(unsigned int *) &philosopher->id = philosopher_id;
	philosopher->meals_eaten = 0;
	philosopher->last_meal_time = time_current_get();
	if (philosopher_id == 1)
		*(pthread_mutex_t *) &philosopher->right_fork = \
			simulation->forks[settings->amount_of_philosophers - 1];
	else
		*(pthread_mutex_t *) &philosopher->right_fork = \
			simulation->forks[philosopher_id - 1];
	*(pthread_mutex_t *) &philosopher->left_fork = \
		simulation->forks[philosopher_id];
	philosopher->simulation_states = &simulation->states;
	philosopher->simulation_settings = settings;
}

static t_simulation_status	philosopher_wait_for_start_signal(\
const struct s_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->simulation_states->start_signal.mutex);
	if (philosopher->simulation_states->start_signal.status == \
		SIMULATION_FAILURE)
	{
		pthread_mutex_unlock(\
			&philosopher->simulation_states->start_signal.mutex);
		return (SIMULATION_FAILURE);
	}
	pthread_mutex_unlock(&philosopher->simulation_states->start_signal.mutex);
	return (SIMULATION_SUCCESS);
}

void	*philosopher_routine(struct s_philosopher *philosopher)
{
	if (philosopher_wait_for_start_signal(philosopher))
	{
		free(philosopher);
		return (NULL);
	}
	
	philosopher_action_print(philosopher, "has taken a fork");
	// while (1)
	// {
	// 	philosopher_think(philosopher);
	// 	philosopher_take_forks(philosopher);
	// 	philosopher_eat(philosopher);
	// 	philosopher_put_forks(philosopher);
	// }
	free(philosopher);
	return (NULL);
}
