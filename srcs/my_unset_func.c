/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 05:09:07 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 11:51:58 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_del_lst(t_list *temp, t_list *prev, t_list **head)
{
	if (prev == NULL)
		*head = temp->next;
	else
		prev->next = temp->next;
	free(temp->content);
	free(temp);
}

int	ft_del_envp(t_list **envp_list, char *envp)
{
	t_list	*temp;
	t_list	*prev;
	int		len;

	temp = *envp_list;
	prev = NULL;
	len = ft_strlen(envp);
	while (temp)
	{
		if (ft_strncmp(envp, temp->content, len) == 0)
		{
			if (((char *)temp->content)[len] == '=' ||
					!((char *)temp->content)[len])
			{
				ft_del_lst(temp, prev, envp_list);
				return (1);
			}
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}

void	my_unset_func(char **mass, t_list **envp_list)
{
	int	i;

	i = 1;
	while (mass[i])
	{
		if (mass[i][0] == '_' || ft_isalpha(mass[i][0]))
			ft_del_envp(envp_list, mass[i]);
		else
			printf("minishell: unset: `%s': not a valid identifier\n", mass[i]);
		i++;
	}
	g_exit_sta.tus = 0;
}
