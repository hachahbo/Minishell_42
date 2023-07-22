/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:43:57 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/22 15:06:17 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_env *env_list, t_var *var)
{
    char    *str;

    (void)env_list;
    str = getcwd(NULL, 0);
    if (str)
    {
        write(var->std_out, str, ft_strlen(str));
        write(var->std_out, "\n", 1);
    }
}


