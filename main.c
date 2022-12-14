/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:30:57 by nvideira          #+#    #+#             */
/*   Updated: 2022/10/16 23:17:18 by nvideira         ###   ########.fr       */
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

int	setup(t_philo *philo, t_args *args)
{
	int	i;

	i = -1;
	if (!philo)
		return (0);
	args->fork = malloc(args->n_philo * sizeof(pthread_mutex_t));
	args->f_bool = malloc(args->n_philo + 1 * sizeof(int));
	if (!init_mutex(args))
		return (0);
	while (++i < args->n_philo)
		philo[i] = philo_create(i + 1, args);
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
	args->dead = 0;
	if (args->n_philo < 1 || args->time_die < 1 || args->time_eat < 1
		|| args->time_sleep < 1)
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
		return (printf("Bad input.\n"));
	if (args.n_philo == 1)
		return (printf("%lld: 1 died\n", args.time_die));
	philo = (t_philo *)malloc(args.n_philo * sizeof(t_philo));
	if (!setup(philo, &args))
		return (printf("An error has occurred when starting the simulation\n"));
	i = -1;
	while (++i < args.n_philo)
		if (pthread_create(&philo[i].t_id, NULL, &routine, (void *)(&philo[i])))
			return (printf("An error has ocurred when creating threads"));
	i = -1;
	while (++i < args.n_philo)
		pthread_join(philo[i].t_id, NULL);
	destroy_mutex(&args);
	free(philo);
	free(args.fork);
	return (0);
}
