/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:20:29 by htsang            #+#    #+#             */
/*   Updated: 2023/04/12 00:37:29 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/simulation.h"
#include "PHILOSOPHERS/simulation/simulation_settings.h"
#include "PHILOSOPHERS/simulation_launcher.h"
#include <stdlib.h>

int	main(int argc, const char **argv)
{
	const struct s_simulation_settings	settings;
	struct s_simulation					simulation;
	t_philosophers_amount				philosophers_amount;

	if (simulation_settings_init((struct s_simulation_settings *) &settings, \
		argc, argv))
		return (EXIT_FAILURE);
	if (simulation_init(&simulation, settings.amount_of_philosophers))
		return (EXIT_FAILURE);
	philosophers_amount = simulation_start(&simulation, &settings);
	if (philosophers_amount_meet_expectation(philosophers_amount, &settings))
	{
		simulation_wait_for_philosophers(&simulation, \
			settings.amount_of_philosophers);
		simulation_terminate(&simulation, settings.amount_of_philosophers);
		return (EXIT_SUCCESS);
	}
	simulation_wait_for_philosophers(&simulation, philosophers_amount);
	simulation_terminate(&simulation, settings.amount_of_philosophers);
	return (EXIT_FAILURE);
}
