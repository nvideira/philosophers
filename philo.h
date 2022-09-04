/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:02:11 by nvideira          #+#    #+#             */
/*   Updated: 2022/09/04 21:49:30 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# define EATING 1
# define SLEEPING 2
# define THINKING 3


typedef struct s_args{
    int n_philo;
    int time_die;
    int time_eat;
    int time_sleep;
    int limit;
}   t_args;

typedef struct s_philo{
    pthread_t		*t_id;
	int				error;
	int				state;
	int				num;
	pthread_mutex_t	fork;
	struct	timeval	date;
}   t_philo;

int	        ft_atoi(const char *str);
void		routine(t_philo *philo, t_args *args);
void		ft_error(char *str);

#endif
