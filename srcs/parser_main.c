/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <lbrandy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 15:16:48 by lbrandy           #+#    #+#             */
/*   Updated: 2021/10/02 16:19:53 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	d_red(char *type, t_redir *red, char *name, t_g_lst *grand)
{
	if (ft_strncmp(type, ">>", 2) == 0)
	{
		red->filename = name;
		grand->p_cnt++;
		grand->p_r_cnt++;
	}
	if (ft_strncmp(type, "<<", 2) == 0)
	{
		red->filename = NULL;
		red->fd = readline_mass(name, grand);
		grand->r_cnt++;
	}
}

t_redir	*created(t_token *tmp, t_g_lst *grand)
{
	t_redir	*mass;
	int		j;

	mass = (t_redir *)malloc(sizeof(t_redir) * grand->redir_count);
	j = 0;
	while (tmp)
	{
		if (tmp->str[0] == '>' || tmp->str[0] == '<')
		{
			fd_create(tmp->str, &mass[j], (tmp->next)->str, grand);
			j++;
		}
		tmp = tmp->next;
	}
	return (mass);
}

void	quotes_handler(char **env, t_all *all)
{
	t_g_lst	*head;
	t_token	*lst;
	int		j;

	j = 0;
	head = all->grand;
	while (j < (all->pipes + 1))
	{
		lst = head[j].first_list;
		while (lst)
		{
			lst->str = pars_quotes(lst->str, env);
			lst = lst->next;
		}
		j++;
	}
}

int	creation_fd(t_all *all)
{
	int		i;

	i = -1;
	while (++i < (all->pipes + 1))
	{	
		all->grand[i].redirs = redir_fd_create(all->grand[i].first_list,
				&all->grand[i]);
		if (g_exit_sta.tement == 228)
			return (0);
	}
	return (1);
}

int	parser_main(char **env, t_all *all)
{
	char	*new_line;
	char	*str;

	if (!all)
		return (0);
	sig_init();
	str = readline("minishell$: ");
	if (str == NULL)
		ctrl_d();
	if (!str[0])
		return (0);
	add_history(str);
	new_line = preparser(str);
	if (!new_line)
		return (0);
	free(str);
	pipe_fd_create(all, new_line);
	all->grand = grandlist_creation(new_line, (all->pipes + 1));
	if (!(creation_fd(all)))
		return (0);
	quotes_handler(env, all);
	return (1);
}
