/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <lbrandy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 16:18:05 by lbrandy           #+#    #+#             */
/*   Updated: 2021/10/02 16:25:43 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir	*redir_fd_create(t_token *list, t_g_lst *grand)
{
	int		j;
	t_token	*tmp;

	tmp = list;
	j = 0;
	while (tmp)
	{
		if (tmp->str[0] == '>' || tmp->str[0] == '<')
			j++;
		tmp = tmp->next;
	}
	grand->redir_count = j;
	tmp = list;
	return (created(tmp, grand));
}

void	pipe_fd_create(t_all *all, char *str)
{
	int	i;

	i = 0;
	all->pipes = pipe_count(str);
	all->fd_pipe = (int **)malloc(sizeof(int *) * (all->pipes + 1));
	while (i < (all->pipes))
	{
		all->fd_pipe[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
}

void	fd_create(char *type, t_redir *red, char *name, t_g_lst *grand)
{
	grand->p_cnt = 0;
	grand->r_cnt = 0;
	if (ft_strlen(type) == 1)
	{
		if (ft_strncmp(type, ">", 1) == 0)
		{
			red->filename = name;
			grand->p_cnt++;
		}
		if (ft_strncmp(type, "<", 1) == 0)
		{
			red->filename = name;
			grand->r_cnt++;
		}
	}
	else
		d_red(type, red, name, grand);
	red->type = type;
}

int	search_envp(char *str, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
		{
			if (envp[i][len] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

void	call_child(t_all *all, char **envp)
{
	if (all->i - 2 >= 0)
		close(all->fd_pipe[all->i - 2][0]);
	sig_init_for_ch();
	all->pid = fork();
	if (all->pid == 0)
		ch_p_handler(all, envp);
	if (all->i != all->pipes)
		close(all->fd_pipe[all->i][1]);
}
