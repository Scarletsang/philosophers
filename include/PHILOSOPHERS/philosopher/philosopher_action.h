/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_action.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:59:04 by htsang            #+#    #+#             */
/*   Updated: 2023/04/12 23:06:33 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_ACTION_H
# define PHILOSOPHER_ACTION_H

# include "PHILOSOPHERS/time.h"
# include "PHILOSOPHERS/philosopher.h"

void	philosopher_action_print(const struct s_philosopher *philosopher, \
	const char *action);

#endif