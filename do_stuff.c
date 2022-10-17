/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_stuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:09:14 by nvideira          #+#    #+#             */
/*   Updated: 2022/10/16 23:21:32 by nvideira         ###   ########.fr       */
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
	philo->c_time = time_elapsed(philo);
	if (check_death(philo))
		return (1);
	if (grab_forks(philo, philo->num - 1,
			philo->num % philo->args->n_philo))
	{
		drop_forks(philo, philo->num - 1,
			philo->num % philo->args->n_philo);
		return (1);
	}
	print_status(philo, EATING);
	philo->last_meal = time_elapsed(philo);
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
	print_status(philo, SLEEPING);
	smart_sleep(philo, philo->args->time_sleep);
	return (0);
}
