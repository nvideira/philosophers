/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:15:44 by nvideira          #+#    #+#             */
/*   Updated: 2022/09/04 00:37:42 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo *philo, t_args *args, int i)
{
	philo->num = ++i;
	while (1)
	{
		if (philo->state == EATING)
		{
			
			philo->state = SLEEPING;
			usleep(args->time_sleep * 1000);
		}
		else if (philo->state == SLEEPING)
		{
			philo->state = THINKING;
			usleep(args->time_sleep * 1000);
		}
		else if (philo->state == THINKING)
		{
			philo->state = EATING;
			usleep(args->time_eat * 1000);
		}
	}
}
