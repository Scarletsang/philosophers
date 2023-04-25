/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_launcher.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:59:04 by htsang            #+#    #+#             */
/*   Updated: 2023/04/24 16:10:25 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_LAUNCHER_H
# define SIMULATION_LAUNCHER_H

# include "PHILOSOPHERS/time.h"
# include "PHILOSOPHERS/simulation.h"
# include "PHILOSOPHERS/simulation/settings.h"
# include "PHILOSOPHERS/simulation/states.h"
# include "PHILOSOPHERS/philosopher.h"
# include "PHILOSOPHERS/reaper.h"
# include <pthread.h>
# include <stdlib.h>

typedef unsigned int	t_philosophers_amount;

t_simulation_status		simulation_spawn_philosopher(\
struct s_simulation *simulation, \
const struct s_simulation_settings *settings, unsigned int philosopher_id);

t_simulation_status		simulation_spawn_reaper(\
struct s_simulation *simulation, \
const struct s_simulation_settings *settings);

t_philosophers_amount	simulation_start(struct s_simulation *simulation, \
const struct s_simulation_settings *settings);

int						philosophers_amount_meet_expectation(\
t_philosophers_amount philosopher_amount, \
const struct s_simulation_settings *settings);

//////////////////////////////////////////////
/////////    lonely simulation    ////////////
//////////////////////////////////////////////

struct s_lonely_simulation
{
	pthread_t		philosopher;
	pthread_mutex_t	fork;
	t_milliseconds	start_time;
	t_milliseconds	time_to_die;
};

void					*lonely_philosopher_routine(\
struct s_lonely_simulation *simulation);

t_simulation_status		lonely_simulation_start(t_milliseconds time_to_die);

#endif