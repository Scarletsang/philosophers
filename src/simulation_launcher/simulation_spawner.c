/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_spawner.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:15:27 by htsang            #+#    #+#             */
/*   Updated: 2023/04/24 16:10:09 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/simulation_launcher.h"

static void	philosopher_init(struct s_philosopher *philosopher, \
struct s_simulation *simulation, const struct s_simulation_settings *settings, \
unsigned int philosopher_id)
{
	*(unsigned int *) &philosopher->id = philosopher_id;
	philosopher->meals_eaten = 0;
	philosopher->last_meal_time = simulation->philosophers_last_meal_times + \
		philosopher_id - 1;
	if (philosopher_id == 1)
		philosopher->left_fork = simulation->forks + \
			settings->amount_of_philosophers - 1;
	else
		philosopher->left_fork = simulation->forks + philosopher_id - 2;
	philosopher->right_fork = simulation->forks + philosopher_id - 1;
	philosopher->simulation_states = &simulation->states;
	philosopher->simulation_settings = settings;
}

t_simulation_status	simulation_spawn_philosopher(\
struct s_simulation *simulation, \
const struct s_simulation_settings *settings, unsigned int philosopher_id)
{
	struct s_philosopher	*philosopher;

	philosopher = malloc(sizeof(struct s_philosopher));
	if (!philosopher)
		return (SIMULATION_FAILURE);
	philosopher_init(philosopher, simulation, settings, philosopher_id);
	if (pthread_create(&simulation->philosophers[philosopher_id - 1], NULL, \
		(void *(*)(void *)) philosopher_routine, (void *) philosopher))
	{
		free(philosopher);
		return (SIMULATION_FAILURE);
	}
	return (SIMULATION_SUCCESS);
}

static void	reaper_init(struct s_reaper *reaper, \
struct s_simulation *simulation, \
const struct s_simulation_settings *settings)
{
	reaper->philosophers_last_meal_times = \
		simulation->philosophers_last_meal_times;
	reaper->simulation_states = &simulation->states;
	reaper->simulation_settings = settings;
}

t_simulation_status	simulation_spawn_reaper(\
struct s_simulation *simulation, \
const struct s_simulation_settings *settings)
{
	struct s_reaper	*reaper;

	reaper = malloc(sizeof(struct s_reaper));
	if (!reaper)
		return (SIMULATION_FAILURE);
	reaper_init(reaper, simulation, settings);
	if (pthread_create(&simulation->reaper, NULL, \
		(void *(*)(void *)) reaper_routine, (void *) reaper))
	{
		free(reaper);
		return (SIMULATION_FAILURE);
	}
	return (SIMULATION_SUCCESS);
}
