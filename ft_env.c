/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:48:53 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/11 08:50:39 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_env(t_list *env_list)
// {
// 	 while(env_list)
//     {
//         if(ft_strchr(env_list->content, '='))
//             printf("%s\n", env_list->content);
//         env_list = env_list->next;
//     }
// }
void	ft_env(t_env *env_list)
{
	 while(env_list)
    {
        if(ft_strchr(env_list->content, '='))
            printf("%s\n", env_list->content);
        env_list = env_list->next;
    }
}
