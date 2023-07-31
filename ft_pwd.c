/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:43:57 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/30 21:13:52 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_env *env_list, t_var *var)
{
	char	*str;
	t_env	*save;

	save = env_list;
	str = NULL;
	while (save)
	{
		if (!ft_strcmp(save->key, "PWD"))
			str = save->val;
		save = save->next;
	}
	if (str)
	{
		write(var->std_out, str, ft_strlen(str));
		write(var->std_out, "\n", 1);
	}
}
