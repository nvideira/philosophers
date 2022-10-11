/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:15:44 by nvideira          #+#    #+#             */
/*   Updated: 2022/10/10 10:09:58 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_elapsed(t_philo *philo)
{
	struct timeval	current_time;
	long long		diff;

	gettimeofday(&current_time, NULL);
	diff = current_time.tv_sec * 1000;
	diff += current_time.tv_usec / 1000;
	diff -= philo->start_time;
	return (diff);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->death_trigger);
	if (philo->args->dead == 1)
	{
		pthread_mutex_unlock(&philo->args->death_trigger);
		return (1);
	}
	if (time_elapsed(philo) - philo->last_meal > philo->args->time_die)
	{
		philo->state = DEAD;
		printf("%lld: %d died.\n", time_elapsed(philo), philo->num);
		philo->args->dead = 1;
		pthread_mutex_unlock(&philo->args->death_trigger);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->death_trigger);
	return (0);
}

t_philo	philo_create(int num, t_args *args)
{
	t_philo			philo;
	struct timeval	time;

	philo.num = num;
	philo.state = THINKING;
	philo.args = args;
	gettimeofday(&time, NULL);
	philo.start_time = (time.tv_sec * 1000);
	philo.start_time += (time.tv_usec / 1000);
	philo.n_meals = args->limit;
	philo.last_meal = 0;
	return (philo);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (philo->n_meals)
	{
		if (philo->state == EATING)
		{
			if (snoring(philo))
				break ;
		}
		else if (philo->state == SLEEPING)
		{
			if (brainstorming(philo))
				break ;
		}
		else if (philo->state == THINKING)
		{
			if (eating(philo))
				break ;
		}
		else
			break ;
	}
	return (NULL);
}
