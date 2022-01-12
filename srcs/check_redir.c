/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <lbrandy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:29:10 by lbrandy           #+#    #+#             */
/*   Updated: 2021/10/01 17:32:59 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_name_of_file(char *str, int *i)
{
	char	*error_str;
	int		j;

	j = *i;
	while (str[*i] == ' ')
		(*i)++;
	while (str[*i] != ' ' && str[*i] != '>' && str[*i] != '<')
		(*i)++;
	if (str[*i] == '>' || str[*i] == '<')
	{
		error_str = ft_substr(str, j, *i - j);
		printf("minishell: syntax error near unexpected token `%s'\n",
			error_str);
		free(error_str);
		return (0);
	}
	return (1);
}

int	count_redir(char *str)
{
	int	counter;

	counter = 0;
	while (*str)
	{
		if (*str == '>' || *str == '<')
		{
			counter++;
			if (*(str + 1) == '<' || *(str + 1) == '>')
				str++;
		}
		str++;
	}
	return (counter);
}

int	check_redir(char *str)
{
	int	i;
	int	j;
	int	counter;

	j = 0;
	i = 0;
	counter = count_redir(str);
	while (str[i])
	{
		if (j >= counter - 1)
			break ;
		if (str[i] == '>' || str[i] == '<')
		{
			if (str[i + 1] == '>' || str[i + 1] == '<')
				i += 2;
			else
				i++;
			if (!check_name_of_file(str, &i))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
