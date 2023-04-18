/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:38:24 by htsang            #+#    #+#             */
/*   Updated: 2023/04/18 21:53:53 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/simulation/states.h"

t_simulation_status	simulation_states_init(struct s_simulation_states *states)
{
	states->start_time = 0;
	states->print_signal.status = SIMULATION_UNINITIALIZED;
	states->start_signal.status = SIMULATION_UNINITIALIZED;
	states->kill_signal.status = SIMULATION_UNINITIALIZED;
	return (simulation_signal_init(&states->print_signal) || \
			simulation_signal_init(&states->start_signal) || \
			simulation_signal_init(&states->kill_signal));
}

t_simulation_status	simulation_states_free(\
const struct s_simulation_states *states)
{
	t_simulation_status	status;

	status = SIMULATION_SUCCESS;
	if (simulation_signal_free(&states->print_signal))
		status = SIMULATION_FAILURE;
	if (simulation_signal_free(&states->start_signal))
		status = SIMULATION_FAILURE;
	if (simulation_signal_free(&states->kill_signal))
		status = SIMULATION_FAILURE;
	return (status);
}
