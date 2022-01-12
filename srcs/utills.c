/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:18:11 by lbrandy           #+#    #+#             */
/*   Updated: 2021/10/02 14:40:50 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	if (str1[i] && !str2[i])
		return ((unsigned char)str1[i]);
	else if (!str1[i] && str2[i])
		return (-(unsigned char)str2[i]);
	else
		return (0);
}

void	dup_reverse(t_all *all)
{
	if (all->b_flag == 1)
	{
		if (all->grand[all->i].p_cnt)
			dup2(all->grand[all->i].fd1, 1);
		if (all->grand[all->i].r_cnt && (!all->grand[all->i].p_r_cnt))
			dup2(all->grand[all->i].fd1, 0);
		all->b_flag = 0;
	}	
}

void	ch_p_handler(t_all *all, char **envp)
{
	dup_handler(all, &all->grand[all->i]);
	cmd_handl(envp, &all->grand[all->i], &all->envp_list, all);
	dup2(all->grand->fd1, 0);
	dup_reverse(all);
}

void	err_hand(char *message)
{
	ft_putstr_fd(message, 2);
	exit(g_exit_sta.tus);
}

void	ft_lstfree_cont(void *content)
{
	if (content)
		free(content);
}
