/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:24:47 by htsang            #+#    #+#             */
/*   Updated: 2023/04/19 13:54:21 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

typedef unsigned long long	t_milliseconds;

t_milliseconds	time_now(void);

t_milliseconds	time_since(t_milliseconds start_time);

void			time_sleep(t_milliseconds duration);

#endif