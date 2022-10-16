/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:57:44 by nvideira          #+#    #+#             */
/*   Updated: 2022/10/16 23:21:32 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->args->chomp);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->args->chomp);
		return ;
	}
	philo->c_time = time_elapsed(philo);
	if (status == EATING)
		printf("%lld: %d is eating.\n", philo->c_time, philo->num);
	else if (status == SLEEPING)
		printf("%lld: %d is sleeping.\n", philo->c_time, philo->num);
	else if (status == THINKING)
		printf("%lld: %d is thinking.\n", philo->c_time, philo->num);
	else if (status == FORKING)
	{
		printf("%lld: %d has taken a fork.\n", philo->c_time, philo->num);
		printf("%lld: %d has taken a fork.\n", philo->c_time, philo->num);
	}
	else if (status == UNFORKING)
	{
		printf("%lld: %d dropped a fork.\n", philo->c_time, philo->num);
		printf("%lld: %d dropped a fork.\n", philo->c_time, philo->num);
	}
	pthread_mutex_unlock(&philo->args->chomp);
}
