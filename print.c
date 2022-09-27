/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:57:44 by nvideira          #+#    #+#             */
/*   Updated: 2022/09/27 17:57:07 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_status(t_philo *philo, int status)
{
    if (status == EATING)
    {
        
        printf("%lld: %d is eating.\n", time_elapsed(philo), philo->num);
		usleep(philo->args->time_eat * 1000);
		philo->last_meal = time_elapsed(philo);
    }
    else if (status == SLEEPING)
    {
        printf("%lld: %d is sleeping.\n", time_elapsed(philo), philo->num);
        usleep(philo->args->time_sleep * 1000);
    }
    else if (status == THINKING)
    {
        printf("%lld: %d is sleeping.\n", time_elapsed(philo), philo->num);
		usleep(philo->args->time_sleep * 1000);
    }
    else
    {
        pthread_mutex_lock(&philo->args->death_trigger);
		printf("%lld: %d died\n", time_elapsed(philo), philo->num);
		pthread_mutex_unlock(&philo->args->death_trigger);
    }
}