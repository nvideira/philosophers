/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_stuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:09:14 by nvideira          #+#    #+#             */
/*   Updated: 2022/10/10 10:10:03 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	brainstorming(t_philo *philo)
{
	if (check_death(philo))
		return (1);
	philo->state = THINKING;
	print_status(philo, THINKING);
	return (0);
}

int	eating(t_philo *philo)
{
	philo->state = EATING;
	if (check_death(philo))
		return (1);
	grab_forks(philo, philo->num - 1,
		philo->num % philo->args->n_philo);
	pthread_mutex_lock(&philo->args->chomp);
	if (check_death(philo))
	{
		drop_forks(philo, philo->num - 1,
			philo->num % philo->args->n_philo, 1);
		pthread_mutex_unlock(&philo->args->chomp);
		return (1);
	}
	print_status(philo, EATING);
	usleep(philo->args->time_eat * 1000);
	philo->last_meal = time_elapsed(philo);
	philo->n_meals--;
	pthread_mutex_unlock(&philo->args->chomp);
	drop_forks(philo, philo->num - 1,
		philo->num % philo->args->n_philo, 0);
	return (0);
}

int	snoring(t_philo *philo)
{
	philo->state = SLEEPING;
	if (check_death(philo))
		return (1);
	print_status(philo, SLEEPING);
	usleep(philo->args->time_sleep * 1000);
	return (0);
}
