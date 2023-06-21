/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:30:36 by amoukhle          #+#    #+#             */
/*   Updated: 2023/06/21 21:44:22 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_env_heredoc(t_list *list, t_var *var)
{
	if (list->next && list->type == ENV && list->state == GENERAL
		&& (list->next->type == QOUTE || list->next->type == DOUBLE_QUOTE)
		&& var->num_env % 2 != 0)
		return ("");
	return (list->content);
}

int	skip_node_heredoc(t_list *list)
{
	if ((list->type == QOUTE && list->state == GENERAL)
		|| (list->type == DOUBLE_QUOTE && list->state == GENERAL))
		return (0);
	return (1);
}

void	ft_skip_node_heredoc(t_list *list, t_var *var)
{
	if (!var->str && (list->type == DOUBLE_QUOTE || list->type == QOUTE))
		var->str = "";
	var->num_env = 0;
	var->skip = 1;
	var->q_dq = 1;
}

char	*get_string_heredoc(t_list *list, t_var *var, t_list_str **list_str)
{
	char	*tmp;

	while (list)
	{
		var->skip = 0;
		if (!skip_node_heredoc(list))
			ft_skip_node_heredoc(list, var);
		if (!var->skip && list->type == ENV)
		{
			var->num_env++;
			tmp = handle_env_heredoc(list, var);
			var->str = join_list_str(var->str, tmp, list_str);
		}
		else if (!var->skip)
		{
			var->num_env = 0;
			var->str = join_list_str(var->str, list->content, list_str);
		}
		list = list->next;
	}
	return (var->str);
}

int	skip_node_delimiter(t_list *list, t_var *var)
{
	if (((list->type == WORD || list->type == Q_MARK) && list->prev && list->prev->type == ENV
		&& list->state != IN_QUOTE && var->num_env % 2 != 0))
		return (0);
	return (1);
}

void	ft_skip_node_delimiter(t_var *var)
{
	var->num_env = 0;
	var->skip = 1;
}

char	*get_string_delimiter(t_list *list, t_var *var, t_list *env_list, t_list_str **list_str)
{
	char	*tmp;

	while (list)
	{
		var->skip = 0;
		if (!skip_node_delimiter(list, var))
			ft_skip_node_delimiter(var);
		if (!var->skip && list->type == ENV)
		{
			var->num_env++;
			tmp = handle_env_DOC(list, env_list, var->num_env);
			if (!tmp)
				tmp = "";
			var->str = join_list_str(var->str, tmp, list_str);
		}
		else if (!var->skip)
			var->str = join_list_str(var->str, list->content, list_str);
		list = list->next;
	}
	return (var->str);
}

void	ft_init_var_delimiter(t_var *var)
{
	var->start = 0;
	var->end = 0;
	var->flag1 = 0;
	var->flag2 = 0;
	var->num_env = 0;
	var->str = NULL;
}

// void	ft_expand_heredoc()
// {
	
// }

void	fill_file(char *delimiter, int fd, t_var *var)
{
	char	*line;
	char	*str;
	t_list	*list;
	t_list_str	*list_str;

	list = NULL;
	list_str = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (!var->q_dq)
		{
			ft_init_var_delimiter(var);
			ft_make_list(line, &list, var);
			str = get_string_delimiter(list, var, var->env_list, &list_str);
			ft_lstclear(&list);
			write(fd, str, ft_strlen(str));
		}
		else
			write(fd, line, ft_strlen(line));
		free(line);
		list_strclear(&list_str);
	}
	close (fd);
}

void	ft_msg_error_heredoc(char *name)
{
	int	len_error;

	len_error = ft_strlen(strerror(errno));
	write(2, "bash: ", 6);
	write(2, name, ft_strlen(name));
	write(2, ": ", 2);
	write(2, strerror(errno), len_error);
	write (2, "\n", 1);
	exit(1);
}

char	*ft_name_file(void)
{
	static int	i;
	char		*name;
	char		*num;
	
	num = ft_itoa(i++);
	name = ft_strjoin("/tmp/here_doc", num);
	free(num);
	while (access(name, F_OK) != -1)
	{
		free(name);
		num = ft_itoa(i++);
		name = ft_strjoin("/tmp/here_doc", num);
		free(num);
	}
	return (name);
}

int	ft_open_heredoc(t_list *node, t_var *var)
{
	t_list		*list;
	char		*delimiter;
	t_list_str	*list_str;
	int			file;
	char		*name_file;

	list = NULL;
	list_str = NULL;
	name_file = ft_name_file();
	ft_init_var(var);
	ft_make_list(node->cmd[1], &list, var);
	delimiter = get_string_heredoc(list, var, &list_str);
	file = open(name_file, O_WRONLY | O_CREAT, 0777);
	if (file == -1)
		ft_msg_error_heredoc(name_file);
	fill_file(delimiter, file, var);
	file = open(name_file, O_RDONLY, 0777);
	if (file == -1)
		ft_msg_error_heredoc(name_file);
	ft_lstclear(&list);
	list_strclear(&list_str);
	free(name_file);
	return (file);
}
