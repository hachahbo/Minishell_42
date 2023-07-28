/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:25:45 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/28 12:33:59 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_the_PWD(t_env **env_list)
{
	t_env	*save;
	char	*help;

	save = *env_list;
	while(save)
	{
		if(!ft_strcmp(save->key, "PWD"))
		{
			help = save->val;
			if(!getcwd(NULL, 0))
			{
				save->val = ft_strjoin(save->val, ft_strdup("/.."));
				save->c = '=';
				free(save->content);
				free(save->val);
				save->content = ft_strjoin("PWD=", save->val);
			}
			else
			{
				save->val = getcwd(NULL, 0);
				save->c = '=';
				free(save->content);
				save->content = ft_strjoin("PWD=", save->val);
			}
			free(help);
			system("leaks minishell");
		}
		save = save->next;
	}
}

void	change_the_OLDPWD(t_env **env_list)
{
	t_env	*save;
	char	*str;
	char	*str2;
	char	*help;

	save = *env_list;
	while(save)
	{
		if(!ft_strcmp(save->key, "OLDPWD"))
		{
			str2  = getcwd(NULL, 0);
			help = ft_strjoin("=", str2);
			str = ft_strjoin("OLDPWD", help);
			free(help);
			free(str2);
			help = save->content;
			save->content = str;
			free(help);
			help = save->val;
			save->val = getcwd(NULL, 0);
			save->c = '=';
			free(help);
		}
		save = save->next;
	}
}

void cd_change_pwd(t_env **env_list, char *str, int x)
{
	(void)x;
	change_the_OLDPWD(env_list);
	chdir(str);
	change_the_PWD(env_list);

}

void check_the_path(int *x)
{

	(void)x;
	if(!getcwd(NULL, 0))
	{
		printf("cd: error retrieving current directory:");
		printf(" getcwd: cannot access parent directories: No such file or directory\n");
	}
}
int ft_check_args_of_cd(t_list *head, t_env **env_list, char **env)
{
	static int x = 0;
	char *str = NULL;
	t_env *save = *env_list;
	
	if(!head->cmd[1] || !ft_strcmp(head ->cmd[1], "~"))
	{
		if(!env[0])
		{
			if(!head->cmd[1])
				printf("bash: cd: HOME not set\n");
			else if(!ft_strcmp(head ->cmd[1], "~"))
				cd_change_pwd(env_list, "/Users/hachahbo", x);
		}
    	else
		{
			while(save)
			{
				if(!ft_strcmp(save->val, "/Users/hachahbo"))
				{
					str = save->val;
					break;
				}
				save = save->next;
			}
			cd_change_pwd(env_list, str, x);
		}
	}
	else if(!ft_strcmp(head->cmd[1], ".."))
	{
		cd_change_pwd(env_list, head->cmd[1], x);
		check_the_path(&x);
	}
	else if(!ft_strcmp(head->cmd[1], "."))
		cd_change_pwd(env_list, head->cmd[1], x);
	else if(!ft_strcmp(head->cmd[1], "/"))
		cd_change_pwd(env_list, head->cmd[1], x);
	else
		cd_change_pwd(env_list, head->cmd[1], x);
	return (0);
}
int rendering_cd(t_list *list, t_env **env_list, char **env)
{
	if(list  == NULL)
		return (0);

	ft_check_args_of_cd(list, env_list, env);
	return (0);
}