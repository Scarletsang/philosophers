/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:29:29 by htsang            #+#    #+#             */
/*   Updated: 2023/04/17 21:31:09 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REAPER_H
# define REAPER_H

# include "PHILOSOPHERS/time.h"
# include "PHILOSOPHERS/simulation.h"
# include "PHILOSOPHERS/simulation/simulation_settings.h"

struct s_reaper
{
	t_milliseconds						*philosophers_last_meal_times;
	struct s_simulation_states			*simulation_states;
	const struct s_simulation_settings	*simulation_settings;
};

void	reaper_init(struct s_reaper *reaper, struct s_simulation *simulation, \
const struct s_simulation_settings *settings);

void	*reaper_routine(struct s_reaper *reaper);

#endif