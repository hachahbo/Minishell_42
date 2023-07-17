/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:43:57 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/17 09:16:51 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_list *env_list)
{
    (void) env_list;
    printf("%s\n", getcwd(NULL, 0));
}
