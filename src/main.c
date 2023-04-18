/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:20:29 by htsang            #+#    #+#             */
/*   Updated: 2023/04/18 16:37:37 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/simulation.h"
#include "PHILOSOPHERS/simulation/settings.h"
#include "PHILOSOPHERS/simulation_launcher.h"
#include <stdlib.h>

void	bury_dead_philosopher(struct s_simulation *simulation, \
unsigned int *dead_philosopher_id)
{
	if (dead_philosopher_id)
	{
		simulation_philosopher_status_print(\
			&simulation->states, *dead_philosopher_id, "died");
		free(dead_philosopher_id);
	}
}

int	main(int argc, const char **argv)
{
	const struct s_simulation_settings	settings;
	struct s_simulation					simulation;
	t_philosophers_amount				philosophers_amount;
	unsigned int						*dead_philosopher_id;

	if (simulation_settings_init((struct s_simulation_settings *) &settings, \
		argc, argv))
		return (EXIT_FAILURE);
	if (simulation_init(&simulation, settings.amount_of_philosophers))
		return (EXIT_FAILURE);
	philosophers_amount = simulation_start(&simulation, &settings);
	dead_philosopher_id = simulation_wait_for_reaper(&simulation);
	if (philosophers_amount_meet_expectation(philosophers_amount, &settings))
		simulation_wait_for_philosophers(&simulation, \
			settings.amount_of_philosophers);
	else
		simulation_wait_for_philosophers(&simulation, philosophers_amount);
	bury_dead_philosopher(&simulation, dead_philosopher_id);
	return (simulation_terminate(&simulation, settings.amount_of_philosophers));
}
