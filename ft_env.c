/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:48:53 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/14 12:16:18 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_env(t_list *env_list)
// {
// 	 while(env_list)
//     {
//         env_list = env_list->next;
//     }
// }
void	ft_env(t_env *env_list)
{
	 while(env_list)
    {
        // if(env_list->c == '=')
        //     printf("%s=%s\n", env_list->key, env_list->val);
        if(ft_strchr(env_list->content, '='))
            printf("%s\n", env_list->content);
        env_list = env_list->next;
    }
}
