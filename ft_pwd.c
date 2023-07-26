/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:43:57 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/26 10:34:12 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_env *env_list, t_var *var)
{
    char    *str;
	t_env *save = env_list;

	while(save)
	{
		if(!ft_strcmp(save->key, "PWD"))
		str = save->val;
		save= save->next;
	}
    if (str)
    {
        write(var->std_out, str, ft_strlen(str));
        write(var->std_out, "\n", 1);
    }
}


