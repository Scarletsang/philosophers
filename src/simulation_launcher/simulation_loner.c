/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_loner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:48:01 by htsang            #+#    #+#             */
/*   Updated: 2023/04/19 19:51:41 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/simulation_launcher.h"

void	*lonely_philosopher_routine(struct s_lonely_simulation *simulation)
{
	pthread_mutex_lock(&simulation->fork);
	simulation_philosopher_status_print(\
		time_since(simulation->start_time), 1, "has taken a fork");
	pthread_mutex_unlock(&simulation->fork);
	time_sleep(simulation->time_to_die);
	simulation_philosopher_status_print(\
		time_since(simulation->start_time), 1, "died");
	return (NULL);
}

t_simulation_status	lonely_simulation_start(t_milliseconds time_to_die)
{
	struct s_lonely_simulation	lonely_simulation;

	lonely_simulation.time_to_die = time_to_die;
	lonely_simulation.start_time = time_now();
	pthread_mutex_init(&lonely_simulation.fork, NULL);
	pthread_create(&lonely_simulation.philosopher, NULL, \
		(void *(*)(void *)) lonely_philosopher_routine, \
		(void *) &lonely_simulation);
	pthread_join(lonely_simulation.philosopher, NULL);
	pthread_mutex_destroy(&lonely_simulation.fork);
	return (SIMULATION_SUCCESS);
}
