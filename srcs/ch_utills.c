/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_utills.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <lbrandy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 15:30:13 by lbrandy           #+#    #+#             */
/*   Updated: 2021/10/02 16:22:20 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_wait(t_all *all)
{
	close(all->fd_pipe[all->i - 2][0]);
	all->i = 0;
	while (all->i <= all->pipes)
	{
		wait(0);
		if (all->exit_flag == 1)
			exit(g_exit_sta.tus);
		all->i++;
	}
}

void	with_pipes(t_all *all, char **envp)
{
	all->flag = 0;
	while (all->i <= all->pipes)
	{
		if (all->i != all->pipes)
		{
			if (pipe(all->fd_pipe[all->i]) == -1)
				exit(g_exit_sta.tus);
		}
		call_child(all, envp);
		if (all->pid == -1)
			exit(g_exit_sta.tus);
		all->i++;
	}
	close_wait(all);
}

void	check_exit(t_all *all)
{
	t_token	*lst;

	lst = all->grand[0].first_list;
	while (lst)
	{
		if (ft_strcmp("exit", lst->str) == 0)
			all->exit_flag = 1;
		lst = lst->next;
	}
}

void	exec_cmd(t_all *all, char **envp)
{
	int	status;

	all->pid = fork();
	if (all->pid == 0)
		ch_p_handler(all, envp);
	if (all->pid != 0)
	{
		wait(&status);
		g_exit_sta.tus = WIFEXITED(status);
		if (all->exit_flag == 1)
			exit(g_exit_sta.tus);
	}
	if (all->pid == -1)
		exit(g_exit_sta.tus);
}

void	without_pipes(t_all *all, char **envp, t_g_lst *grand)
{
	sig_init_for_ch();
	check_exit(all);
	grand->cmd_flags = list_separator(grand->first_list, grand->redir_count);
	all->flag = 1;
	if (check_command(grand->cmd_flags[0], all))
	{
		dup_handler(all, &all->grand[all->i]);
		do_builtins(grand->cmd_flags, &all->envp_list, all);
		dup_reverse(all);
	}
	else
		exec_cmd(all, envp);
}
