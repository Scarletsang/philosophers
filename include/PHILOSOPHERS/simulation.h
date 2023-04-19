/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:20:19 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/04/19 13:42:54 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "PHILOSOPHERS/time.h"
# include "PHILOSOPHERS/simulation/states.h"
# include "PHILOSOPHERS/reaper.h"
# include <pthread.h>
# include <stdlib.h>

struct s_simulation
{
	pthread_t					*philosophers;
	t_milliseconds				*philosophers_last_meal_times;
	pthread_t					reaper;
	pthread_mutex_t				*forks;
	struct s_simulation_states	states;
};

///////////////////////////////////////////
/////////      simulation      ////////////
///////////////////////////////////////////

t_simulation_status		simulation_init(struct s_simulation *simulation, \
unsigned int amount_of_philosophers);

struct s_reaper_report	*simulation_wait_for_reaper(\
struct s_simulation *simulation);

t_simulation_status		simulation_wait_for_philosophers(\
struct s_simulation *simulation, unsigned int amount_of_philosophers);

t_simulation_status		simulation_terminate(\
const struct s_simulation *simulation, unsigned int amount_of_philosophers);

#endif