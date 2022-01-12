/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 23:03:35 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 11:21:50 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_init(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, catch_signal_c);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_init_for_ch(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_sl);
}

void	sig_init_for_ch_redir(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_d);
}
