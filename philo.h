/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:02:11 by nvideira          #+#    #+#             */
/*   Updated: 2022/10/12 09:43:51 by nvideira         ###   ########.fr       */
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
# define DEAD 4
# define FORKING 5
# define UNFORKING 6

typedef struct s_args{
	int				n_philo;
	long long		time_die;
	int				time_eat;
	int				time_sleep;
	int				limit;
	int				dead;
	pthread_mutex_t	*fork;
	pthread_mutex_t	chomp;
	pthread_mutex_t	death_trigger;
}	t_args;

typedef struct s_philo{
	pthread_t		t_id;
	int				state;
	int				num;
	struct timeval	date;
	t_args			*args;
	int				n_meals;
	long long		last_meal;
	long long		start_time;
	long long		current_time;
}	t_philo;

long long	ft_atoi(const char *str);
size_t		ft_strlen(const char *str);
void		*routine(void *arg);
t_philo		philo_create(int num, t_args *args);
int			init_mutex(t_args *args);
void		destroy_mutex(t_args *args);
int			grab_forks(t_philo *philo, int left, int right);
void		drop_forks(t_philo *philo, int left, int right);
int			check_death(t_philo *philo);
long long	time_elapsed(t_philo *philo);
void		print_status(t_philo *philo, int status);
int			brainstorming(t_philo *philo);
int			eating(t_philo *philo);
int			snoring(t_philo *philo);
#endif
