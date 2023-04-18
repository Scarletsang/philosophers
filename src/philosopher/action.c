/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:35:13 by htsang            #+#    #+#             */
/*   Updated: 2023/04/18 16:54:32 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/philosopher.h"
#include "PHILOSOPHERS/philosopher/action.h"

t_simulation_status	philosopher_take_forks(struct s_philosopher *philosopher)
{
	if (philosopher->id % 2 == 1)
	{
		pthread_mutex_lock(philosopher->left_fork);
		philosopher_action_print(philosopher, "has taken a fork");
		pthread_mutex_lock(philosopher->right_fork);
		philosopher_action_print(philosopher, "has taken a fork");
		return (SIMULATION_SUCCESS);
	}
	pthread_mutex_lock(philosopher->right_fork);
	philosopher_action_print(philosopher, "has taken a fork");
	pthread_mutex_lock(philosopher->left_fork);
	philosopher_action_print(philosopher, "has taken a fork");
	return (SIMULATION_SUCCESS);
}

// t_simulation_status	philosopher_eat(struct s_philosopher *philosopher)
// {

// }

// t_simulation_status	philosopher_think(struct s_philosopher *philosopher)
// {

// }

// t_simulation_status	philosopher_put_forks(struct s_philosopher *philosopher)
// {

// }

// t_simulation_status	philosopher_sleep(struct s_philosopher *philosopher)
// {

// }
