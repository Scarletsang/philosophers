/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:42:14 by htsang            #+#    #+#             */
/*   Updated: 2023/04/12 23:07:09 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/philosopher/philosopher_action.h"
#include <stdio.h>

void	philosopher_action_print(const struct s_philosopher *philosopher, \
	const char *action)
{
	simulation_signal_wait(&philosopher->simulation_states->print_signal);
	printf("%llu %u %s\n", \
		time_since_simulation_get(philosopher->simulation_states->start_time), \
		philosopher->id, action);
	simulation_signal_send(&philosopher->simulation_states->print_signal,
		SIMULATION_SUCCESS);
}
