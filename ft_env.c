/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:48:53 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/17 04:56:38 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env_list)
{
	 while(env_list)
    {
        if(!ft_strcmp(env_list->key, "000"))
		    env_list = env_list->next;
	    if(!env_list)
		    return ;
        if(env_list->c == '=')
            printf("%s=%s\n", env_list->key, env_list->val);
        env_list = env_list->next;
    }
}
