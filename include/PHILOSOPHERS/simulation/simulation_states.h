/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_states.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:15:36 by htsang            #+#    #+#             */
/*   Updated: 2023/04/12 00:46:43 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_STATES_H
# define SIMULATION_STATES_H

# include "PHILOSOPHERS/time.h"
# include <pthread.h>

typedef enum e_simulation_status
{
	SIMULATION_SUCCESS,
	SIMULATION_FAILURE,
	SIMULATION_UNINITIALIZED
}				t_simulation_status;

struct s_simulation_signal
{
	pthread_mutex_t		mutex;
	t_simulation_status	status;
};

struct s_simulation_states
{
	t_milliseconds				start_time;
	struct s_simulation_signal	print_signal;
	struct s_simulation_signal	start_signal;
};

//////////////////////////////////////////////////
/////////      simulation states      ////////////
//////////////////////////////////////////////////

t_simulation_status	simulation_states_init(struct s_simulation_states *states);

t_simulation_status	simulation_states_free(\
const struct s_simulation_states *states);

//////////////////////////////////////////////////
/////////      simulation signal      ////////////
//////////////////////////////////////////////////

t_simulation_status	simulation_signal_send(\
struct s_simulation_signal *signal, t_simulation_status status);

t_simulation_status	simulation_signal_free(\
const struct s_simulation_signal *signal);

#endif