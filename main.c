/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:30:57 by nvideira          #+#    #+#             */
/*   Updated: 2022/09/04 21:49:20 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_args(t_args *args, char **av)
{
	args->n_philo = ft_atoi(av[1]);
	args->time_die = ft_atoi(av[2]);
	args->time_eat = ft_atoi(av[3]);
	args->time_sleep = ft_atoi(av[4]);
	if (av[5])
		args->limit = ft_atoi(av[5]);
}

int	main(int ac, char **av)
{
	t_args			args;
	t_philo			*philo;

	philo->num = 1;
	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments.\n"));
	get_args(&args, av);
	philo = (t_philo *)malloc(args.n_philo * sizeof(t_philo));
	if (pthread_mutex_init(&philo->fork, NULL) != 0)
		ft_error("Mutex init failed.");
	while (args.n_philo--)
	{
		philo->error = pthread_create(&philo->t_id[philo->num - 1], NULL, &routine, &args);
		if (philo->error != 0)
			ft_error("An error has ocurred when creating threads");
		philo->num++;
	}
	return (0);
}
