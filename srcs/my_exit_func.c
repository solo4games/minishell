/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 05:12:14 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 12:02:03 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_exit_stat(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

int	check_arg_count(char **mass)
{
	int	i;

	i = 0;
	while (mass[i])
		i++;
	if (i > 2)
	{
		printf("minishell: exit: ");
		printf("too many arguments\n");
		return (0);
	}
	return (1);
}

void	my_exit_func(char **mass, t_all *all)
{
	g_exit_sta.tus = 0;
	if (check_arg_count(mass) == 1)
	{
		if (all->exit_flag == 1)
			printf("exit\n");
		if (ft_check_exit_stat(mass[1]) == 0)
		{
			printf("bash: exit: %s: ", mass[1]);
			printf("numeric argument required\n");
			g_exit_sta.tus = 255;
		}
		else if (mass[1])
			g_exit_sta.tus = ft_atoi(mass[1]);
		exit(g_exit_sta.tus);
	}
}
