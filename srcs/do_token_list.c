/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_token_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:13:42 by lbrandy           #+#    #+#             */
/*   Updated: 2021/10/02 12:24:51 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	space_in_quote(char *str, int end)
{
	int	count1;
	int	count2;
	int	i;

	count1 = 0;
	count2 = 0;
	i = 0;
	while (i <= end)
	{
		if (str[i] == '\'')
			count1++;
		if (str[i] == '\"')
			count2++;
		i++;
	}
	if (!(count1 % 2) && !(count2 % 2))
		return (1);
	return (0);
}

int	pars_redir(t_token **head, char *str, int start, int end)
{
	char	temp;

	if (start != end)
		token_pb(head, ft_substr(str, start, end - start));
	start = end;
	temp = str[end];
	if (str[end] == '>')
	{
		end++;
		if (str[end] == '>')
			token_pb(head, ft_strdup(">>"));
		else
			token_pb(head, ft_strdup(">"));
	}
	if (str[end] == '<')
	{
		end++;
		if (str[end] == '<')
			token_pb(head, ft_strdup("<<"));
		else
			token_pb(head, ft_strdup("<"));
	}
	if (str[end] == '>' || str[end] == '<')
		end++;
	return (end);
}

int	pars_space(t_token **head, char *str, int start, int end)
{
	if (start != end)
		token_pb(head, ft_substr(str, start, end - start));
	return (end + 1);
}

t_token	*do_token_list(t_token *head, char *str)
{
	t_token	*tmp;
	int		i;
	int		start;

	tmp = head;
	i = -1;
	start = 0;
	while (str[++i])
	{
		if ((str[i] == '>' || str[i] == '<') && not_in_quote(str, i))
		{
			start = pars_redir(&tmp, str, start, i);
			i = start - 1;
		}
		else if (str[i] == ' ' && space_in_quote(str, i))
			start = pars_space(&tmp, str, start, i);
	}
	if (i != 0 && str[i - 1] != ' ')
		token_pb(&tmp, ft_substr(str, start, i - start));
	return (tmp);
}
