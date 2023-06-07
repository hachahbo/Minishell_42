/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 20:13:17 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/07 13:53:54 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_builtins(t_list *list, t_list *env_list)
{
	while(list)
	{
		if(!ft_strcmp(list->content, "cd"))
			rendering_cd(list);
		else if(!ft_strcmp(list->content, "echo"))
			ft_echo(list);
		else if(!ft_strcmp(list->content, "env"))
			ft_env(env_list);
		else if(!ft_strcmp(list->content, "pwd"))
			ft_pwd(env_list);
		else if(!ft_strcmp(list->content, "exit"))
		{
			printf("exit\n");
			exit(1);
		}
		list = list->next;
	}
	return (0);
}