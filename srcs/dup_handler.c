/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 02:12:04 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 12:16:50 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_p_cnt(t_all *all, t_g_lst *grand)
{
	if (grand->p_cnt == 0)
	{
		close(all->fd_pipe[all->i][0]);
		dup2(all->fd_pipe[all->i][1], 1);
	}
	else
		close(all->fd_pipe[all->i][1]);
}

void	dup_r_cnt(t_all *all, t_g_lst *grand)
{
	if (grand->r_cnt == 0)
	{
		close(all->fd_pipe[all->i - 1][1]);
		dup2(all->fd_pipe[all->i - 1][0], 0);
	}
	else
		close(all->fd_pipe[all->i - 1][0]);
}

void	pipes_without_redirs(t_all *all)
{
	if (all->i == 0)
	{
		close(all->fd_pipe[all->i][0]);
		dup2(all->fd_pipe[all->i][1], 1);
	}
	else if (all->i == all->pipes)
	{
		close(all->fd_pipe[all->i - 1][1]);
		dup2(all->fd_pipe[all->i - 1][0], 0);
	}
	else
	{
		close(all->fd_pipe[all->i - 1][1]);
		dup2(all->fd_pipe[all->i - 1][0], 0);
		close(all->fd_pipe[all->i][0]);
		dup2(all->fd_pipe[all->i][1], 1);
	}
}

void	pipes_with_redirs(t_all *all, t_g_lst *grand)
{
	if (all->i == 0)
	{
		dup_p_cnt(all, grand);
		redirs(grand, all);
	}
	else if (all->i == all->pipes)
	{
		dup_r_cnt(all, grand);
		redirs(grand, all);
	}
	else
	{
		dup_r_cnt(all, grand);
		dup_p_cnt(all, grand);
		redirs(grand, all);
	}
}

void	dup_handler(t_all *all, t_g_lst *grand)
{
	if (grand->redir_count != 0 && all->pipes == 0)
		redirs(grand, all);
	else if (grand->redir_count != 0 && all->pipes > 0)
		pipes_with_redirs(all, grand);
	else if (grand->redir_count == 0 && all->pipes > 0)
		pipes_without_redirs(all);
}
