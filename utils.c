/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:43:41 by nvideira          #+#    #+#             */
/*   Updated: 2022/10/08 20:08:34 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	int	swap;

	if (right < left)
	{
		swap = left;
		left = right;
		right = swap;
	}
	pthread_mutex_lock(&philo->args->fork[left]);
	pthread_mutex_lock(&philo->args->fork[right]);
	print_status(philo, FORKING);
	return (0);
}

void	drop_forks(t_philo *philo, int left, int right, int flag)
{
	int	swap;

	if (right < left)
	{
		swap = left;
		left = right;
		right = swap;
	}
	pthread_mutex_unlock(&philo->args->fork[left]);
	pthread_mutex_unlock(&philo->args->fork[right]);
	if (!flag)
		print_status(philo, UNFORKING);
}
