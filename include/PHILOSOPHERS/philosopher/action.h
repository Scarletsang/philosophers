/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:59:04 by htsang            #+#    #+#             */
/*   Updated: 2023/04/18 16:40:43 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTION_H
# define ACTION_H

# include "PHILOSOPHERS/philosopher.h"
# include "PHILOSOPHERS/simulation/states.h"

t_simulation_status	philosopher_take_forks(struct s_philosopher *philosopher);

t_simulation_status	philosopher_eat(struct s_philosopher *philosopher);

t_simulation_status	philosopher_think(struct s_philosopher *philosopher);

t_simulation_status	philosopher_put_forks(struct s_philosopher *philosopher);

t_simulation_status	philosopher_sleep(struct s_philosopher *philosopher);

#endif