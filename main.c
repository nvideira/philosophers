/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:30:57 by nvideira          #+#    #+#             */
/*   Updated: 2022/09/20 17:56:43 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	only_digits(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_int(t_args args, char **av)
{
	if (ft_strncmp(ft_itoa(args.n_philo), av[1], ft_strlen(av[1]))
		|| ft_strncmp(ft_itoa(args.time_die), av[2], ft_strlen(av[2]))
		|| ft_strncmp(ft_itoa(args.time_eat), av[3], ft_strlen(av[3]))
		|| ft_strncmp(ft_itoa(args.time_sleep), av[4], ft_strlen(av[4])))
	{
		return (0);
	}	
	return (1);
}

int	get_args(t_args *args, char **av)
{
	if (!only_digits(av))
		return (0);
	args->n_philo = ft_atoi(av[1]);
	args->time_die = ft_atoi(av[2]);
	args->time_eat = ft_atoi(av[3]);
	args->time_sleep = ft_atoi(av[4]);
	if (av[5])
		args->limit = ft_atoi(av[5]);
	else
		args->limit = -1;
	if (args->n_philo < 1 || args->time_die < 1 || args->time_eat < 1
		|| args->time_sleep < 1)
		return (0);
	if (!is_int(*args, av))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_args	args;
	int		i;

	i = -1;
	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments.\n"));
	if (!get_args(&args, av))
		ft_error("Bad input");
	philo = (t_philo *)malloc(args.n_philo * sizeof(t_philo));
	if (!philo)
		ft_error("malloc error\n");
	args.fork = (pthread_mutex_t *)malloc(args.n_philo * sizeof(pthread_mutex_t));
	init_mutex(&args);
	while (++i < args.n_philo)
		philo[i] = philo_create(i + 1, &args);
	i = -1;
	while (++i < args.n_philo)
		if (pthread_create(&philo[i].t_id, NULL, &routine, (void *)(&philo[i])))
			ft_error("An error has ocurred when creating threads");
	i = 0;
	while (pthread_join(philo[i].t_id, NULL))
		i++;
	destroy_mutex(&args);
	free(philo);
	free(args.fork);
	return (0);
}
