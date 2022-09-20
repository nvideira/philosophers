/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:15:44 by nvideira          #+#    #+#             */
/*   Updated: 2022/09/20 17:58:23 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo philo_create(int num, t_args args)
{
	t_philo philo;

	philo.num = num;
	philo.state = THINKING;
	philo.args = &args;
	philo.fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	// if (pthread_mutex_init(philo.args->fork, NULL) != 0)
	// 	ft_error("Mutex init failed.");
	return (philo);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->state == EATING)
		{
			philo->state = SLEEPING;
			gettimeofday(&philo->date, NULL);
			printf("%ld: %d is sleeping.\n", philo->date.tv_usec, philo->num);
			usleep(philo->args->time_sleep * 1000);
		}
		else if (philo->state == SLEEPING)
		{
			philo->state = THINKING;
			gettimeofday(&philo->date, NULL);
			printf("%ld: %d is thinking.\n", philo->date.tv_usec, philo->num);
			usleep(philo->args->time_sleep * 1000);
		}
		else if (philo->state == THINKING)
		{
			philo->state = EATING;
			gettimeofday(&philo->date, NULL);
			printf("%ld: %d has taken a fork.\n", philo->date.tv_usec, philo->num);
			printf("%ld: %d is eating.\n", philo->date.tv_usec, philo->num);
			usleep(philo->args->time_eat * 1000);
		}
	}
}
