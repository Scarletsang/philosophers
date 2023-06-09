/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:08:26 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/04/27 22:45:52 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/philosopher.h"
#include "PHILOSOPHERS/philosopher/action.h"
#include <stdlib.h>

static inline void	*philosopher_die(struct s_philosopher *philosopher)
{
	if (philosopher->action == &philosopher_take_forks)
	{
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);
	}
	free(philosopher);
	return (NULL);
}

void	*philosopher_routine(struct s_philosopher *philosopher)
{
	if (simulation_signal_status_get(\
		&philosopher->simulation_states->start_signal))
		return (free(philosopher), NULL);
	if ((philosopher->id % 2) == 1)
		time_sleep(philosopher->simulation_settings->time_to_eat / 2);
	philosopher->action = &philosopher_take_forks;
	while (1)
	{
		if (simulation_signal_status_get(\
				&philosopher->simulation_states->kill_signal))
				return (philosopher_die(philosopher));
		if (philosopher->action(philosopher))
		{
			*philosopher->last_meal_time = 0;
			return (philosopher_die(philosopher));
		}
	}
}
