/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:07:08 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/04/19 13:46:56 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "PHILOSOPHERS/time.h"
# include "PHILOSOPHERS/simulation/states.h"
# include "PHILOSOPHERS/simulation/settings.h"
# include <pthread.h>

struct s_philosopher
{
	const unsigned int					id;
	unsigned int						meals_eaten;
	t_simulation_status					(*action)(struct s_philosopher *);
	t_milliseconds						*last_meal_time;
	pthread_mutex_t						*left_fork;
	pthread_mutex_t						*right_fork;
	struct s_simulation_states			*simulation_states;
	const struct s_simulation_settings	*simulation_settings;
};

typedef t_simulation_status	(*t_philosopher_action)(\
struct s_philosopher *philosopher);

void	*philosopher_routine(struct s_philosopher *philosopher);

////////////////////////////////////////////
////////////      printer      /////////////
////////////////////////////////////////////

void	philosopher_action_print(const struct s_philosopher *philosopher, \
	const char *action);

void	simulation_philosopher_status_print(t_milliseconds time, \
unsigned int philosopher_id, const char *action);

#endif