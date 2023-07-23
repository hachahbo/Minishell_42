/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:25:45 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/23 01:13:02 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

void	ft_cd(char *path)
{
	chdir(path);
}
void change_the_PWD(t_env **env_list)
{
	t_env *save;

	save = *env_list;
	while((*env_list))
	{
		if(!ft_strcmp((*env_list)->key, "PWD"))
			(*env_list)->val = getcwd(NULL, 0);
		(*env_list) = (*env_list)->next;
	}
	env_list = &save;
}
void change_the_OLDPWD(t_env **env_list)
{
	t_env *save;


	save = *env_list;
	while((*env_list))
	{
		if(!ft_strcmp((*env_list)->key, "OLDPWD"))
		{
			(*env_list)->val = getcwd(NULL, 0);
			(*env_list)->c = '=';
			
		}
		(*env_list) = (*env_list)->next;
	}
	env_list = &save;
}
int ft_check_args_of_cd(t_list *head, t_env *env_list)
{
	char *new_path;
	t_env *save;
	
	if(!head->cmd[1] || !ft_strcmp(head ->cmd[1], "~"))
	{
		save = env_list;
		new_path = getenv("HOME");
		ft_cd(new_path);
		env_list = save;
		change_the_PWD(&env_list);
	}
	else if(!ft_strcmp(head->cmd[1], ".."))
	{
		save = env_list;
		change_the_OLDPWD(&env_list);
		ft_cd("..");
		env_list = save;
		change_the_PWD(&env_list);
	}
	else if(!ft_strcmp(head->cmd[1], "."))
	{
		save = env_list;
		change_the_OLDPWD(&env_list);
		ft_cd(".");
		env_list = save;
		change_the_PWD(&env_list);
	}	
	else if(!ft_strcmp(head->cmd[1], "/"))
	{
		save = env_list;
		change_the_OLDPWD(&env_list);
		ft_cd("/");
		env_list = save;
		change_the_PWD(&env_list);
	}
	else
	{
		save = env_list;
		change_the_OLDPWD(&env_list);
		ft_cd(head->cmd[1]);
		env_list = save;
		change_the_PWD(&env_list);
	}
	return (0);
}
int rendering_cd(t_list *list,  t_env *env_list)
{
	if(list  == NULL)
		return (0);

	ft_check_args_of_cd(list, env_list);
	return (0);
}