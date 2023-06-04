/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:43:57 by amoukhle          #+#    #+#             */
/*   Updated: 2023/06/02 01:23:29 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pwd(t_list *env_list)
{
    char *var;
    char *value;
    
    var = "PWD";
    value = NULL;
    while (env_list)
    {
        if (ft_strncmp(var, env_list->content, ft_strlen(var)) == 0)
            value = &env_list->content[ft_strlen(var) + 1];
        env_list = env_list->next;
    }
	if (!value)
		value = getcwd(NULL, 0);
    return (value);
}