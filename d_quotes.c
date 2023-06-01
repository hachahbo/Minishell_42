/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 06:28:18 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/01 06:29:02 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_d_quote(t_list *head)
{
	int x;
	int i;
	t_list *help;

	x = 0;
	help = head;
	while(head)
	{
		if(ft_strcmp(head->content, "\"") == 0)
			x++;
		head = head ->next;
	}
	i = 0;
	head = help;
	while(head)
	{
		if(ft_strcmp(head->content, "\'")== 0)
			i++;
		head = head ->next;
	}
	if((x % 2 != 0) || (i % 2 != 0))
	{
		printf("syntax error\n");
		return (1);
	}
	return (0);		
}