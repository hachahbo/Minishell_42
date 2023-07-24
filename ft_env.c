/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:48:53 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/23 23:46:15 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env_list, t_var *var)
{
	while (env_list)
	{
		// if (!ft_strcmp(env_list->key, "000"))
		// 	env_list = env_list->next;
		// if (!env_list)
		// 	return ;
		if (env_list->c == '=')
		{
			write(var->std_out, env_list->key, ft_strlen(env_list->key));
			write(var->std_out, "=", 1);
			write(var->std_out, env_list->val, ft_strlen(env_list->val));
			write(var->std_out, "\n", 1);
		}
		env_list = env_list->next;
	}
}