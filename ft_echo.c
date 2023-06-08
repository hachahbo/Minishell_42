/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 06:26:17 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/07 14:13:27 by amoukhle         ###   ########.fr       */
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
int check_next_of_echo(t_list *head)
{

	head = head->next;
	while(head && is_spaces(head->content))
		head = head->next;
	if(!head)
	{
		printf("\n");
		return (1);
	}
	return (0);
}
int ft_echo(t_list *head)
{
	// while(head)
	// {
	// 	if(!ft_strcmp(head->content, "echo"))
	// 		break;
	// 	head = head->next;
	// }
	if(!head->next)
	{
		printf("\n");
		return (1);
	}
	if(check_next_of_echo(head))
		return (1);
	head = head->next;
	while(head && is_spaces(head ->content))
		head = head->next;
	while(head)
	{
		if(!is_spaces(head ->content))
		{
			if(!ft_strcmp(head->content, "-n"))
			{
				printf("");
				return (0);
			}
			else if(head->next  == NULL)
				printf("%s", head->content);
			else
				printf("%s ", head->content);
		}
		head = head->next;
	}
	printf("\n");
	return (0);
}