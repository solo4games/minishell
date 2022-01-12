/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <lbrandy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:08:23 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 16:00:37 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token(t_token *lst)
{
	t_token	*tmp;

	while (lst)
	{
		tmp = lst;
		free(lst->str);
		lst = lst->next;
		free(tmp);
	}
}

void	free_cmd_handler(char **mass)
{
	int	i;

	i = 0;
	while (mass[i])
	{
		free(mass[i]);
		i++;
	}
	free(mass);
}

void	free_all(t_all *all)
{
	int	i;

	i = 0;
	while (i <= all->pipes)
	{
		free(all->grand[i].str);
		free_token(all->grand[i].first_list);
		if (all->pipes == 0)
			free_cmd_handler(all->grand[i].cmd_flags);
		if (i < all->pipes)
			free(all->fd_pipe[i]);
		i++;
	}
	free(all->fd_pipe);
	free(all->grand);
	free(all->grand->redirs);
}

int	main(int argc, char **argv, char **envp)
{
	t_all	*all;
	int		flag;

	(void)argv;
	(void)argc;
	all = (t_all *)malloc(sizeof(t_all));
	init_fields(all, envp);
	flag = 0;
	while (1)
	{
		envp = from_list_to_mass(all->envp_list, envp, flag);
		flag++;
		if (parser_main(envp, all) != 0)
		{
			all->i = 0;
			if (all->pipes == 0)
				without_pipes(all, envp, &all->grand[all->i]);
			if (all->pipes > 0)
				with_pipes(all, envp);
			free_all(all);
		}
	}
	return (0);
}
