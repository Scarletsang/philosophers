/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:24:47 by htsang            #+#    #+#             */
/*   Updated: 2023/04/19 14:25:28 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# include "PHILOSOPHERS/time.h"

typedef enum e_parser_exit_code
{
	PARSE_SUCCESS,
	PARSE_FAILURE
}				t_parser_exit_code;

struct	s_simulation_settings
{
	t_milliseconds	time_to_die;
	t_milliseconds	time_to_eat;
	t_milliseconds	time_to_sleep;
	unsigned int	amount_of_philosophers;
	unsigned int	amount_of_meals_must_eat;
};

t_parser_exit_code	simulation_settings_init(\
struct s_simulation_settings *settings, int argc, const char **argv);

#endif