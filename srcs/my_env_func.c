/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 05:13:06 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 12:02:37 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	search_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	my_env_func(t_list *envp_list)
{
	t_list	*lst;

	lst = envp_list;
	while (lst)
	{
		if (search_equal(lst->content) == 1)
			printf("%s\n", lst->content);
		lst = lst->next;
	}
	g_exit_sta.tus = 0;
}
