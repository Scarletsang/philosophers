/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:20:29 by htsang            #+#    #+#             */
/*   Updated: 2023/04/10 22:55:52 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/simulation.h"
#include "PHILOSOPHERS/simulation_settings.h"
#include "PHILOSOPHERS/philosopher.h"
#include <stdlib.h>

int	main(int argc, const char **argv)
{
	const struct s_simulation_settings	settings;
	const struct s_simulation			simulation;
	unsigned int						philosopher_id;

	if (simulation_settings_init((struct s_simulation_settings *) &settings, \
		argc, argv))
		return (EXIT_FAILURE);
	if (simulation_create((struct s_simulation *) &simulation, \
		settings.amount_of_philosophers))
		return (EXIT_FAILURE);
	philosopher_id = 0;
	while (++philosopher_id <= settings.amount_of_philosophers)
	{
		if (simulation_spawn_philosopher(&simulation, &settings, \
			philosopher_id))
		{
			simulation_wait_for_philosophers(&simulation, philosopher_id);
			simulation_destroy(&simulation, settings.amount_of_philosophers);
			return (EXIT_FAILURE);
		}
	}
	simulation_wait_for_philosophers(&simulation, philosopher_id - 1);
	simulation_destroy(&simulation, settings.amount_of_philosophers);
	return (EXIT_SUCCESS);
}
