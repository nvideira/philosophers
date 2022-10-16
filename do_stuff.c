/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_stuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:09:14 by nvideira          #+#    #+#             */
/*   Updated: 2022/10/16 21:15:01 by nvideira         ###   ########.fr       */
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
	philo->current_time = time_elapsed(philo);
	if (grab_forks(philo, philo->num - 1,
			philo->num % philo->args->n_philo))
	{
		drop_forks(philo, philo->num - 1,
			philo->num % philo->args->n_philo);
		return (1);
	}
	print_status(philo, EATING);
	philo->last_meal = philo->current_time + (long long)philo->args->time_eat;
	smart_sleep(philo, philo->args->time_eat);
	philo->n_meals--;
	drop_forks(philo, philo->num - 1,
		philo->num % philo->args->n_philo);
	return (0);
}

int	snoring(t_philo *philo)
{
	philo->state = SLEEPING;
	if (check_death(philo))
		return (1);
	smart_sleep(philo, philo->args->time_sleep);
	print_status(philo, SLEEPING);
	return (0);
}
