/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_grandlist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 12:20:27 by lbrandy           #+#    #+#             */
/*   Updated: 2021/10/02 12:26:19 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipe_count(char *str)
{
	int	i;
	int	counter;

	counter = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '|' && not_in_quote(str, i))
			counter++;
	}
	return (counter);
}

t_g_lst	grandlist_cell(char *str, int *start, int i)
{
	t_g_lst	cell;

	cell.str = ft_substr(str, *start, i - *start);
	*start = i + 1;
	cell.first_list = NULL;
	cell.redirs = NULL;
	return (cell);
}

t_g_lst	*grandlist_creation(char *str, int pipes)
{
	int		i;
	int		start;
	int		j;
	t_g_lst	*grand_head;

	grand_head = (t_g_lst *)malloc(sizeof(t_g_lst) * (pipes));
	start = 0;
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '|' && not_in_quote(str, i))
		{
			grand_head[j] = grandlist_cell(str, &start, i);
			j++;
		}
	}
	if (i != 0)
		grand_head[j] = grandlist_cell(str, &start, i);
	free(str);
	j = -1;
	while (++j < pipes)
		grand_head[j].first_list = do_token_list(grand_head[j].first_list,
				grand_head[j].str);
	return (grand_head);
}
