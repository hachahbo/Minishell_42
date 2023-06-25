/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 20:13:17 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/24 17:46:44 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_builtins(t_list *list, t_list *env_list, char **env)
{
	// printf("teste : %s\n", list->cmd[0]);
	while(list)
	{
		if(!ft_strcmp(list->content, "cd"))
			rendering_cd(list);
		if(!ft_strcmp(list->cmd[0], "echo"))
			ft_echo(list);
		else if(!ft_strcmp(list->cmd[0], "env"))
			ft_env(env_list);
		else if (!ft_strcmp(list->cmd[0], "export"))
			ft_export(list, env_list, env);
		// // else if(!ft_strcmp(list->content  
		// else if(!ft_strcmp(list->content, "exit"))
		// {
		// 	printf("exit\n");
		// 	exit(1);
		// }
		list = list->next;
	}
	return (0);
}