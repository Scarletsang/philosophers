/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:42:14 by htsang            #+#    #+#             */
/*   Updated: 2023/04/18 16:26:30 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/philosopher.h"
#include <stdio.h>

void	philosopher_action_print(const struct s_philosopher *philosopher, \
	const char *action)
{
	simulation_signal_wait(&philosopher->simulation_states->print_signal);
	simulation_philosopher_status_print(philosopher->simulation_states, \
		philosopher->id, action);
	simulation_signal_respond(&philosopher->simulation_states->print_signal,
		SIMULATION_SUCCESS);
}

void	simulation_philosopher_status_print(\
struct s_simulation_states *states, unsigned int philosopher_id, \
const char *action)
{
	printf("%-6llu %-4u %s\n", \
		time_since_simulation_get(states->start_time), \
		philosopher_id, action);
}
