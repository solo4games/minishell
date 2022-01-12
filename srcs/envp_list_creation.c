/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <lbrandy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 04:59:13 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 16:21:33 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_pwd(t_list **head)
{
	char	*str;
	char	*temp;

	str = NULL;
	str = getcwd(str, 100);
	temp = ft_strjoin("PWD=", str);
	ft_lstadd_back(head, ft_lstnew(temp));
	free(temp);
	free(str);
}

char	*shlvl_inc(char *shlvl)
{
	int		temp;
	char	*str1;
	char	*str2;
	char	*temp1;
	int		i;

	i = 0;
	while (!(ft_isdigit(shlvl[i])))
		i++;
	temp = ft_atoi(&(shlvl[i]));
	temp++;
	str1 = ft_substr(shlvl, 0, i);
	str2 = ft_itoa(temp);
	temp1 = str1;
	str1 = ft_strjoin(str1, str2);
	free(temp1);
	free(str2);
	return (str1);
}

void	create_shlvl(t_list **head, int flag, char **envp)
{
	char	*str;
	char	*temp;
	int		i;

	str = NULL;
	i = 0;
	if (flag == 0)
		ft_lstadd_back(head, ft_lstnew("SHLVL=1"));
	else
	{
		i = search_envp("SHLVL", envp);
		str = shlvl_inc(envp[i]);
		temp = str;
		ft_lstadd_back(head, ft_lstnew(str));
		free(temp);
	}
}

t_list	*check_envp(char **envp)
{
	t_list	*head;

	head = NULL;
	if (search_envp("SHLVL", envp) == -1)
		create_shlvl(&head, 0, envp);
	else
		create_shlvl(&head, 1, envp);
	ft_lstadd_back(&head, ft_lstnew("_=/usr/bin/env"));
	if (search_envp("PWD", envp) == -1)
		create_pwd(&head);
	if (search_envp("OLDPWD", envp) == -1)
		ft_lstadd_back(&head, ft_lstnew("OLDPWD"));
	return (head);
}

t_list	*envp_list_create(char **envp)
{
	int		i;
	t_list	*head;

	head = check_envp(envp);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("SHLVL=", envp[i], 6) != 0
			&& ft_strncmp("_=", envp[i], 2) != 0)
			ft_lstadd_back(&head, ft_lstnew(envp[i]));
		i++;
	}
	return (head);
}
