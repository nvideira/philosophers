/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:15:44 by nvideira          #+#    #+#             */
/*   Updated: 2022/08/31 19:06:55 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(t_philo *philo)
{
	while (1)
	{
		if (philo->state == EATING)
		{
			philo->state = SLEEPING;
			usleep(philo->time_sleep * 1000);
		}
		else if (philo->state == SLEEPING)
		{
			philo->state = THINKING;
			usleep(philo->time_sleep * 1000);
		}
		else if (philo->state == THINKING)
		{
			philo->state = EATING;
			usleep(philo->time_eat * 1000);
		}
	}
}
