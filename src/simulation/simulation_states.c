/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_states.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:38:24 by htsang            #+#    #+#             */
/*   Updated: 2023/04/12 00:47:43 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/simulation/simulation_states.h"

static t_simulation_status	simulation_signal_init(\
struct s_simulation_signal *signal)
{
	if (!pthread_mutex_init(&signal->mutex, NULL))
		signal->status = SIMULATION_SUCCESS;
	return (signal->status);
}

t_simulation_status	simulation_signal_send(\
struct s_simulation_signal *signal, t_simulation_status status)
{
	signal->status = status;
	return (pthread_mutex_unlock(&signal->mutex));
}

t_simulation_status	simulation_signal_free(\
const struct s_simulation_signal *signal)
{
	if (signal->status != SIMULATION_UNINITIALIZED)
		return (pthread_mutex_destroy((pthread_mutex_t *) &signal->mutex));
	return (SIMULATION_SUCCESS);
}

t_simulation_status	simulation_states_init(struct s_simulation_states *states)
{
	states->start_time = 0;
	states->print_signal.status = SIMULATION_UNINITIALIZED;
	states->start_signal.status = SIMULATION_UNINITIALIZED;
	return (simulation_signal_init(&states->print_signal) || \
			simulation_signal_init(&states->start_signal));
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
	return (status);
}
