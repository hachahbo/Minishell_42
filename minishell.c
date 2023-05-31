/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:55:43 by hachahbo          #+#    #+#             */
/*   Updated: 2023/05/31 16:14:47 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_strcmp(char *s1, char *s2)
{
	int i;
	i = 0;
	while(s1[i] && s2[i] && s1[i] == s2 [i])
		i++;
	return(s1[i] - s2[i]);
}

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
	if(ft_strcmp(c , "\0") == 0)
	{
		return(0);
	}
	while((input[*end] >= 'a' && input[*end] <= 'z') || 
		(input[*end] >= 'A' && input[*end] <= 'Z') 
			|| (input[*end] >= '0' && input[*end] <= '9'))
		*end += 1;
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
	if(ft_strcmp(new->content, "\"") == 0 && *flag2 == 1)
		new->state = IN_QUOTE;
	else if(ft_strcmp(new->content, "\'") == 0 && *flag1 == 1)
		new->state = IN_DQUOTE;
	else if(ft_strcmp(new->content, "\"") == 0 && *flag1 == 0)
	{
		new->state = GENERAL;
		*flag1 = 1;
	}
	else if (ft_strcmp(new->content, "\"") == 0 && *flag1 == 1)
	{
		new->state = GENERAL;
		*flag1 = 0;
	}
	else if (ft_strcmp(new->content, "\'") == 0 && *flag2 == 0)
	{
		new->state = GENERAL;
		*flag2 = 1;
	}
	else if (ft_strcmp(new->content, "\'") == 0 && *flag2 == 1)
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
int check_d_quote(t_list *head)
{
	int x;
	int i;
	t_list *help;
	
	x = 0;
	help = head;
	while(head)
	{
		if(ft_strcmp(head->content, "\"") == 0)
			x++;
		head = head ->next;
	}
	i = 0;
	head = help;
	while(head)
	{
		if(ft_strcmp(head->content, "\'")== 0)
			i++;
		head = head ->next;
	}
	if((x % 2 != 0) || (i % 2 != 0))
	{
		printf("syntax error\n");
		return (1);
	}
	return (0);
		
}
int is_spaces(char *str)
{
	if(ft_strcmp(str, " ") == 0 || ft_strcmp(str, "\n") == 0 || ft_strcmp(str, "\t") == 0)
		return (1);
	return (0);
}
int ft_empty(t_list *head)
{
	int i;

	i = 0;
	while(head->next)
	{
		head = head->next;
	}
	if(is_spaces(head->content) && !head->next)
		return (1);
	return (0);
}
int is_redirection(char *str)
{
	if(!ft_strcmp(str, "<<"))
		return (1);
	if(!ft_strcmp(str, "<"))
		return (1);
	if(!ft_strcmp(str, ">>"))
		return (1);
	if(!ft_strcmp(str, ">"))
		return (1);
	return (0);
}
int check_redirection(t_list *head)
{
	while(head)
	{
		if(is_redirection(head->content) && (!head->next || ft_empty(head->next)))
		{
			printf("syntax Error\n");
			return (1);
		}
		head = head ->next;
	}
	return (0);
}
int check_pipes(t_list *head)
{
	int x;
	int c = 0;

	x = 0;
	while(1)
	{
		if(!(is_spaces(head->content)) && c == 0)
		{
			c = 1;
			x++;
		}
		if(!head->next || ft_strcmp(head->content, "|") == 0)
			break;
		if(!(is_spaces(head->content)))
			x++;
		head = head->next;
	}
	while(head)
	{
		if((!ft_strcmp(head->content, "|") && (!head->next || ft_empty(head->next))) || !x)
		{
			printf("syntax Error\n");
			return (1);
		}
		head = head->next;
	}
	return (0);
}
int ft_valid_command(t_list *head)
{
	if(check_d_quote(head))
		return (1);
	if(check_redirection(head))
		return (1);
	if(check_pipes(head))
		return (1);
	return (0);
}
void f()
{
	system("leaks minishell");
}
int main(int ac, char **av, char **env)
{
    char *input;
	t_list *head;

	head = NULL;
	// atexit(f);
    while(1)
	{
		input = readline("[minishell][$]~> ");
    	if (!input || ft_strcmp(input, "\0") == 0)
        	exit (1);
		if(ft_strisspace(input))
			break ;
		ft_make_list(input, &head);
		if(ft_valid_command(head) == 0)
			printlist(head);
		ft_lstclear(&head);
		if(strlen(input) > 0)
			add_history(input);
   		free(input);
	}
    return (0);
}