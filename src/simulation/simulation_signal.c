/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_signal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:11:43 by htsang            #+#    #+#             */
/*   Updated: 2023/04/12 22:43:38 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/simulation/simulation_states.h"

t_simulation_status	simulation_signal_init(\
struct s_simulation_signal *signal)
{
	if (!pthread_mutex_init(&signal->mutex, NULL))
		signal->status = SIMULATION_SUCCESS;
	return (signal->status);
}

t_simulation_status	simulation_signal_wait(\
struct s_simulation_signal *signal)
{
	if (pthread_mutex_lock(&signal->mutex))
		return (SIMULATION_FAILURE);
	return (SIMULATION_SUCCESS);
}

t_simulation_status	simulation_signal_send(\
struct s_simulation_signal *signal, t_simulation_status status)
{
	signal->status = status;
	if (pthread_mutex_unlock(&signal->mutex))
		return (SIMULATION_FAILURE);
	return (SIMULATION_SUCCESS);
}

t_simulation_status	simulation_signal_free(\
const struct s_simulation_signal *signal)
{
	if ((signal->status != SIMULATION_UNINITIALIZED) && \
		pthread_mutex_destroy((pthread_mutex_t *) &signal->mutex))
		return (SIMULATION_FAILURE);
	return (SIMULATION_SUCCESS);
}
