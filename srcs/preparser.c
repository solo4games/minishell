/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 15:11:10 by lbrandy           #+#    #+#             */
/*   Updated: 2021/10/02 11:29:34 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_red(char *str, int *i)
{
	char	temp;

	temp = str[(*i)++];
	if (str[*i] == temp)
		(*i)++;
	while (str[*i] == ' ')
		(*i)++;
	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '\0')
	{
		printf("minishell: syntax error near unexpected token `%c'\n", str[*i]);
		return (0);
	}
	return (1);
}

static int	ft_check_pipe(char *str, int *i)
{
	int	j;

	j = *i;
	if (j == 0)
	{
		printf("minishell: syntax error near unexpected token `%c'\n", str[*i]);
		return (0);
	}
	(*i)++;
	while (str[*i] == ' ' && str[*i] != '\0')
		(*i)++;
	if (str[*i] == '|' || str[*i] == '\0')
	{
		printf("minishell: syntax error near unexpected token `%c'\n", str[*i]);
		return (0);
	}
	return (1);
}

static char	*ft_del_spaces(char *str)
{
	int		i;
	int		j;
	char	*new_line;

	new_line = (char *)malloc(sizeof(char) * (new_str_count(str) + 1));
	j = 0;
	i = -1;
	while (str[++i])
	{
		while ((str[i] == ' ' && !not_in_quote(str, i) && (str[i + 1] == ' '
					|| !str[i + 1] || str[i + 1] == '|')))
			i++;
		new_line[j++] = str[i];
	}
	new_line[j] = '\0';
	return (new_line);
}

int	preparser_helper(int *c1, int *c2, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && not_in_quote(str, i))
			(c1)++;
		if (str[i] == '\"' && not_in_quote(str, i))
			(c2)++;
		if (str[i] == '|' && not_in_quote(str, i))
			if (ft_check_pipe(str, &i) == 0)
				return (0);
		if ((str[i] == '>' || str[i] == '<') && not_in_quote(str, i))
			if (ft_check_red(str, &i) == 0)
				return (0);
	}
	return (1);
}

char	*preparser(char *str)
{
	int		count_1;
	int		count_2;
	char	*line;

	count_1 = 0;
	count_2 = 0;
	if (preparser_helper(&count_1, &count_2, str) == 0)
		return (NULL);
	if (count_1 % 2 || count_2 % 2)
	{
		printf("minishell: unclosed quotes\n");
		return (NULL);
	}
	if (check_redir(str) == 0)
		return (NULL);
	line = ft_del_spaces(str);
	return (line);
}
