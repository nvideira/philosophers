/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:02:11 by nvideira          #+#    #+#             */
/*   Updated: 2022/09/06 20:37:50 by nvideira         ###   ########.fr       */
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
    pthread_t		t_id;
	int				state;
	int				num;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*left;
	struct	timeval	date;
	t_args			args;
}   t_philo;

int	        ft_atoi(const char *str);
char		*ft_itoa(int n);
char		*ft_strdup(const char *s1);
void		*routine(t_philo *philo);
void		ft_error(char *str);
t_philo 	philo_create(int num);

#endif
