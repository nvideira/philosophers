/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:46:43 by nvideira          #+#    #+#             */
/*   Updated: 2022/10/17 18:47:52 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	grab_forks(t_philo *philo, int left, int right)
{
	while (philo->n_forks < 2)
	{
		if (!check_death(philo))
			take_fork(philo, left);
		if (!check_death(philo))
			take_fork(philo, right);
		if (check_death(philo))
			return (1);
	}
	print_status(philo, FORKING);
	return (0);
}

void	take_fork(t_philo *philo, int side)
{
	pthread_mutex_lock(&philo->args->fork[side]);
	if (philo->args->f_bool[side] == 0)
	{
		philo->args->f_bool[side] = 1;
		philo->n_forks++;
	}
	pthread_mutex_unlock(&philo->args->fork[side]);
}

void	drop_forks(t_philo *philo, int left, int right)
{
	pthread_mutex_lock(&philo->args->fork[left]);
	philo->args->f_bool[left] = 0;
	pthread_mutex_unlock(&philo->args->fork[left]);
	pthread_mutex_lock(&philo->args->fork[right]);
	philo->args->f_bool[right] = 0;
	pthread_mutex_unlock(&philo->args->fork[right]);
	philo->n_forks = 0;
}
