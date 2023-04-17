/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_launcher.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:59:04 by htsang            #+#    #+#             */
/*   Updated: 2023/04/17 17:31:51 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_LAUNCHER_H
# define SIMULATION_LAUNCHER_H

# include "PHILOSOPHERS/time.h"
# include "PHILOSOPHERS/simulation.h"
# include "PHILOSOPHERS/simulation/simulation_settings.h"
# include "PHILOSOPHERS/simulation/simulation_states.h"
# include "PHILOSOPHERS/philosopher.h"
# include "PHILOSOPHERS/reaper.h"
# include <pthread.h>
# include <stdlib.h>

typedef unsigned int	t_philosophers_amount;

t_philosophers_amount	simulation_start(struct s_simulation *simulation, \
const struct s_simulation_settings *settings);

int						philosophers_amount_meet_expectation(\
t_philosophers_amount philosopher_amount, \
const struct s_simulation_settings *settings);

#endif