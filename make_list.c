/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 06:09:13 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/12 12:57:45 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_env_list(char **env, t_list **env_list)
{
	int		i;
	t_list	*new;

	i = 0;
	while(env[i])
	{
		new = ft_lstnew(env[i], NULL);
		ft_lstadd_back(env_list, new);
		i++;
	}
}

void 	ft_make_list(char *input, t_list **head, t_var *vars)
{
	t_list *new;
	char  *str;

	while (1)
	{
		input = skip_spaces(input);
		str = check_data(input, &vars->start, &vars->end);
		if(str == NULL)
		{
			free(str);
			break ;
		}
		new = ft_lstnew(str, NULL);
		ft_status(new, &vars->flag1, &vars->flag2);
		ft_lstadd_back(head, new);
		free(str);
	}
}

int	serche_for_DOC(t_list *list)
{
	if (list->type == WORD || list->type == Q_MARK)
		list = list->prev;
	if (list->type == ENV)
		list = list->prev;
	while (list && (list->type == WORD || list->type == QOUTE
		|| list->type == DOUBLE_QUOTE || list->type == Q_MARK
		|| list->state == IN_DQUOTE || list->state == IN_QUOTE
		|| list->type == ENV))
		list = list->prev;
	while (list && list->type == WHITE_SPACE && list->state == GENERAL)
		list = list->prev;
	if (list && (list->type == HERE_DOC || list->type == DREDIR_OUT
		|| list->type == REDIR_IN || list->type == REDIR_OUT) && list->state == GENERAL)
		return (0);
	return (1);
}

char *handle_env(t_list *list, t_list *env_list, int num_env)
{
	if ((list->type == ENV && list->state == GENERAL
		&& (list->next == NULL || list->next->type == WHITE_SPACE))
		|| (list->type == ENV && list->state == IN_QUOTE))
		return (list->content);
	else if (list->type == ENV && list->state == GENERAL && num_env % 2 != 0
		&& (list->next->type == QOUTE || list->next->type == DOUBLE_QUOTE))
		return ("");
	else if (list->type == ENV && (list->state == IN_DQUOTE || list->state == GENERAL))
	{
		if (list->next->type == WORD && num_env % 2 != 0 && serche_for_DOC(list) == 1)
				return (ft_expand_value(list->next->content, env_list));
		else if (list->next->type == Q_MARK && num_env % 2 != 0 && serche_for_DOC(list) == 1)
				return (ft_itoa(state_exit));
	}
	return (list->content);
}

int	skip_node(t_list *head, int num_env)
{
	if ((head->type == QOUTE && head->state == GENERAL && serche_for_DOC(head) == 1)
		|| (head->type == DOUBLE_QUOTE && head->state == GENERAL && serche_for_DOC(head) == 1)
		|| ((head->type == WORD || head->type == Q_MARK) && head->prev && head->prev->type == ENV
		&& head->state != IN_QUOTE && num_env % 2 != 0 && serche_for_DOC(head) == 1))
		return (0);
	return (1);
}

int	join_node(t_list *head)
{
	if (head->type == WORD || head->type == ENV || head->type == Q_MARK
		|| head->type == QOUTE || head->type == DOUBLE_QUOTE
		|| head->state == IN_QUOTE || head->state == IN_DQUOTE)
		return (0);
	return (1);
}

void	add_node(t_list **new_list, char *str, int in_join)
{
	t_list *new;

	new = ft_lstnew(str, NULL);
	if (in_join == 0)
		new->state = GENERAL;
	else
		new->state = IN_DQUOTE;
	ft_lstadd_back(new_list, new);
}

char	*generate_value_of_env(char *str, char *tmp, t_list_str **list_str, t_list **new_list)
{
	int		i;
	char	**str_split;

	str_split = ft_split(tmp, ' ');
	i = 0;
	while(str_split[i + 1])
	{
		str = ft_strjoin(str, str_split[i]);
		list_stradd_back(list_str, new_list_str(str));
		i++;
		ft_lstadd_back(new_list, ft_lstnew(str, NULL));
		str = NULL;
	}
	str = ft_strjoin(str, str_split[i]);
	list_stradd_back(list_str, new_list_str(str));
	free_double(str_split);
	return (str);
}

char	*join_list_str(char *s1, char *s2, t_list_str **list_str)
{
	s1 = ft_strjoin(s1, s2);
	list_stradd_back(list_str, new_list_str(s1));
	return (s1);
}

void	ft_make_new_list(t_list *head, t_list **new_list, t_list *env_list, t_list_str **list_str)
{
	char	*str;
	char	*tmp;
	int		in_join;
	int		num_env;
	char	**str_split;

	num_env = 0;
	while (head)
	{
		in_join = 0;
		str = NULL;
		if (head->type != WORD && head->type != QOUTE && head->type != Q_MARK
			&& head->type != DOUBLE_QUOTE && head->type != ENV)
			str = head->content;
		while (head && !join_node(head))
		{
			if (!skip_node(head, num_env))
			{
				num_env = 0;
				head = head->next;
				continue;
			}
			if (head->type == ENV)
			{
				num_env++;
				tmp = handle_env(head, env_list, num_env);
				if (!tmp)
				{
					head = head->next;
					in_join = 1;
					continue;
				}
				if (head->state == GENERAL && ft_strcmp(tmp, "$") && ft_strchr(tmp, ' '))
					str = generate_value_of_env(str, tmp, list_str, new_list);
				else
					str = join_list_str(str, tmp, list_str);
			}
			else
				str = join_list_str(str, head->content, list_str);
			head = head->next;
			in_join = 1;
		}
		if (str)
			add_node(new_list, str, in_join);
		if (in_join == 0 && head)
			head = head->next;
		num_env = 0;
	}
}

