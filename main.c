/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:30:57 by nvideira          #+#    #+#             */
/*   Updated: 2022/08/31 19:04:53 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_args(t_args *args, char **av)
{
	args->n_philo = ft_atoi(av[1]);
	if (args->n_philo < 1)
		ft_error("Not enough philosophers.");
	args->time_die = ft_atoi(av[2]);
	if (args->time_die < 1)
		ft_error("Time to die is too short.");
	args->time_eat = ft_atoi(av[3]);
	if (args->time_eat < 1)
		ft_error("The philosophers need more time to eat.");
	args->time_sleep = ft_atoi(av[4]);
	if (args->time_sleep < 1)
		ft_error("The philosophers need more time to sleep.");
	if (av[5])
	{
		args->limit = ft_atoi(av[5]);
		if (args->limit < 1)
			ft_error("The philosophers need to eat at least once.");
	}
}

int	main(int ac, char **av)
{
	t_args			args;
	t_philo			*philo;
	pthread_mutex_t	**forks;
	unsigned int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments.\n"));
	get_args(&args, av);
	philo = (t_philo *)malloc(args.n_philo * sizeof(t_philo));
	forks = (pthread_mutex_t **)malloc(args.n_philo * sizeof(pthread_mutex_t *));
	if (pthread_mutex_init(&forks, NULL) != 0)
		ft_error("Mutex init failed.");
	while (args.n_philo--)
	{
		philo->t_id[i] = pthread_create(&philo->t_id[i], NULL, &routine, &args);
		i++;
	}
	return (0);
}
