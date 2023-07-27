/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:48:53 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/27 22:35:19 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env_list, t_var *var)
{
	while (env_list)
	{
		if (env_list->c == '=')
		{
			write(var->std_out, env_list->key, ft_strlen(env_list->key));
			write(var->std_out, "=", 1);
			if (env_list->val)
				write(var->std_out, env_list->val, ft_strlen(env_list->val));
			write(var->std_out, "\n", 1);
		}
		env_list = env_list->next;
	}
}

void	ft_creat_list_env(char **env, t_env **new_env_list)
{
	t_env	*new_env;
	char	*get_cwd;
	char	*str;

	env = creat_env();
	get_cwd = getcwd(NULL, 0);
	str = ft_strjoin(("PWD="), get_cwd);
	new_env = ft_lstnew_env(str, env);
	ft_lstadd_back_env(new_env_list, new_env);
	free(str);
	str = ft_strdup("SHLVL=1");
	new_env = ft_lstnew_env(str, env);
	ft_lstadd_back_env(new_env_list, new_env);
	free(str);
	str = ft_strjoin(("_="), "/usr/bin/env");
	new_env = ft_lstnew_env(str, env);
	ft_lstadd_back_env(new_env_list, new_env);
	free(str);
	str = ft_strdup("OLDPWD");
	new_env = ft_lstnew_env(str, env);
	ft_lstadd_back_env(new_env_list, new_env);
	free(str);
	free_double(env);
	free(get_cwd);
}

void	make_copy_env_list_char(char **env, t_env **new_env_list)
{
	t_env	*new_env;
	int		i;

	i = 0;
	if (!env[i])
		ft_creat_list_env(env, new_env_list);
	else
	{
		while (env[i])
		{
			new_env = ft_lstnew_env(env[i], env);
			ft_lstadd_back_env(new_env_list, new_env);
			i++;
		}
	}
}

char	**creat_env(void)
{
	char	**env;
	char	*str;

	env = (char **)malloc((sizeof(char *) * 4));
	if (!env)
		affiche_error();
	str = getcwd(NULL, 0);
	env[0] = ft_strjoin(("PWD="), str);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	free(str);
	return (env);
}
