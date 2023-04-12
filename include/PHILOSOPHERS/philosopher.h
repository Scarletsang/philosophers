/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:07:08 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/04/12 16:38:24 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "PHILOSOPHERS/time.h"
# include "PHILOSOPHERS/simulation.h"
# include "PHILOSOPHERS/simulation/simulation_settings.h"
# include <pthread.h>

struct s_philosopher
{
	const unsigned int					id;
	unsigned int						meals_eaten;
	t_milliseconds						last_meal_time;
	const pthread_mutex_t				*left_fork;
	const pthread_mutex_t				*right_fork;
	struct s_simulation_states			*simulation_states;
	const struct s_simulation_settings	*simulation_settings;
};

void	philosopher_init(struct s_philosopher *philosopher, \
struct s_simulation *simulation, const struct s_simulation_settings *settings, \
unsigned int philosopher_id);

void	*philosopher_routine(struct s_philosopher *philosopher);

#endif