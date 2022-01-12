/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 05:13:56 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 12:30:00 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_option(char **mass)
{
	int	i;

	i = 0;
	while (mass[i])
	{
		if (ft_strcmp("-n", mass[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	my_echo_func(char **mass)
{
	int	i;
	int	flag;

	i = 1;
	flag = find_option(mass);
	while (mass[i])
	{
		if (ft_strcmp("-n", mass[i]) != 0)
			printf("%s", mass[i]);
		if (mass[i + 1] && ft_strcmp("-n", mass[i]) != 0)
			printf(" ");
		i++;
	}
	if (flag != 1)
		printf("\n");
	g_exit_sta.tus = 0;
}
