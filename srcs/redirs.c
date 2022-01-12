/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 02:05:57 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 14:46:10 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	double_redir(t_g_lst *grand)
{
	grand->fd2 = open(grand->redirs[grand->i].filename,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (grand->fd2 < 0)
		exit(g_exit_sta.tus);
	grand->fd1 = dup(1);
	dup2(grand->fd2, 1);
}

void	double_reverse_redir(t_g_lst *grand, t_all *all)
{
	if (all->b_flag == 0)
		dup2(grand->redirs[grand->i].fd, 0);
}

void	redir(t_g_lst *grand)
{
	grand->fd2 = open(grand->redirs[grand->i].filename,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (grand->fd2 < 0)
		exit(g_exit_sta.tus);
	grand->fd1 = dup(1);
	dup2(grand->fd2, 1);
}

void	reverse_redir(t_g_lst *grand)
{
	grand->fd2 = open(grand->redirs[grand->i].filename, O_RDONLY, 0644);
	if (grand->fd2 < 0)
		exit(g_exit_sta.tus);
	grand->fd1 = dup(0);
	dup2(grand->fd2, 0);
}

void	redirs(t_g_lst *grand, t_all *all)
{
	grand->i = 0;
	while (grand->i < grand->redir_count)
	{
		if (ft_strncmp(grand->redirs[grand->i].type, ">>", 2) == 0)
			double_redir(grand);
		if (ft_strncmp(grand->redirs[grand->i].type, "<<", 2) == 0)
			double_reverse_redir(grand, all);
		if (ft_strncmp(grand->redirs[grand->i].type, ">", 2) == 0)
			redir(grand);
		if (ft_strncmp(grand->redirs[grand->i].type, "<", 2) == 0)
			reverse_redir(grand);
		grand->i++;
	}
}
