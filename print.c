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

// void    before_print(t_philo *philo, int status, t_args *args)
// {
//     pthread_mutex_lock(&args->death_trigger);
//     print_status(philo, status, args);
//     pthread_mutex_unlock(&args->death_trigger);
// }

void    print_status(t_philo *philo, int status)
{
    if (check_death(philo))
        return ;
    if (status == EATING) 
        printf("%lld: %d is eating.\n", time_elapsed(philo), philo->num);
    else if (status == SLEEPING)
        printf("%lld: %d is sleeping.\n", time_elapsed(philo), philo->num);
    else if (status == THINKING)
        printf("%lld: %d is thinking.\n", time_elapsed(philo), philo->num);
    else if (status == FORKING)
    {
        printf("%lld: %d has taken a fork.\n", time_elapsed(philo), philo->num);
        printf("%lld: %d has taken a fork.\n", time_elapsed(philo), philo->num);
    }
    else if (status == UNFORKING)
    {
        printf("%lld: %d has dropped a fork.\n", time_elapsed(philo), philo->num);
        printf("%lld: %d has dropped a fork.\n", time_elapsed(philo), philo->num);
    }
}
