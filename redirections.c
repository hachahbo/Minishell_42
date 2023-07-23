/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 06:34:56 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/01 06:53:02 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redirection(char *str)
{
	if(!ft_strcmp(str, "<<"))
		return (1);
	if(!ft_strcmp(str, "<"))
		return (1);
	if(!ft_strcmp(str, ">>"))
		return (1);
	if(!ft_strcmp(str, ">"))
		return (1);
	return (0);
}

int check_redirection(t_list *head)
{
	while(head)
	{
		if(is_redirection(head->content) 
			&& (!head->next || ft_empty(head->next)))
		{
			printf("syntax Error\n");
			return (1);
		}
		head = head ->next;
	}
	return (0);
}