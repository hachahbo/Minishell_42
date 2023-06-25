/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:56:21 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/25 23:37:25 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_small(t_list *list)
{
    char *min;

    min = list->content;
    while(list->next)
    {
        if(ft_strcmp(min, list->next->content) > 0)
            min = list->next->content;
        list = list->next;
    }
    return(min);
}
void remove_node(t_list** head, char *min)
 {
    t_list* current = *head;
    t_list* previous = NULL;

    while (current != NULL)
    {
        if (!ft_strcmp(current->content, min)) 
        {
            if (previous == NULL)
                *head = current->next;
            else 
                previous->next = current->next;
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void add_node_to_list(t_list** head, t_list *new)
{
    if (*head == NULL)
    {
        *head = new;
        return ;
    }
    // if the new node should be inserted at the beginning
    // if (new->content < (*head)->content)
    if(ft_strcmp(new->content, (*head)->content) < 0)
    {
        new->next = *head;
        *head = new;
        return;
    }
    // traverse the list to find the appropriate position to insert the new node
    t_list* current = *head;
    while (current->next != NULL && ft_strcmp(current->next->content, new->content) < 0)
        current = current->next;
    // insert the new node in the middle or at the end
    new->next = current->next;
    new->type = WORD;
    current->next = new;
}

void	make_copy_env_list(t_list *env_list, t_list **copy_env)
{
	int		i;
	t_list	*new;

	i = 0;
	while(env_list)
	{
		new = ft_lstnew(env_list->content, NULL);
		ft_lstadd_back(copy_env, new);
		env_list = env_list->next;
	}
}
char *until_equal(char *big_str)
{
    char *str;
    int     i;

    i = 0;
    while(!ft_strchr(big_str, '=') && big_str[i])
        i++;
    // if(big_str[i] == '\0')
    //     return (0);
    str = malloc(sizeof(char) * i + 1);
    i = 0;
    while(!ft_strchr(big_str, '=') && big_str[i])
    {
        str[i] = big_str[i];
        i++;
    }
    str[i] = '\0';
    return (str);
} 
int  check_double_nodes(t_list *new, t_list **env_list)
{
    char    *str;
    char    *str2;
    char *save;
    t_list *head;

    head = *env_list;
    
    str = until_equal(new->content);
    while(*env_list)
        {
            str2 = until_equal(new->content);
            if(!ft_strcmp(str, str2))
            { 
                save = ft_strchr(new->content , '=');
                if(!save)
                    return (1);
                (*env_list)->content = new->content;
                return (1);
            }
            (*env_list) = (*env_list)->next;
        }
    
    env_list = &head;
    return (0);
}

void print_the_node(t_list *node)
{
    int i;
    char *str;

    i = 0;
    printf("declare -x ");
    if(!ft_strchr(node->content, '='))
    {
        printf("%s\n", node->content);
        return ;
    }
    while(node->content[i] != '=')
    {
        printf("%c", node->content[i]);
        i++;
    }
    printf("%c", node->content[i]);
    printf("\"");
    str = ft_strchr(node->content, '=');
    i = 1;
    while(str[i])
    {
        printf("%c", str[i]);
        i++;
    }
    printf("\"");
    printf("\n");
}

void print_export(t_list *export_list)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    while(export_list)
    {
        if(export_list->type == WORD)
            print_the_node(export_list);
        else
            printf("declare -x %s\n", export_list->content);
        export_list = export_list->next;
    } 
}
void ft_export(t_list *head, t_list *env_list, char **env)
{
    char *min;
    int i;
    t_list *new;
    t_list *export_list = NULL;
    t_list *copy_env = NULL;
        
    (void)head;
    (void)env;
    (void)env_list;
    i = 1;
    if(head->cmd[1])
    {
        while(head->cmd[i])
        {
            new = ft_lstnew(head->cmd[i], NULL);
            new->type = 1; 
            if(!check_double_nodes(new, &env_list))
                add_node_to_list(&env_list, new);
            i++;
        }
    }   
    make_copy_env_list(env_list, &copy_env);
    while(1)
    {
        if(copy_env == NULL)
            break;
        min = find_small(copy_env);
        new = ft_lstnew(min, NULL);
        ft_lstadd_back(&export_list, new);
        remove_node(&copy_env, min);
    }
    if(!head->cmd[1])
        print_export(export_list);
}
