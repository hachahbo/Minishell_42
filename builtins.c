/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 20:13:17 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/06 14:06:22 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_builtins(t_list *new_list_w_d_q, t_list *env_list)
{
	while(new_list_w_d_q)
	{
		if(!ft_strcmp(new_list_w_d_q->content, "cd"))
			rendering_cd(new_list_w_d_q);
		else if(!ft_strcmp(new_list_w_d_q->content, "echo"))
			ft_echo(env_list, new_list_w_d_q);
		else if(!ft_strcmp(new_list_w_d_q->content, "env"))
			ft_env(env_list);
		else if(!ft_strcmp(new_list_w_d_q->content, "pwd"))
			ft_pwd(env_list);
		else if(!ft_strcmp(new_list_w_d_q->content, "exit"))
		{
			printf("exit\n");
			exit(1);
		}
		new_list_w_d_q = new_list_w_d_q->next;
	}
	return (0);
}