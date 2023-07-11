/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 20:13:17 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/11 14:51:54 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void make_copy_env_list_char(char **env, t_env **new_env_list)
{
    t_env *new_env;
	int i;
    
	i = 0;
    while(env[i])
    {
        new_env = ft_lstnew_env(env[i]);
        ft_lstadd_back_env(new_env_list, new_env);
        i++;
    }
    
}

int ft_builtins(t_list *list, t_list *env_list, t_env *help)
{
	// printf("teste : %s\n", list->cmd[0]);
	(void)env_list; 
	// t_env *new_env_list = NULL;
	
	while(list)
	{
		if(!ft_strcmp(list->content, "cd"))
			rendering_cd(list);
		if(!ft_strcmp(list->cmd[0], "echo"))
			ft_echo(list);
		else if(!ft_strcmp(list->cmd[0], "env"))
			ft_env(help);
		else if (!ft_strcmp(list->cmd[0], "export"))
			ft_export(list, help);
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