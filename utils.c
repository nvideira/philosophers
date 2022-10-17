/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:43:41 by nvideira          #+#    #+#             */
/*   Updated: 2022/10/17 18:47:25 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_sleep(t_philo *philo, int time)
{
	long long	start_time;

	start_time = time_elapsed(philo);
	while ((time_elapsed(philo) - start_time < time) && !check_death(philo))
		usleep(20);
}

int	init_mutex(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		if (pthread_mutex_init(&(args->fork[i]), NULL))
			return (0);
		args->f_bool[i] = 0;
		i++;
	}
	args->f_bool[i] = '\0';
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
