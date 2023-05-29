/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:55:43 by hachahbo          #+#    #+#             */
/*   Updated: 2023/05/29 15:26:42 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int  ft_strisspace(const char* str) {
    while (*str) {
        if (!isspace(*str))
            return 0;
        str++;
	}
    return 1; 
}
void	ft_lstclear(t_list **lst)
{
	t_list	*temp;
	t_list	*freed;

	temp = *lst;
	while (temp != NULL)
	{
		freed = temp;
		temp = temp->next;
		free(freed->content);
		free(freed);
	}
	*lst = NULL;
}
char *skip_spaces(char *input)
{
	int i;
	
	i = 0;
	while((input[i] >=  9 &&  input[i] <= 13) || input[i] == 32)
		i++;
	return(input + i);
}
char *check_data(char *input, int *start, int *end)
{
	char *str;
	char *c;
	int temp;

	temp = *end;
	c = (input + *end);
	if(strcmp(c , "\0") == 0)
	{
		return(0);
	}
	while((input[*end] >= 'a' && input[*end] <= 'z') || 
		(input[*end] >= 'A' && input[*end] <= 'Z') || (input[*end] >= '0' && input[*end] <= '9'))
	{
		*end += 1;
	}
	if (temp == *end)
	{

		if((input[*end] == '>' && input[*end + 1] == '>') 
			|| (input[*end] == '<' && input[*end + 1] == '<'))
			*end += 1;
		*end += 1;
		str = ft_substr(input, *start, *end - *start);
		*start = *end;
		return(str);
	}
	str = ft_substr(input, *start, *end - *start);
	*start = *end;
	return(str);
}

void printlist(t_list *head)
{
	printf("command			state			token\n");
	while(head)
	{
		printf("\"%s\"			%d			%d\n", head->content, head->state, head->type);
		head= head->next;
	}
	printf("\n");
}
void ft_status(t_list *new, int *flag1, int *flag2)
{
	if(strcmp(new->content, "\"") == 0 && *flag2 == 1)
		new->state = IN_QUOTE;
	else if(strcmp(new->content, "\'") == 0 && *flag1 == 1)
		new->state = IN_DQUOTE;
	else if(strcmp(new->content, "\"") == 0 && *flag1 == 0)
	{
		new->state = GENERAL;
		*flag1 = 1;
	}
	else if (strcmp(new->content, "\"") == 0 && *flag1 == 1)
	{
		new->state = GENERAL;
		*flag1 = 0;
	}
	else if (strcmp(new->content, "\'") == 0 && *flag2 == 0)
	{
		new->state = GENERAL;
		*flag2 = 1;
	}
	else if (strcmp(new->content, "\'") == 0 && *flag2 == 1)
	{
		new->state = GENERAL;
		*flag2 = 0;
	}
	else if (*flag1 == 0 && *flag2 == 0)
		new->state = GENERAL;
	else if (*flag1 == 1)
		new->state = IN_DQUOTE;
	else if (*flag2 == 1)
		new->state = IN_QUOTE;
	
}
void ft_make_list(char *input, t_list **head)
{
	int flag1;
	int flag2;
	t_list *new;
	char  *str;
	int start;
	int end;
	
	start = 0;
	end = 0;
	flag1 = 0;
	flag2 = 0;
	while (1)
	{
		input = skip_spaces(input);
		str = check_data(input, &start, &end);
		if(str == NULL)
		{
			free(str);
			break ;
		}
		new = ft_lstnew(str);
		ft_status(new, &flag1, &flag2); 
		ft_lstadd_back(head, new);
		free(str);
	}
}

int main()
{
    char *input;
	t_list *head;

	head = NULL;
    while(1)
	{
		input = readline("[minishell][$]~> ");
    	if (!input || strcmp(input, "\0") == 0)
        	exit (1);
		if(ft_strisspace(input))
			break ;
		ft_make_list(input, &head);
		printlist(head);
		ft_lstclear(&head);
		if(strlen(input) > 0)
			add_history(input);
   		free(input);
	}
	system("leaks minishell");
    return (0);
}