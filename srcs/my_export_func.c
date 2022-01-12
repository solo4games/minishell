/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 05:10:49 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 12:01:18 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_export(char *envp)
{
	char	*str;
	int		i;

	printf("declare -x ");
	i = 0;
	while (envp[i] != '=' && envp[i])
		i++;
	str = ft_substr(envp, 0, i + 1);
	if (envp[i])
	{
		printf("%s\"", str);
		free(str);
		str = NULL;
		str = ft_substr(envp, i + 1, ft_strlen(envp) - i - 1);
		printf("%s\"\n", str);
		free(str);
	}
	else
		printf("%s\n", str);
}

void	find_min(t_list *envp_list, int *flag)
{
	t_list	*min;
	t_list	*tmp;
	int		i;
	int		min_i;

	i = 0;
	min_i = 0;
	tmp = envp_list;
	min = envp_list;
	while (tmp)
	{
		if ((ft_strcmp(min->content, tmp->content) > 0 && flag[i] == 0)
			|| (ft_strcmp(min->content, tmp->content) < 0 && flag[min_i] == 1))
		{
			min = tmp;
			min_i = i;
		}
		tmp = tmp->next;
		i++;
	}
	if (ft_strncmp("_=", min->content, 2) != 0)
		print_export(min->content);
	flag[min_i] = 1;
}

int	check_full(int *mass, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (mass[i] == 0)
			return (1);
		i++;
	}
	return (0);
}

void	print_sort_envp(t_list *envp_list)
{
	int		*flag;
	int		i;
	t_list	*tmp;
	int		size;
	int		count;

	count = 0;
	size = ft_lstsize(envp_list);
	flag = (int *)malloc(sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		flag[i] = 0;
		i++;
	}
	tmp = envp_list;
	while (check_full(flag, size))
	{
		find_min(envp_list, flag);
		count++;
	}
	free(flag);
}

void	my_export_func(char **mass, t_list *envp_list)
{
	int	i;

	i = 1;
	if (!mass[i])
		print_sort_envp(envp_list);
	else
	{
		while (mass[i])
		{
			if (mass[i][0] == '_' || ft_isalpha(mass[i][0]))
			{
				if (ft_check_over(&envp_list, mass[i]) == 0)
					return ;
				else if (ft_check_duplicate(envp_list, mass[i]) == 1)
					ft_lstadd_back(&envp_list, ft_lstnew(mass[i]));
			}
			else
				printf("minishell: export: `%s': not a valid identifier\n",
					mass[i]);
			i++;
		}
	}
	g_exit_sta.tus = 0;
}
