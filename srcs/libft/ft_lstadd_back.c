/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:04:36 by lbrandy           #+#    #+#             */
/*   Updated: 2021/07/12 19:02:27 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (new && lst)
	{
		if (!(*lst))
			*lst = new;
		else
			ft_lstlast(*lst)->next = new;
	}
}
