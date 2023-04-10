/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:07:08 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/04/10 22:56:14 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "PHILOSOPHERS/time.h"
# include "PHILOSOPHERS/simulation.h"
# include "PHILOSOPHERS/simulation_settings.h"
# include <pthread.h>

struct s_philosopher
{
	const unsigned int					id;
	unsigned int						meals_eaten;
	t_milliseconds						last_meal_time;
	const pthread_mutex_t				*left_fork;
	const pthread_mutex_t				*right_fork;
	const t_milliseconds				*start_time;
	const pthread_mutex_t				*is_printing;
	const struct s_simulation_settings	*simulation_settings;
};

t_simulation_status	simulation_spawn_philosopher(\
const struct s_simulation *simulation, \
const struct s_simulation_settings *settings, unsigned int philosopher_id);

#endif