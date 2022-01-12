/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:19:16 by lbrandy           #+#    #+#             */
/*   Updated: 2021/10/02 11:57:04 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_doing_dup(char *str, t_list *lst, int i)
{
	char	*temp;

	if (str[i] != '=' && str[i])
		return (1);
	else
	{
		if (str[i] == '=')
		{
			temp = lst->content;
			lst->content = ft_strdup(str);
			free(temp);
		}
		return (0);
	}
}

int	ft_check_duplicate(t_list *envp_list, char *str)
{
	t_list	*lst;
	int		i;

	lst = envp_list;
	while (lst)
	{
		i = 0;
		while (((char *)lst->content)[i] != '=' && ((char *)lst->content)[i])
			i++;
		if (ft_strncmp(str, lst->content, i) == 0)
			return (ft_doing_dup(str, lst, i));
		lst = lst->next;
	}
	return (1);
}

void	ft_create_str_plus(t_list **envp_list, char *str)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
	int		i;

	i = 0;
	while (str[i] != '+')
		i++;
	temp = ft_substr(str, 0, i);
	temp2 = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	temp3 = ft_strjoin(temp, temp2);
	ft_lstadd_back(envp_list, ft_lstnew(temp3));
	free(temp);
	free(temp2);
	free(temp3);
}

int	doing_overload(t_list *lst, char *str, int i)
{
	char	*temp;
	char	*temp2;

	if (ft_strncmp(lst->content, str, i) == 0
		&& (((char *)lst->content)[i] == '=' || !((char *)lst->content)[i]))
	{
		if (((char *)lst->content)[i] == '=')
			temp = ft_substr(str, i + 2, ft_strlen(str) - i - 2);
		if (!((char *)lst->content)[i])
			temp = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
		temp2 = lst->content;
		lst->content = ft_strjoin(lst->content, temp);
		free(temp2);
		free(temp);
		return (0);
	}
	return (1);
}

int	ft_check_over(t_list **envp_list, char *str)
{
	t_list	*lst;
	int		i;

	lst = *envp_list;
	i = 0;
	while (str[i])
	{
		if (ft_strncmp(&str[i], "+=", 2) == 0)
			break ;
		i++;
	}
	if (!str[i])
		return (1);
	else
	{
		while (lst)
		{
			if (doing_overload(lst, str, i) == 0)
				return (0);
			lst = lst->next;
		}
		ft_create_str_plus(envp_list, str);
		return (0);
	}
}
