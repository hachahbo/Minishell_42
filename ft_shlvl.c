/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:04:45 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/27 23:07:41 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_value_of_shlvl(char *value, t_env *env_list, t_env *tm, int i)
{
	int		lvl;
	char	*tmp;
	char	*new_shlvl;

	lvl = ft_atoi(value) + 1;
	tmp = ft_itoa(lvl);
	new_shlvl = ft_strjoin("SHLVL=", tmp);
	free(env_list->content);
	env_list->content = new_shlvl;
	free(env_list->val);
	env_list->val = ft_strdup(tmp);
	free(tmp);
	ft_change_all_d_s(tm, new_shlvl, i);
}

void	ft_change_shlvl(t_env *env_list)
{
	char	*value;
	int		i;
	t_env	*tm;

	tm = env_list;
	value = NULL;
	i = 0;
	while (env_list)
	{
		if (ft_strncmp("SHLVL=", env_list->content, ft_strlen("SHLVL=")) == 0)
		{
			value = &env_list->content[ft_strlen("SHLVL=")];
			break ;
		}
		env_list = env_list->next;
		i++;
	}
	if (!value)
		return ;
	ft_change_value_of_shlvl(value, env_list, tm, i);
}

void	ft_change_all_d_s(t_env *env_list, char *new_shlvl, int i)
{
	while (env_list)
	{
		free(env_list->env[i]);
		env_list->env[i] = ft_strdup(new_shlvl);
		env_list = env_list->next;
	}
}
