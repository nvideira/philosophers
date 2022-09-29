/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:15:44 by nvideira          #+#    #+#             */
/*   Updated: 2022/09/28 18:22:37 by nvideira         ###   ########.fr       */
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
		return (1);
	if (time_elapsed(philo) - philo->last_meal > philo->args->time_die)
	{
		philo->state = DEAD;
		print_status(philo, DEAD, philo->args);
		philo->args->dead = 1;
		return (1);
	}
	pthread_mutex_unlock(&philo->args->death_trigger);
	return (0);
}

t_philo philo_create(int num, t_args *args)
{
	t_philo 		philo;
	struct timeval	time;

	philo.num = num;
	philo.state = THINKING;
	philo.args = args;
	gettimeofday(&time, NULL);
	philo.start_time = (time.tv_sec * 1000);
	philo.start_time += (time.tv_usec / 1000);
	philo.n_meals = args->limit;
	philo.last_meal = philo.start_time;
	return (philo);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	t_args		*args;

	philo = (t_philo *)arg;
	args = philo->args;
	while (philo->n_meals)
	{
		if (philo->state == EATING)
		{
			if (check_death(philo))
				break ;
			philo->state = SLEEPING;
			before_print(philo, SLEEPING, philo->args);
			usleep(philo->args->time_sleep * 1000);
		}
		else if (philo->state == SLEEPING)
		{
			if (check_death(philo))
				break ;
			philo->state = THINKING;
			before_print(philo, THINKING, philo->args);
		}
		else if (philo->state == THINKING)
		{
			if (check_death(philo))
				break ;
			if (grab_forks(philo, philo->num - 1, philo->num % philo->args->n_philo))
				break ;
			philo->state = EATING;
			before_print(philo, EATING, philo->args);
			usleep(philo->args->time_eat * 1000);
			philo->last_meal = time_elapsed(philo);
			philo->n_meals--;
			drop_forks(philo, philo->num - 1, philo->num % philo->args->n_philo);
		}
		else
			break ;
	}
	printf("dead: %d\n", philo->args->dead);
	pthread_mutex_unlock(&philo->args->death_trigger);
	pthread_mutex_unlock(&args->fork[philo->num - 1]);
	pthread_mutex_unlock(&args->fork[philo->num % philo->args->n_philo]);
	//free(philo);
	return (NULL);
}
