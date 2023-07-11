/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 06:31:48 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/10 08:14:34 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_pipes(t_list *head)
{
	int x;
	int c = 0;

	x = 0;
	if(!ft_strcmp(head->content, "|"))
	{
		printf("syntax Error\n");
		return (1);
	}
	while(1)
	{
		if(!(is_spaces(head->content)) && c == 0)
		{
			c = 1;
			x++;
		}
		if(!head->next || ft_strcmp(head->content, "|") == 0)
			break;
		if(!(is_spaces(head->content)))
			x++;
		head = head->next;
	}
	while(head)
	{
		if((!ft_strcmp(head->content, "|") && (!head->next || ft_empty(head->next))) || !x)
		{
			printf("syntax Error\n");
			return (1);
		}
		head = head->next;
	}
	return (0);
}