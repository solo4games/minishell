/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:06:40 by lbrandy           #+#    #+#             */
/*   Updated: 2021/10/02 12:04:44 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_pwd(t_list *tmp, char *pwd, char *old_pwd)
{
	char	*str;
	char	*temp;

	if (!old_pwd)
	{
		str = NULL;
		str = getcwd(str, 100);
		temp = tmp->content;
		tmp->content = ft_strjoin(pwd, str);
		free(temp);
		free(str);
	}
	else
	{
		str = tmp->content;
		tmp->content = ft_strjoin(pwd, old_pwd);
		free(str);
	}
}

void	change_envp(t_list *envp_list, char *old_pwd)
{
	t_list	*tmp;

	tmp = envp_list;
	while (tmp)
	{
		if (ft_strncmp("PWD=", tmp->content, 4) == 0)
		{
			old_pwd = ft_substr(tmp->content, 4, ft_strlen(tmp->content) - 4);
			change_pwd(tmp, "PWD=", NULL);
			break ;
		}
		tmp = tmp->next;
	}
	tmp = envp_list;
	while (tmp)
	{
		if (ft_strncmp("OLDPWD=", tmp->content, 7) == 0)
		{
			change_pwd(tmp, "OLDPWD=", old_pwd);
			free(old_pwd);
			break ;
		}
		tmp = tmp->next;
	}
}

char	*walk(char *path, char *temp_old, int flag, int i)
{
	char	*str1;
	int		j;

	while (path[i])
	{
		j = i;
		while (path[i] != '/' && path[i])
			i++;
		str1 = ft_substr(path, j, i - j);
		if (ft_strncmp("..", str1, ft_strlen(str1)) == 0 && flag == 1)
		{
			temp_old = go_up(temp_old);
			if (!temp_old[1])
				flag = 0;
		}
		else
		{
			temp_old = go_down(temp_old, str1);
			flag = 1;
		}
		free(str1);
		if (path[i])
			i++;
	}
	return (temp_old);
}

int	changing(t_list *tmp, char *path)
{
	char	*temp;
	int		i;

	temp = ft_substr(tmp->content, 5, ft_strlen(tmp->content) - 5);
	i = chdir(temp);
	if (i != 0)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return (-1);
	}
	i = 0;
	while (path[i] != '/' && path[i])
		i++;
	free(temp);
	return (i + 1);
}

int	get_home(char *path, t_list *envp_list)
{
	t_list	*tmp;

	tmp = envp_list;
	if ((path[0] == '~' && (path[1] == '/' || !path[1])) || !path)
	{
		while (tmp)
		{
			if (ft_strncmp("HOME=", tmp->content, 5) == 0)
				break ;
			tmp = tmp->next;
		}
		if (tmp)
			return (changing(tmp, path));
		else
		{
			printf("minishell: cd: HOME not set\n");
			return (-1);
		}
	}
	return (0);
}
