/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:08:26 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/04/17 23:32:18 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/philosopher.h"
#include "PHILOSOPHERS/philosopher/philosopher_action.h"
#include <stdio.h>

void	philosopher_init(struct s_philosopher *philosopher, \
struct s_simulation *simulation, const struct s_simulation_settings *settings, \
unsigned int philosopher_id)
{
	*(unsigned int *) &philosopher->id = philosopher_id;
	philosopher->meals_eaten = 0;
	philosopher->last_meal_time = simulation->philosophers_last_meal_times + \
		philosopher_id - 1;
	if (philosopher_id == 1)
		philosopher->left_fork = simulation->forks + \
			settings->amount_of_philosophers - 1;
	else
		philosopher->left_fork = simulation->forks + philosopher_id - 2;
	philosopher->right_fork = simulation->forks + philosopher_id - 1;
	philosopher->simulation_states = &simulation->states;
	philosopher->simulation_settings = settings;
}

void	*philosopher_routine(struct s_philosopher *philosopher)
{
	if (simulation_signal_status_get(\
		&philosopher->simulation_states->start_signal))
		return (free(philosopher), NULL);
	philosopher_action_print(philosopher, "has taken a fork");
	while (1)
	{
		if (simulation_signal_status_get(\
			&philosopher->simulation_states->kill_signal))
			return (free(philosopher), NULL);
	// 	philosopher_think(philosopher);
	// 	philosopher_take_forks(philosopher);
	// 	philosopher_eat(philosopher);
	// 	philosopher_put_forks(philosopher);
	}
	free(philosopher);
	return (NULL);
}
