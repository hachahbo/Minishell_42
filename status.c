/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 06:36:53 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/01 06:53:50 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_status(t_list *new, int *flag1, int *flag2)
{
	if(!ft_strcmp(new->content, "\"")&& *flag2 == 1)
		new->state = IN_QUOTE;
	else if(!ft_strcmp(new->content, "\'") && *flag1 == 1)
		new->state = IN_DQUOTE;
	else if(!ft_strcmp(new->content, "\"")&& *flag1 == 0)
	{
		new->state = GENERAL;
		*flag1 = 1;
	}
	else if (!ft_strcmp(new->content, "\"")&& *flag1 == 1)
	{
		new->state = GENERAL;
		*flag1 = 0;
	}
	else if (!ft_strcmp(new->content, "\'") && *flag2 == 0)
	{
		new->state = GENERAL;
		*flag2 = 1;
	}
	else if (!ft_strcmp(new->content, "\'") && *flag2 == 1)
	{
		new->state = GENERAL;
		*flag2 = 0;
	}
	else if (*flag1 == 0 && *flag2 == 0)
		new->state = GENERAL;
	else if (*flag1 == 1)
		new->state = IN_DQUOTE;
	else if (*flag2 == 1)
		new->state = IN_QUOTE;
}