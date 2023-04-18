/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:21:42 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/04/18 21:32:36 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/simulation/settings.h"
#include <limits.h>

static inline int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static t_parser_exit_code	as_milliseconds(void *parse_to, \
const char *parse_from)
{
	if (*(t_milliseconds *)parse_to > (ULLONG_MAX - (*parse_from - '0')) / 10)
		return (PARSE_FAILURE);
	*(t_milliseconds *)parse_to = *(t_milliseconds *)parse_to * 10 + \
		(*parse_from - '0');
	return (PARSE_SUCCESS);
}

static t_parser_exit_code	as_amount(void *parse_to, const char *parse_from)
{
	if (*(unsigned int *)parse_to > (UINT_MAX - (*parse_from - '0')) / 10)
		return (PARSE_FAILURE);
	*(unsigned int *)parse_to = *(unsigned int *)parse_to * 10 + \
		(*parse_from - '0');
	return (PARSE_SUCCESS);
}

static t_parser_exit_code	number_parse(void *parse_to, \
const char *parse_from, \
t_parser_exit_code (*parse_number_func)(void *, const char *))
{
	while (*parse_from)
	{
		if (!is_digit(*parse_from))
			return (PARSE_FAILURE);
		if (parse_number_func(parse_to, parse_from))
			return (PARSE_FAILURE);
		parse_from++;
	}
	return (PARSE_SUCCESS);
}

t_parser_exit_code	simulation_settings_init(\
struct s_simulation_settings *settings, int argc, const char **argv)
{
	if (argc != 5 && argc != 6)
		return (PARSE_FAILURE);
	*settings = (struct s_simulation_settings){0, 0, 0, 0, 0};
	if (number_parse(&settings->amount_of_philosophers, argv[1], as_amount) || \
		number_parse(&settings->time_to_die, argv[2], as_milliseconds) || \
		number_parse(&settings->time_to_eat, argv[3], as_milliseconds) || \
		number_parse(&settings->time_to_sleep, argv[4], as_milliseconds))
		return (PARSE_FAILURE);
	if (argc == 6)
	{
		if (number_parse(&settings->amount_of_times_each_philosopher_must_eat, \
			argv[5], as_amount))
			return (PARSE_FAILURE);
	}
	else
		settings->amount_of_times_each_philosopher_must_eat = UINT_MAX;
	return (PARSE_SUCCESS);
}
