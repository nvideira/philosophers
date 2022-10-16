/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:43:41 by nvideira          #+#    #+#             */
/*   Updated: 2022/10/16 21:10:30 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_sleep(t_philo *philo, int time)
{
	long long	start_time;

	start_time = time_elapsed(philo);
	while ((time_elapsed(philo) - start_time < time) && !check_death(philo))
		usleep(2000);
}

int	init_mutex(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		if (pthread_mutex_init(&(args->fork[i]), NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&(args->death_trigger), NULL)
		|| pthread_mutex_init(&(args->chomp), NULL))
		return (0);
	return (1);
}

void	destroy_mutex(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		if (pthread_mutex_destroy(&(args->fork[i])))
			printf("Fork Mutex destroy failed.\n");
		i++;
	}
	if (pthread_mutex_destroy(&(args->death_trigger))
		|| pthread_mutex_destroy(&(args->chomp)))
		printf("Death & Chomp Mutex destroy failed.\n");
}

int	grab_forks(t_philo *philo, int left, int right)
{
	if (philo->num % 2 == 1)
	{
		pthread_mutex_lock(&philo->args->fork[left]);
		pthread_mutex_lock(&philo->args->fork[right]);
	}
	else
	{
		pthread_mutex_lock(&philo->args->fork[right]);
		pthread_mutex_lock(&philo->args->fork[left]);
	}
	if (time_elapsed(philo) - philo->last_meal > philo->args->time_die)
	{
		pthread_mutex_lock(&philo->args->death_trigger);
		philo->state = DEAD;
		philo->args->dead = 1;
		printf("%lld: %d died.\n", philo->current_time + philo->args->time_die,
			philo->num);
		pthread_mutex_unlock(&philo->args->death_trigger);
		return (1);
	}
	print_status(philo, FORKING);
	return (0);
}

void	drop_forks(t_philo *philo, int left, int right)
{
	if (philo->num % 2 == 1)
	{
		pthread_mutex_unlock(&philo->args->fork[left]);
		pthread_mutex_unlock(&philo->args->fork[right]);
	}
	else
	{
		pthread_mutex_unlock(&philo->args->fork[right]);
		pthread_mutex_unlock(&philo->args->fork[left]);
	}
}
