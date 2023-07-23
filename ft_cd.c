/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:25:45 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/23 11:06:31 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// else if(!ft_strcmp(head->cmd[1], "-"))
	change_the_OLDPWD(&env_list);
	// if(!(!ft_strcmp(str, "-")))
		ft_cd(str);
	env_list = save;
	change_the_PWD(&env_list);

	// printf(" ->>>>%s\n", s1);
	// // printf(" ->>>>%s\n", s2);
	
	// if(!ft_strcmp(str, "-"))
	// {
	// 	// printf("->>>>>>>>>>>>%d\n", x);
	// 	if(!s1)
	// 		printf("cd: OLDPWD not set");
	// 	if(x ==  2)
	// 	{
	// 		env_list = save;
	// 		s1 = change_the_PWD(&env_list);
	// 		ft_cd(s1);
	// 		printf("->>%s\n",s1);
	// 	}
	// 	if(x ==  1)
	// 	{
	// 		env_list = save;
	// 		s2 =change_the_OLDPWD(&env_list);
	// 		ft_cd(s2);
	// 		printf("%s\n",s2);
	// 	}
		// ft_dash(env_list,  x);
	// }
}

// void	ft_dash(t_env *env_list, int x)
// {
// 	t_env *save;
// 	char *str;
	
// 	save = env_list;
// 	if(x == 1)
// 	{
// 		env_list = save;
// 		str = change_the_OLDPWD(&env_list);
// 		ft_cd(str);
// 		printf("%s\n",str);
// 	}
// 	else if(x == 2)
// 	{
// 		env_list = save;
// 		str = change_the_PWD(&env_list);
// 		ft_cd(str);
// 		printf("%s\n",str);
// 	}
// 	env_list = save;
// }
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
	// {
	// 	x = (x % 2) + 1;
	// 	cd_change_pwd(env_list, head->cmd[1], x);
	// }
	else
		cd_change_pwd(env_list, head->cmd[1], x);
		
	
	return (0);
}
int rendering_cd(t_list *list,  t_env *env_list)
{
	if(list  == NULL)
		return (0);

	ft_check_args_of_cd(list, env_list);
	return (0);
}