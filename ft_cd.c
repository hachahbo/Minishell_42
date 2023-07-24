/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:25:45 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/24 01:18:24 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *path)
{
	chdir(path);
}

void	change_the_PWD(t_env **env_list)
{
	t_env *save;
	char *help;

	save = *env_list;
	while((*env_list))
	{
		if(!ft_strcmp((*env_list)->key, "PWD"))
		{
			help = (*env_list)->val;
			(*env_list)->val = getcwd(NULL, 0);
			(*env_list)->c = '=';
			free(help);
		}
		(*env_list) = (*env_list)->next;
	}
	env_list = &save;
}

void	change_the_OLDPWD(t_env **env_list)
{
	t_env *save;
	char *str;
	char *str2;
	char *help;
	save = *env_list;
	while((*env_list))
	{
		if(!ft_strcmp((*env_list)->key, "OLDPWD"))
		{
			str2  = getcwd(NULL, 0);
			help = ft_strjoin("=", str2);
			str = ft_strjoin("OLDPWD", help);
			free(help);
			free(str2);
			help = (*env_list)->content;
			(*env_list)->content = str;
			free(help);
			help = (*env_list)->val;
			(*env_list)->val = getcwd(NULL, 0);
			(*env_list)->c = '=';
			free(help);
		}
		(*env_list) = (*env_list)->next;
	}
	env_list = &save;
}

void cd_change_pwd(t_env *env_list, char *str, int x)
{
	t_env *save;
	
	(void)x;
	save = env_list;
	change_the_OLDPWD(&env_list);
		ft_cd(str);
	env_list = save;
	change_the_PWD(&env_list);
}
int ft_check_args_of_cd(t_list *head, t_env *env_list)
{
	static int x = 0;
	if(!head->cmd[1] || !ft_strcmp(head ->cmd[1], "~"))
		cd_change_pwd(env_list, "/Users/hachahbo", x);
	else if(!ft_strcmp(head->cmd[1], ".."))
		cd_change_pwd(env_list, head->cmd[1], x);
	else if(!ft_strcmp(head->cmd[1], "."))
		cd_change_pwd(env_list, head->cmd[1], x);
	else if(!ft_strcmp(head->cmd[1], "/"))
		cd_change_pwd(env_list, head->cmd[1], x);
	else
		cd_change_pwd(env_list, head->cmd[1], x);
		
	
	return (0);
}
int rendering_cd(t_list *list, t_env *env_list)
{
	if(list  == NULL)
		return (0);

	ft_check_args_of_cd(list, env_list);
	return (0);
}