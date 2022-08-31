/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:02:11 by nvideira          #+#    #+#             */
/*   Updated: 2022/08/31 19:07:45 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

typedef void (*t_test)(void);

typedef struct s_args{
    int n_philo;
    int time_die;
    int time_eat;
    int time_sleep;
    int limit;
}   t_args;

typedef struct s_philo{
    pthread_t   *t_id;
	
}   t_philo;

int	        ft_atoi(const char *str);
void		routine(t_philo *philo);
void		ft_error(char *str);
