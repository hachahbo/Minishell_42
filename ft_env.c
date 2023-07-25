/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:48:53 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/25 16:00:37 by amoukhle         ###   ########.fr       */
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