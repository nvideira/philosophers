/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:15:44 by nvideira          #+#    #+#             */
/*   Updated: 2022/09/04 21:57:09 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo *philo, t_args *args)
{
	while (1)
	{
		if (philo->state == EATING)
		{
			philo->state = SLEEPING;
			gettimeofday(&philo->date, NULL);
			printf("%ld: philosopher %d is sleeping.", philo->date, philo->num);
			usleep(args->time_sleep * 1000);
		}
		else if (philo->state == SLEEPING)
		{
			philo->state = THINKING;
			gettimeofday(&philo->date, NULL);
			printf("%ld: philosopher %d is thinking.", philo->date, philo->num);
			usleep(args->time_sleep * 1000);
		}
		else if (philo->state == THINKING)
		{
			philo->state = EATING;
			gettimeofday(&philo->date, NULL);
			printf("%ld: philosopher %d has taken a fork.", philo->date, philo->num);
			printf("%ld: philosopher %d is eating.", philo->date, philo->num);
			usleep(args->time_eat * 1000);
		}
	}
}
