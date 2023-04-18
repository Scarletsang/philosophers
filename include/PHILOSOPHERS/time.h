/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:24:47 by htsang            #+#    #+#             */
/*   Updated: 2023/04/18 22:21:01 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

typedef unsigned long long	t_milliseconds;

t_milliseconds	time_current_get(void);

t_milliseconds	time_since_simulation_get(t_milliseconds start_time);

void			time_sleep(t_milliseconds duration);

#endif