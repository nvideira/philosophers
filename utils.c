/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:43:41 by nvideira          #+#    #+#             */
/*   Updated: 2022/09/28 18:17:17 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *str)
{
	printf("Error: %s\n", str);
	exit(1);
}

void	init_mutex(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		if (pthread_mutex_init(&(args->fork[i]), NULL))
			ft_error("Mutex init failed.");
		i++;
	}
	if (pthread_mutex_init(&(args->death_trigger), NULL)
		|| pthread_mutex_init(&(args->chomp), NULL))
		ft_error("Mutex init failed.");
}

void	destroy_mutex(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		if (pthread_mutex_destroy(&(args->fork[i])))
			printf("ForkMutex destroy failed.\n");
		else
			printf("ForkMutex destroyed successfully\n");
		i++;
	}
	if (pthread_mutex_destroy(&(args->death_trigger))
		|| pthread_mutex_destroy(&(args->chomp)))
		printf("DeathMutex destroy failed.\n");
	else
		printf("DeathMutex destroyed successfully\n");
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
	// if (philo->num % 2 == 1 && !philo->args->dead)
	// {
		pthread_mutex_lock(&philo->args->fork[left]);
		pthread_mutex_lock(&philo->args->fork[right]);
	// }
	// else if (!philo->args->dead)
	// {
	// 	pthread_mutex_lock(&philo->args->fork[right]);
	// 	pthread_mutex_lock(&philo->args->fork[left]);
	// }
	// if (check_death(philo) || philo->args->dead)
	// {
	// 	pthread_mutex_unlock(&philo->args->fork[left]);
	// 	pthread_mutex_unlock(&philo->args->fork[right]);
	// 	return (1);
	// }
	print_status(philo, FORKING, philo->args);
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
		print_status(philo, UNFORKING, philo->args);
}
