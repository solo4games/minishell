/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 05:14:30 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 12:06:33 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_absolute(t_list *envp_list, char *path)
{
	int		i;
	char	*old_pwd;

	old_pwd = NULL;
	old_pwd = getcwd(old_pwd, 100);
	i = chdir(path);
	free(old_pwd);
	if (i == 0)
		change_envp(envp_list, old_pwd);
}

char	*go_up(char *str)
{
	char	*temp;
	int		len;
	int		i;

	len = ft_strlen(str);
	i = len - 1;
	while (str[i] != '/' && str[i])
		i--;
	if (i == 0)
		i++;
	temp = str;
	str = ft_substr(str, 0, i);
	free(temp);
	return (str);
}

char	*go_down(char *str, char *sub)
{
	char	*temp;

	if (str[ft_strlen(str) - 1] != '/')
	{
		temp = str;
		str = ft_strjoin(str, "/");
		free(temp);
	}
	temp = str;
	str = ft_strjoin(str, sub);
	free(temp);
	return (str);
}

void	do_relative(t_list *envp_list, char *path)
{
	char	*temp_old;
	char	*old_pwd;
	int		flag;
	int		i;

	i = 0;
	i = get_home(path, envp_list);
	if (i == -1)
		return ;
	temp_old = NULL;
	temp_old = getcwd(temp_old, 100);
	old_pwd = temp_old;
	flag = 1;
	temp_old = walk(path, temp_old, flag, i);
	i = chdir(temp_old);
	free(temp_old);
	if (i == 0)
		change_envp(envp_list, old_pwd);
	else
	{
		printf("minishell: cd: %s: ", path);
		printf("%s\n", strerror(errno));
	}
}

void	my_cd_func(t_list *envp_list, char **mass)
{
	t_list	*tmp;

	tmp = envp_list;
	if (mass[1])
	{
		if (mass[1][0] == '/')
			do_absolute(envp_list, mass[1]);
		else
			do_relative(envp_list, mass[1]);
	}
	g_exit_sta.tus = 0;
}
