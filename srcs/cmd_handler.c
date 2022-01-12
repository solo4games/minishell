/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <lbrandy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 01:44:33 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 16:51:06 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	search_path(char **envp, t_g_lst *grand)
{
	grand->i = 0;
	while (envp[grand->i] != NULL)
	{
		if (!(ft_strncmp("PATH", envp[grand->i], 4)))
		{
			grand->path_f = envp[grand->i];
			grand->path = ft_split(&grand->path_f[5], ':');
			grand->j = 0;
			while (grand->path[grand->j] != NULL)
				grand->j++;
		}
		grand->i++;
	}
}

void	making_paths(t_g_lst *grand)
{
	char	*temp;

	grand->j = 0;
	while (grand->path[grand->j] != NULL)
	{
		temp = grand->path[grand->j];
		grand->paths[grand->j] = ft_strjoin(grand->path[grand->j], "/");
		free(temp);
		temp = grand->paths[grand->j];
		grand->paths[grand->j] = ft_strjoin(grand->paths[grand->j],
				grand->cmd_flags[0]);
		free(temp);
		grand->j++;
	}
	grand->paths[grand->j] = NULL;
}

void	cmd_handl(char **envp, t_g_lst *grand, t_list **e_list, t_all *all)
{
	if (!all->flag)
		grand->cmd_flags = list_separator(grand->first_list,
				grand->redir_count);
	if (check_command(grand->cmd_flags[0], all))
		do_builtins(grand->cmd_flags, e_list, all);
	else
	{
		search_path(envp, grand);
		grand->paths = (char **)malloc(sizeof(char *) * grand->j);
		making_paths(grand);
		check_exec(grand);
		if (execve(grand->path_f, &grand->cmd_flags[0], envp) == -1)
			printf("minishell: %d: command not found\n", g_exit_sta.tus);
		g_exit_sta.tus = 127;
	}
}
