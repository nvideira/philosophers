/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:02:11 by nvideira          #+#    #+#             */
/*   Updated: 2022/09/20 17:57:54 by nvideira         ###   ########.fr       */
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
	pthread_mutex_t	*fork;
	pthread_mutex_t	*left;
}   t_args;

typedef struct s_philo{
    pthread_t		t_id;
	int				state;
	int				num;
	struct timeval	date;
	t_args			*args;
	int				dead;
	double			last_meal;
	struct timeval	start_time;
}   t_philo;

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*routine(void *arg);
void	ft_error(char *str);
t_philo	philo_create(int num, t_args *args);

#endif
