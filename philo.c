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

long	time_elapsed(t_philo *philo)
{
	struct timeval	current_time;
	long			diff;

	gettimeofday(&current_time, NULL);
	diff = (current_time.tv_sec - philo->date.tv_sec) * 1000;
	diff += (current_time.tv_usec - philo->date.tv_usec) / 1000;
	return (diff);
}

int	check_death(t_philo *philo)
{
	if (time_elapsed(philo) - philo->last_meal > philo->args->time_die)
	{
		pthread_mutex_lock(&philo->args->death_trigger);
		printf("%ld: %d died\n", time_elapsed(philo), philo->num);
		pthread_mutex_unlock(&philo->args->death_trigger);
		philo->dead = 1;
		return (1);
	}
	return (0);
}

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
			if (check_death(philo))
				break ;
			philo->state = SLEEPING;
			time = time_elapsed(philo);
			printf("%ld: %d is sleeping.\n", time, philo->num);
			usleep(philo->args->time_sleep * 1000);
		}
		else if (philo->state == SLEEPING)
		{
			if (check_death(philo))
				break ;
			philo->state = THINKING;
			time = time_elapsed(philo);
			printf("%ld: %d is thinking.\n", time, philo->num);
			usleep(philo->args->time_sleep * 1000);
		}
		else if (philo->state == THINKING)
		{
			if (check_death(philo))
				break ;
			time = time_elapsed(philo);
			if (philo->num == philo->args->n_philo)
				grab_forks(philo, philo->num, 1);
			else
				grab_forks(philo, philo->num, philo->num + 1);
			philo->state = EATING;
			time = time_elapsed(philo);
			printf("%ld: %d is eating.\n", time, philo->num);
			usleep(philo->args->time_eat * 1000);
			philo->last_meal = time;
			if (philo->num == philo->args->n_philo)
				drop_forks(philo, philo->num, 1);
			else
				drop_forks(philo, philo->num, philo->num + 1);
		}
	}
	return (NULL);
}
