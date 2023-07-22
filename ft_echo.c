/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 06:26:17 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/22 14:42:05 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_spaces_char(char c)
{
	if(c == ' ' || c == '\n' ||  c == '\t')
		return (1);
	return (0);
}

int	check_is_n_line(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		while (!is_spaces_char(str[i]) && str[i])
			i++;
		if (is_spaces_char(str[i]) && str[i])
			return (0);
		i = 1;
		if (str[i] == 'n')
		{
			while (str[i] == 'n' && str[i])
				i++;
			if (str[i] == '\0')
				return (1);
			if (str[i] != 'n' || is_spaces_char(str[i]))
				return (0);
			return (1);
		}
	}
	return (0);
}
int	ft_echo(t_list *head, t_var *var)
{
	int		i;
	int		j;
	char	**d_str;

	i = 0;
	j = 0;
	d_str = head->cmd;
	i = -1;
	while (head->cmd[++i])
	{
		if (!check_is_n_line(head->cmd[i]))
			break ;
		if (head->cmd[i] && check_is_n_line(head->cmd[i]))
			j = 1;
	}
	while (head->cmd[++i])
	{
		if (head->cmd[i + 1] == NULL)
		{
			write(var->std_out, head->cmd[i], ft_strlen(head->cmd[i]));
			write(var->std_out, " ", 1);
		}
		else
		{
			write(var->std_out, head->cmd[i], ft_strlen(head->cmd[i]));
			write(var->std_out, " ", 1);
		}
	}
	if (j == 0)
		write(var->std_out, "\n", 1);
	return (0);
}