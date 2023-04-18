/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:56:38 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/04/18 22:28:51 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/time.h"
#include <sys/time.h>
#include <unistd.h>

t_milliseconds	time_current_get(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

t_milliseconds	time_since_simulation_get(t_milliseconds start_time)
{
	return (time_current_get() - start_time);
}

void	time_sleep(t_milliseconds duration)
{
	usleep(duration * 1000);
	// t_milliseconds	start_time;

	// start_time = time_current_get();
	// while ((time_current_get() - start_time) <= duration)
	// 	usleep(10);
}
