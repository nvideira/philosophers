/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:02:11 by nvideira          #+#    #+#             */
/*   Updated: 2022/09/28 18:16:31 by nvideira         ###   ########.fr       */
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
    int n_philo;
    int time_die;
    int time_eat;
    int time_sleep;
	int limit;
	int	dead;
	pthread_mutex_t	*fork;
	pthread_mutex_t	death_trigger;
}   t_args;

typedef struct s_philo{
    pthread_t		t_id;
	int				state;
	int				num;
	struct timeval	date;
	t_args			*args;
	int				n_meals;
	long long		last_meal;
	long long		start_time;
}   t_philo;

long long	ft_atoi(const char *str);
char		*ft_itoa(int n);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s1);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*routine(void *arg);
void		ft_error(char *str);
t_philo		philo_create(int num, t_args *args);
void		init_mutex(t_args *args);
void		destroy_mutex(t_args *args);
int			grab_forks(t_philo *philo, int left, int right);
void		drop_forks(t_philo *philo, int left, int right);
int			check_death(t_philo *philo);
long long	time_elapsed(t_philo *philo);
void		before_print(t_philo *philo, int status, t_args *args);
void		print_status(t_philo *philo, int status, t_args *args);

#endif
