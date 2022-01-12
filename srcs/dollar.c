/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 10:42:11 by lbrandy           #+#    #+#             */
/*   Updated: 2021/10/02 12:24:14 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_replace(char *str, int j, int *i, char *temp)
{
	char	*temp1;
	char	*temp2;

	if (temp)
		temp = replace_envp(str, j, i, temp);
	else
	{
		temp = ft_substr(str, 0, j);
		temp1 = ft_substr(str, *i, ft_strlen(str) - *i);
		temp2 = temp;
		temp = ft_strjoin(temp, temp1);
		free(temp2);
		free(temp1);
		*i = j;
	}
	return (temp);
}

char	*do_exit_status(char *str, int *i)
{
	char	*temp;
	char	*temp2;
	char	*temp3;

	temp = ft_substr(str, 0, *i);
	temp2 = ft_itoa(g_exit_sta.tus);
	temp3 = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	temp = ft_substr(str, *i + 2, ft_strlen(str) - *i - 2);
	temp2 = temp3;
	temp3 = ft_strjoin(temp3, temp);
	free(temp2);
	free(temp);
	return (temp3);
}

char	*print_dollar(char *str, int *i)
{
	int		j;
	char	*temp;
	char	*temp2;
	char	*temp3;

	j = *i;
	if (!str[j + 1] || str[j + 1] == '\"' || str[j + 1] == '\'')
		return (str);
	else
	{
		temp = ft_substr(str, 0, j);
		j += 2;
		temp2 = ft_substr(str, j, ft_strlen(str) - j);
		temp3 = str;
		str = ft_strjoin(temp, temp2);
		free(temp);
		free(temp2);
		free(temp3);
		*i -= 2;
		return (str);
	}
}

char	*find_envp(char **env, char *key)
{
	int		z;
	char	*temp;
	int		k;

	temp = NULL;
	k = -1;
	while (env[++k])
	{
		if (ft_strnstr(env[k], key, ft_strlen(key)))
		{
			z = 0;
			while (env[k][z] && env[k][z] != '=')
				z++;
			temp = ft_substr(env[k], 0, z);
			if (ft_strncmp(temp, key, ft_strlen(temp)) == 0)
				break ;
			free(temp);
			temp = NULL;
		}
	}
	if (env[k])
		temp = ft_substr(env[k], z + 1, ft_strlen(env[k]) - z);
	return (temp);
}

char	*ft_dollar(char *str, int *i, char **env)
{
	int		j;
	char	*temp;
	char	*key;

	j = *i;
	if (str[j + 1] == '?')
		return (do_exit_status(str, i));
	if (str[j + 1] != '_' && !ft_isalpha(str[j + 1]))
		return (print_dollar(str, i));
	while (str[++(*i)])
		if (!ifkey(str[*i]))
			break ;
	key = ft_substr(str, j + 1, *i - j - 1);
	temp = find_envp(env, key);
	return (ft_replace(str, j, i, temp));
}
