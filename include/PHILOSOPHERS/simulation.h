/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:20:19 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/04/10 22:57:43 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "PHILOSOPHERS/time.h"
# include <pthread.h>

typedef enum e_simulation_status
{
	SIMULATION_SUCCESS,
	SIMULATION_FAILURE
}				t_simulation_status;

struct s_simulation
{
	pthread_t		*philosophers;
	pthread_mutex_t	*forks;
	t_milliseconds	start_time;
	pthread_mutex_t	is_printing;
};

t_simulation_status	simulation_create(struct s_simulation *simulation, \
unsigned int amount_of_philosophers);

void				simulation_wait_for_philosophers(\
const struct s_simulation *simulation, unsigned int amount_of_philosophers);

void				simulation_destroy(\
const struct s_simulation *simulation, unsigned int amount_of_philosophers);

#endif