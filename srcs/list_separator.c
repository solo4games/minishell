/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_separator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 01:41:39 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 12:11:42 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*scroll_not_redirs(t_token *tmp, char **mass, int *i)
{
	while (tmp && ft_strncmp(tmp->str, ">>", 2) != 0
		&& ft_strncmp(tmp->str, "<<", 2) != 0
		&& ft_strncmp(tmp->str, ">", 1) != 0
		&& ft_strncmp(tmp->str, "<", 1) != 0)
	{
		mass[*i] = ft_strdup(tmp->str);
		(*i)++;
		tmp = tmp->next;
	}
	return (tmp);
}

t_token	*scroll_redirs(t_token *tmp, char **mass)
{
	(void) mass;
	while (tmp && (ft_strncmp(tmp->str, ">>", 2) == 0
			|| ft_strncmp(tmp->str, "<<", 2) == 0
			|| ft_strncmp(tmp->str, ">", 1) == 0
			|| ft_strncmp(tmp->str, "<", 1) == 0))
		tmp = (tmp->next)->next;
	return (tmp);
}

char	**do_mass(char **mass, t_token *head)
{
	t_token	*tmp;
	int		i;

	tmp = head;
	i = 0;
	tmp = scroll_not_redirs(tmp, mass, &i);
	tmp = scroll_redirs(tmp, mass);
	tmp = scroll_not_redirs(tmp, mass, &i);
	mass[i] = NULL;
	i = 0;
	return (mass);
}

char	**list_separator(t_token *head, int redir_count)
{
	int		counter;
	t_token	*tmp;
	char	**mass;

	tmp = head;
	counter = 0;
	while (tmp)
	{
		counter++;
		tmp = tmp->next;
	}
	mass = (char **)malloc(sizeof(char *) * ((counter - redir_count * 2) + 1));
	mass = do_mass(mass, head);
	return (mass);
}
