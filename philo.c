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

int	time_elapsed(t_philo *philo)
{
	struct timeval	current_time;
	long			diff;

	gettimeofday(&current_time, NULL);
	diff = (current_time.tv_usec - philo->date.tv_usec);
	return (diff);
}

// void	check_death(t_philo *philo)
// {
	
// }

t_philo philo_create(int num, t_args *args)
{
	t_philo philo;

	philo.num = num;
	philo.state = THINKING;
	philo.dead = 0;
	philo.args = args;
	gettimeofday(&philo.start_time, NULL);
	return (philo);
}

void	*routine(void *arg)
{
	t_philo *philo;
	long time;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->state == EATING)
		{
			philo->state = SLEEPING;
			time = time_elapsed(philo);
			printf("%ld: %d is sleeping.\n", time, philo->num);
			usleep(philo->args->time_sleep * 1000);
		}
		else if (philo->state == SLEEPING)
		{
			philo->state = THINKING;
			time = time_elapsed(philo);
			printf("%ld: %d is thinking.\n", time, philo->num);
			usleep(philo->args->time_sleep * 1000);
		}
		else if (philo->state == THINKING)
		{
			time = time_elapsed(philo);
			pthread_mutex_lock(philo->args->fork);
			printf("%ld: %d has taken a fork.\n", time, philo->num);
			//pthread_mutex_lock(philo->args->left);
			//printf("%ld: %d has taken a fork.\n", philo->date.tv_usec, philo->num);
			philo->state = EATING;
			time = time_elapsed(philo);
			printf("%ld: %d is eating.\n", time, philo->num);
			usleep(philo->args->time_eat * 1000);
			pthread_mutex_unlock(philo->args->fork);
			time = time_elapsed(philo);
			printf("%ld: %d put down a fork.\n", time, philo->num);
			//pthread_mutex_unlock(philo->args->left);
		}
	}
}
