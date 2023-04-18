/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:35:13 by htsang            #+#    #+#             */
/*   Updated: 2023/04/18 22:29:46 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/philosopher.h"
#include "PHILOSOPHERS/philosopher/action.h"
#include <unistd.h>

t_simulation_status	philosopher_take_forks(struct s_philosopher *philosopher)
{
	if ((philosopher->id % 2) == 1)
	{
		pthread_mutex_lock(philosopher->left_fork);
		philosopher_action_print(philosopher, "has taken a fork");
		pthread_mutex_lock(philosopher->right_fork);
		philosopher_action_print(philosopher, "has taken a fork");
		philosopher->action = &philosopher_eat;
		return (SIMULATION_SUCCESS);
	}
	pthread_mutex_lock(philosopher->right_fork);
	philosopher_action_print(philosopher, "has taken a fork");
	pthread_mutex_lock(philosopher->left_fork);
	philosopher_action_print(philosopher, "has taken a fork");
	philosopher->action = &philosopher_eat;
	return (SIMULATION_SUCCESS);
}

t_simulation_status	philosopher_eat(struct s_philosopher *philosopher)
{
	philosopher->meals_eaten++;
	philosopher_action_print(philosopher, "is eating");
	*philosopher->last_meal_time = time_current_get();
	time_sleep(philosopher->simulation_settings->time_to_eat);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
	philosopher->action = &philosopher_sleep;
	return (SIMULATION_SUCCESS);
}

t_simulation_status	philosopher_sleep(struct s_philosopher *philosopher)
{
	philosopher_action_print(philosopher, "is sleeping");
	time_sleep(philosopher->simulation_settings->time_to_sleep);
	philosopher->action = &philosopher_think;
	return (SIMULATION_SUCCESS);
}

t_simulation_status	philosopher_think(struct s_philosopher *philosopher)
{
	philosopher_action_print(philosopher, "is thinking");
	philosopher->action = &philosopher_take_forks;
	return (SIMULATION_SUCCESS);
}

