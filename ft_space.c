/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 06:21:24 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/21 17:23:58 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_spaces(char *str)
{
	if(!ft_strcmp(str, " ") || !ft_strcmp(str, "\n")
		|| !ft_strcmp(str, "\t"))
		return (1);
	return (0);
}
int is_spaces_char(char c)
{
	if(c == ' ' || c == '\n' ||  c == '\t')
		return (1);
	return (0);
}

int  ft_strisspace(const char* str)
{
    while (*str) {
        if (!isspace(*str))
            return 0;
        str++;
	}
    return 1; 
}

char *skip_spaces(char *input)
{
	int i;
	
	i = 0;
	while((input[i] >=  9 &&  input[i] <= 13) || input[i] == 32)
		i++;
	return(input + i);
}