char *ft_expand_value(char *str, t_list *env_list)
{
	char	*value;

	value = NULL;
	while (env_list)
	{
		if (ft_strncmp(str, env_list->content, ft_strlen(str)) == 0
			&& env_list->content[ft_strlen(str)] == '=')
			value = &env_list->content[ft_strlen(str) + 1];
		env_list = env_list->next;
	}
	return (value);
}

void	ft_make_new_list_w_s(t_list *new_list, t_list **new_list_w_s)
{
	t_list *new;

	while (new_list)
	{
		if (new_list->type == WHITE_SPACE && new_list->state == GENERAL)
		{
			new_list = new_list->next;
			continue;
		}
		new = ft_lstnew(new_list->content, NULL);
		new->state = new_list->state;
		ft_lstadd_back(new_list_w_s, new);
		new_list = new_list->next;
	}
}

int	count_arg(t_list *new_list_w_s)
{
	int	count;

	count = 0;
	while (new_list_w_s &&
		(new_list_w_s->type != PIPE_LINE || new_list_w_s->state == IN_DQUOTE))
	{
		if ((new_list_w_s->type == REDIR_IN || new_list_w_s->type == REDIR_OUT
			|| new_list_w_s->type == HERE_DOC || new_list_w_s->type == DREDIR_OUT)
			&& new_list_w_s->state == GENERAL)
		{
			new_list_w_s = new_list_w_s->next->next;
			continue;
		}
		count++;
		new_list_w_s = new_list_w_s->next;
	}
	return (count);
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
}

void	affiche_error(void)
{
	perror("Error: malloc");
	exit (1);
}

int	is_DOC(t_list *list)
{
	if ((list->type == REDIR_IN || list->type == REDIR_OUT
		|| list->type == HERE_DOC || list->type == DREDIR_OUT)
		&& list->state == GENERAL)
		return (0);
	return (1);
;}

void	get_command(t_list *new_list_w_s, t_list **last_list)
{
	int		num_arg;
	char	**cmd;
	int		i;
	int		save_state;
	t_list	*new;

	save_state = new_list_w_s->state;
	num_arg = count_arg(new_list_w_s);
	cmd = (char **)malloc(sizeof(char *) * (num_arg + 1));
	if (!cmd)
		affiche_error();
	i = 0;
	while (new_list_w_s &&
		(new_list_w_s->type != PIPE_LINE || new_list_w_s->state == IN_DQUOTE))
	{
		if (!is_DOC(new_list_w_s))
		{
			new_list_w_s = new_list_w_s->next->next;
			continue;
		}
		cmd[i++] = ft_strdup(new_list_w_s->content);
		new_list_w_s = new_list_w_s->next;
	}
	cmd[i] = NULL;
	new = ft_lstnew(NULL, cmd);
	if (save_state == 0)
		new->type_d = WORD;
	ft_lstadd_back(last_list, new);
	free_double(cmd);
}

void	get_DOC(t_list **new_list_w_s, t_list **last_list)
{
	char	**cmd;
	int		i;
	t_list	*new;

	cmd = (char **)malloc(sizeof(char *) * (3));
	if (!cmd)
		affiche_error();
	i = 0;
	while (i < 2 && *new_list_w_s)
	{
		cmd[i++] = ft_strdup((*new_list_w_s)->content);
		*new_list_w_s = (*new_list_w_s)->next;
	}
	cmd[i] = NULL;
	new = ft_lstnew(NULL, cmd);
	ft_lstadd_back(last_list, new);
	free_double(cmd);
}

void	get_pipe(t_list *new_list_w_s, t_list **last_list)
{
	char	**cmd;
	t_list	*new;

	cmd = (char **)malloc(sizeof(char *) * (2));
	if (!cmd)
		affiche_error();
	cmd[0] = ft_strdup(new_list_w_s->content);
	cmd[1] = NULL;
	new = ft_lstnew(NULL, cmd);
	ft_lstadd_back(last_list, new);
	free_double(cmd);
}

void	ft_split_list(t_list **new_list_w_s, t_list **last_list, int *is_cmd, int *is_doc)
{
	if (((*new_list_w_s)->type == WORD || (*new_list_w_s)->type == ENV
		|| (*new_list_w_s)->state == IN_DQUOTE) && *is_cmd == 0)
	{
		get_command((*new_list_w_s), last_list);
		*is_cmd = 1;
	}
	else if (((*new_list_w_s)->type == REDIR_IN || (*new_list_w_s)->type == REDIR_OUT
		|| (*new_list_w_s)->type == HERE_DOC || (*new_list_w_s)->type == DREDIR_OUT) && (*new_list_w_s)->state == GENERAL)
	{
		get_DOC(new_list_w_s, last_list);
		*is_doc = 1;
	}
	else if ((*new_list_w_s)->type == PIPE_LINE && (*new_list_w_s)->state == GENERAL)
	{
		get_pipe((*new_list_w_s), last_list);
		*is_cmd = 0;
	}
}

void	ft_finale_list(t_list *new_list_w_s, t_list **last_list)
{
	int		num_arg;
	char	**cmd;
	int		i;
	int		is_cmd;
	int		is_doc;

	is_cmd = 0;
	is_doc = 0;
	while (new_list_w_s)
	{
		if ((new_list_w_s->type == WORD || new_list_w_s->type == ENV
			|| new_list_w_s->state == IN_DQUOTE) && is_cmd == 1)
		{
			new_list_w_s = new_list_w_s->next;
			continue;
		}
		ft_split_list(&new_list_w_s, last_list, &is_cmd, &is_doc);
		if (new_list_w_s && is_doc == 0)
			new_list_w_s = new_list_w_s->next;
		is_doc = 0;
	}
}
