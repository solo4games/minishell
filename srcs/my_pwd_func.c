/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 06:05:32 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 11:52:19 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_pwd_func(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 100);
	printf("%s\n", pwd);
	free(pwd);
	g_exit_sta.tus = 0;
}
