/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 06:09:13 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/01 06:13:40 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_env_list(char **env, t_list **env_list)
{
	int	i;
	t_list *new;

	while(env[i])
	{
		new = ft_lstnew(env[i]);
		ft_lstadd_back(env_list, new);
		i++;
	}
}

void ft_make_list(char *input, t_list **head)
{
	int flag1;
	int flag2;
	t_list *new;
	char  *str;
	int start;
	int end;
	
	start = 0;
	end = 0;
	flag1 = 0;
	flag2 = 0;
	while (1)
	{
		input = skip_spaces(input);
		str = check_data(input, &start, &end);
		if(str == NULL)
		{
			free(str);
			break ;
		}
		new = ft_lstnew(str);
		ft_status(new, &flag1, &flag2);
		ft_lstadd_back(head, new);
		free(str);
	}
}