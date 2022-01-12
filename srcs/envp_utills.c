/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utills.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 08:37:45 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 12:12:21 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_fields(t_all *all, char **envp)
{
	g_exit_sta.tement = 0;
	all->envp_list = envp_list_create(envp);
	g_exit_sta.tus = 0;
}

void	free_envp(char **mass, int flag)
{
	int	i;

	if (flag != 0)
	{
		i = 0;
		while (mass[i])
		{
			free(mass[i]);
			i++;
		}
		free(mass);
	}
}

char	**from_list_to_mass(t_list *envp_list, char **mass_envp, int flag)
{
	int		counter;
	t_list	*tmp;
	char	**new_envp;
	int		i;

	counter = 0;
	tmp = envp_list;
	i = 0;
	free_envp(mass_envp, flag);
	while (tmp)
	{
		counter++;
		tmp = tmp->next;
	}
	new_envp = (char **)malloc(sizeof(char *) * (counter + 1));
	tmp = envp_list;
	while (i < counter)
	{
		new_envp[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
