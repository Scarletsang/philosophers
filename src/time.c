/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:56:38 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/04/19 19:39:42 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/time.h"
#include <sys/time.h>
#include <unistd.h>

t_milliseconds	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

t_milliseconds	time_since(t_milliseconds start_time)
{
	return (time_now() - start_time);
}

void	time_sleep(t_milliseconds duration)
{
	t_milliseconds	start_time;

	start_time = time_now();
	while (time_since(start_time) <= duration)
		usleep(100);
}
