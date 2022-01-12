/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 17:37:13 by lbrandy           #+#    #+#             */
/*   Updated: 2021/10/02 11:31:49 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	not_in_quote(char *str, int end)
{
	int	count_1;
	int	count_2;
	int	i;

	count_1 = 0;
	count_2 = 0;
	i = 0;
	while (i <= end)
	{
		if (str[i] == '\'')
			count_1++;
		if (str[i] == '\"')
			count_2++;
		i++;
	}
	if (!(count_1 % 2) || !(count_2 % 2))
		return (1);
	return (0);
}

int	ifkey(char c)
{
	if (c != '_' && !ft_isalnum(c))
		return (0);
	return (1);
}

char	*replace_envp(char *str, int j, int *i, char *temp)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = ft_substr(str, 0, j);
	temp2 = temp1;
	temp1 = ft_strjoin(temp1, temp);
	free(temp2);
	temp3 = ft_strdup(str + *i);
	temp2 = temp;
	temp = ft_strjoin(temp1, temp3);
	free(temp1);
	free(temp2);
	free(temp3);
	(*i)--;
	return (temp);
}

int	new_str_count(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		while (str[i] == ' ' && !not_in_quote(str, i) && (str[i + 1] == ' '
				|| !str[i + 1] || str[i + 1] == '|'))
			i++;
		j++;
		i++;
	}
	return (j);
}
