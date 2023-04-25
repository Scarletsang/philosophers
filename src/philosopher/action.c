/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:35:13 by htsang            #+#    #+#             */
/*   Updated: 2023/04/25 17:51:52 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/philosopher.h"
#include "PHILOSOPHERS/philosopher/action.h"

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
	*philosopher->last_meal_time = time_now();
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
	t_milliseconds	time_since_last_meal;

	philosopher_action_print(philosopher, "is thinking");
	time_since_last_meal = time_since(*philosopher->last_meal_time);
	if (time_since_last_meal < philosopher->simulation_settings->time_to_die)
	{
		time_sleep((philosopher->simulation_settings->time_to_die - \
				time_since_last_meal) * 7 / 10);
	}
	if (philosopher->meals_eaten == \
		philosopher->simulation_settings->amount_of_meals_must_eat)
		return (SIMULATION_FAILURE);
	philosopher->action = &philosopher_take_forks;
	return (SIMULATION_SUCCESS);
}
