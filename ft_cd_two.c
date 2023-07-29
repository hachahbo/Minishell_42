/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 09:59:51 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/29 15:02:38 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inside_change_the_pwd(t_env *save)
{
	char	*str;
	char	*help;

	help = save->val;
	str = getcwd(NULL, 0);
	if (!str)
	{
		save->val = ft_strjoin(save->val, ft_strdup("/.."));
		save->c = '=';
		free(save->content);
		free(save->val);
		save->content = ft_strjoin("PWD=", save->val);
		free(help);
	}
	else
	{
		save->val = getcwd(NULL, 0);
		save->c = '=';
		free(save->content);
		save->content = ft_strjoin("PWD=", save->val);
		free(help);
	}
	free(str);
}

void	change_the_pwd(t_env **env_list)
{
	t_env	*save;

	save = *env_list;
	while (save)
	{
		if (!ft_strcmp(save->key, "PWD"))
			inside_change_the_pwd(save);
		save = save->next;
	}
}

void	change_the_oldpwd(t_env **env_list)
{
	t_env	*save;
	char	*str;
	char	*str2;
	char	*help;

	save = *env_list;
	while (save)
	{
		if (!ft_strcmp(save->key, "OLDPWD"))
		{
			str2 = getcwd(NULL, 0);
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

void	cd_change_pwd(t_env **env_list, char *str)
{
	change_the_oldpwd(env_list);
	if (chdir(str) == -1)
		printf("bash: cd: %s: No such file or directory\n", str);
	change_the_pwd(env_list);
}
