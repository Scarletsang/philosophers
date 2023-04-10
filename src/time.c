/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:56:38 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/04/10 22:51:28 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/time.h"
#include <sys/time.h>

t_milliseconds	time_get_current(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

t_milliseconds	time_get_since_simulation(t_milliseconds start_time)
{
	return (current_time_in_ms_get() - start_time);
}
