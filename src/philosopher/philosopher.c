/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:08:26 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/04/18 16:32:15 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/philosopher.h"
#include "PHILOSOPHERS/philosopher/action.h"
#include <stdlib.h>

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
