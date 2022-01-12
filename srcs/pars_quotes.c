/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 15:19:51 by lbrandy           #+#    #+#             */
/*   Updated: 2021/10/02 11:49:51 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
	}
	return (0);
}

char	*do_gap2(char *str, int *i, int j)
{
	char	*temp;
	char	*temp1;
	char	*temp2;

	temp = ft_substr(str, 0, j);
	temp1 = temp;
	temp2 = ft_substr(str, j + 1, *i - j - 1);
	temp = ft_strjoin(temp, temp2);
	free(temp2);
	free(temp1);
	temp1 = temp;
	temp2 = ft_strdup(str + *i + 1);
	temp = ft_strjoin(temp, temp2);
	free(temp2);
	free(temp1);
	(*i)--;
	return (temp);
}

char	*ft_gap2(char *str, int *i, char **env)
{
	int		j;
	char	*temp;

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '$')
			str = ft_dollar(str, i, env);
		if (str[*i] == '\"')
			break ;
	}
	temp = do_gap2(str, i, j);
	free(str);
	return (temp);
}

char	*ft_gap(char *str, int *i)
{
	int		j;
	char	*temp;
	char	*temp1;
	char	*temp2;

	j = *i;
	while (str[++(*i)])
		if (str[*i] == '\'')
			break ;
	temp = ft_substr(str, 0, j);
	temp1 = temp;
	temp2 = ft_substr(str, j + 1, *i - j - 1);
	temp = ft_strjoin(temp, temp2);
	free(temp2);
	free(temp1);
	temp1 = temp;
	temp2 = ft_strdup(str + *i + 1);
	temp = ft_strjoin(temp, temp2);
	free(str);
	free(temp2);
	free(temp1);
	(*i)--;
	return (temp);
}

char	*pars_quotes(char *str, char **env)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			str = ft_gap(str, &i);
		if (str[i] == '\"')
			str = ft_gap2(str, &i, env);
		if (str[i] == '$')
			str = ft_dollar(str, &i, env);
	}
	return (str);
}
