/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler_utills.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <lbrandy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 08:26:57 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 16:42:23 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_exec(t_g_lst *grand)
{
	grand->j = 0;
	while (grand->paths[grand->j] != NULL)
	{
		if (access(grand->paths[grand->j], X_OK) == 0)
			grand->path_f = grand->paths[grand->j];
		grand->j++;
	}
}

int	check_command(char *command, t_all *all)
{
	int	len;

	len = ft_strlen(command);
	if (ft_strncmp("echo", command, len) == 0
		|| ft_strncmp("cd", command, len) == 0
		|| ft_strncmp("pwd", command, len) == 0
		|| ft_strncmp("export", command, len) == 0
		|| ft_strncmp("unset", command, len) == 0
		|| ft_strncmp("env", command, len) == 0
		|| ft_strncmp("exit", command, len) == 0)
	{
		all->b_flag = 1;
		return (1);
	}
	else
		all->b_flag = 0;
	return (0);
}

void	do_builtins(char **mass, t_list **envp_list, t_all *all)
{
	if (ft_strncmp("env", mass[0], 3) == 0)
		my_env_func(*envp_list);
	if (ft_strncmp("export", mass[0], 6) == 0)
		my_export_func(mass, *envp_list);
	if (ft_strncmp("unset", mass[0], 5) == 0)
		my_unset_func(mass, envp_list);
	if (ft_strncmp("cd", mass[0], 2) == 0)
		my_cd_func(*envp_list, mass);
	if (ft_strncmp("pwd", mass[0], 3) == 0)
		my_pwd_func();
	if (ft_strcmp("echo", mass[0]) == 0)
		my_echo_func(mass);
	if (ft_strcmp("exit", mass[0]) == 0)
		my_exit_func(mass, all);
	if (all->pipes != 0)
		exit(g_exit_sta.tus);
}
