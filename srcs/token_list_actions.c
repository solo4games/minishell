/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_actions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trachell <trachell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:19:07 by lbrandy           #+#    #+#             */
/*   Updated: 2021/10/02 11:21:03 by trachell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	token_pb(t_token **head, char *str)
{
	t_token	*new;
	t_token	*temp;

	temp = *head;
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
	{
		printf("malloc error\n");
		return ;
	}
	new->str = str;
	new->next = NULL;
	if (!(temp))
		*head = new;
	else
	{
		while ((temp)->next)
			temp = temp->next;
		temp->next = new;
	}
}
