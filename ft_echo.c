/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 06:26:17 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/01 06:26:29 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(t_list *env_list, t_list *head)
{
	int flag;

	flag = 0;
	while(head)
	{
		if(!ft_strcmp(head->content, "echo"))
			break;
		head = head->next;
	}
	if(!head)
		return (0);
	head = head->next;
	while(is_spaces(head ->content))
		head = head->next; 
	while(head)
	{
		if(!is_spaces(head ->content))
		{
			if(head->next  == NULL)
				printf("%s", head->content);
			else
				printf("%s ", head->content);
		}
		head = head->next;
	}
	printf("\n");
	return (0);
}