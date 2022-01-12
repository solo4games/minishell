/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 23:01:40 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 11:21:30 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	catch_signal_c(int signum)
{
	(void)signum;
	ft_putstr_fd("  \n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_d(void)
{
	ft_putstr_fd("\e[1A\e[12C" "exit\n", 1);
	exit(g_exit_sta.tus);
}

void	ctrl_c(int val)
{
	(void)val;
	g_exit_sta.tus = 130;
	printf("\n");
}

void	ctrl_c_d(int val)
{
	(void)val;
	exit(228);
}

void	ctrl_sl(int val)
{
	(void)val;
	g_exit_sta.tus = 131;
	printf("Quit: 3\n");
}
