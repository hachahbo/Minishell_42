/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 06:26:17 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/21 18:25:14 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_strstr(char *str, char *to_find)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	if (to_find[0] == '\0')
// 		return (0);
// 	while (str[i] != '\0')
// 	{
// 		while (str[i + j] != '\0' && str[i + j] == to_find[j])
// 			j++;
// 		if (to_find[j] == '\0')
// 			return (1);
// 		j = 0;
// 		i++;
// 	}
// 	return (0);
// }

// int  is_variable(char *str, t_list *env_list)
// {
// 	char *s;
// 	int i;

	
// 	while(env_list)
// 	{
// 		 i = 0;
// 		if(ft_strstr(env_list->content, str))
// 		{
// 			s = env_list->content;
// 			while(s[i] != '=')
// 				i++;
// 			if(s[i] == '=')
// 				i++;
// 			s = s + i;
// 			printf("%s \n", s);
// 			return (1);
// 		}
// 		else
// 			env_list = env_list->next;
// 	}
// 	return (0);
// }
// int  ft_search_in_env(t_list *env_list, t_list *head)
// {
// 	head = head->next;
// 	while(head && is_spaces(head ->content))
// 		head = head->next;
// 	if(!ft_strcmp(head->content, "$"))
// 	{
// 		is_variable(head ->next->content, env_list);
// 		return (1);
// 	}
// 	return (0);
// }



// int	check_next_of_echo(t_list *head)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	(void)head;
// 	while(head->cmd[i])
// 	{
// 		j = 0;
// 		while(head->cmd[i][j])
// 			j++;
// 		i++;
// 	}
// 	if(!head->cmd[i])
// 	{
// 		printf("\n");
// 		return (1);
// 	}
// 	return (0);
// }
int	check_is_n_line(char *str)
{
	int i;

	i = 0;
	if(str[i] == '-')
	{
		while(!is_spaces_char(str[i]) && str[i])
			i++;
		if(is_spaces_char(str[i]) && str[i])
			return (0);
		i = 1;
		if(str[i] == 'n')
		{
			while(str[i] == 'n' && str[i])
				i++;
			if(str[i] == '\0')
				return (1);
			if(str[i] != 'n' || is_spaces_char(str[i]))
				return (0);
			return (1);
		}
	}
	return (0);
}
int ft_echo(t_list *head)
{
	int i;
	int j;
	char **d_str;

	i = 0;
	j = 0;
	
	d_str = head->cmd;
	i = 1;
	while (head->cmd[i])
	{
		if(!check_is_n_line(head->cmd[i]))
			break;
		if(head->cmd[i] && check_is_n_line(head->cmd[i]))
		{
			j = 1;
		}
		i++;
	}
	while(head->cmd[i])
	{
		if (head->cmd[i+1]  == NULL)
			printf("%s", head->cmd[i]);
		else
			printf("%s ", head->cmd[i]);
		i++;
	}
	if (j == 0)
		printf("\n");
	return (0);
}