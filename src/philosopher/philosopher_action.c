/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:35:13 by htsang            #+#    #+#             */
/*   Updated: 2023/04/12 23:07:25 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/philosopher/philosopher_action.h"
#include <unistd.h>

t_simulation_status	philosopher_action_take_forks(\
struct s_philosopher *philosopher)
{
	if (philosopher->id % 2 == 1)
	{
		pthread_mutex_lock(&philosopher->left_fork);
		philosopher_action_print(philosopher, "has taken a fork");
		pthread_mutex_lock(&philosopher->right_fork);
		philosopher_action_print(philosopher, "has taken a fork");
		return (SIMULATION_SUCCESS);
	}
	pthread_mutex_lock(&philosopher->right_fork);
	philosopher_action_print(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->left_fork);
	philosopher_action_print(philosopher, "has taken a fork");
	return (SIMULATION_SUCCESS);
}
