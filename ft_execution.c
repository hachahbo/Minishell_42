/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:29:59 by amoukhle          #+#    #+#             */
/*   Updated: 2023/06/24 21:18:12 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(t_var *var, int num_pipe)
{
	int	i;

	i = 0;
	while (i < num_pipe)
	{
		if (pipe(var->fd + i * 2) == -1)
		{
			write (2, "Error: Failed to pipe\n", 22);
			free(var->fd);
			exit (1);
		}
		i++;
	}
}

int	ft_num_pipe(t_list *last_list)
{
	int	n_p;

	n_p = 0;
	while (last_list)
	{
		if (last_list->type_d == PIPE_LINE)
			n_p++;
		last_list = last_list->next;
	}
	return (n_p);
}

void	ft_execution(t_list *last_list, t_list *env_list, t_var *var)
{
	int	num_pipe;

	num_pipe = ft_num_pipe(last_list);
	if (num_pipe != 0)
	{
		var->fd = (int *)malloc(sizeof(int) * num_pipe * 2);
		if (!(var->fd))
			affiche_error();
		ft_pipe(var, num_pipe);
	}
	exec_child(last_list, env_list, var, num_pipe);
	if (num_pipe != 0)
		free(var->fd);
}
void	ft_position_start_end(t_list **last_list)
{
	while (*last_list && (*last_list)->type_d != PIPE_LINE)
		*last_list = (*last_list)->next;
	if (*last_list && (*last_list)->type_d == PIPE_LINE)
		*last_list = (*last_list)->next;
}

void	exec_child(t_list *last_list, t_list *env_list, t_var *var, int num_pipe)
{
	pid_t		pid;
	t_list		*list;
	t_list_str	*list_heredoce;
	t_list_str	*list_heredoce_tmp;
	pid_t		last_child;

	list = last_list;
	list_heredoce = NULL;
	var->n_cmd = num_pipe + 1;
	var->num_cmd = 0;
	var->std_in = 0;
	var->std_out = 1;
	ft_serche_for_heredoce(last_list, var, &list_heredoce);
	list_heredoce_tmp = list_heredoce;
	while (var->num_cmd < var->n_cmd)
	{
		pid = fork();
		if (pid == -1)
		{
			write (2, "Error: Failed to fork\n", 22);
			exit (1);
		}
		if (pid == 0)
			ft_child_proccess(list, env_list, var, &list_heredoce_tmp);
		(var->num_cmd)++;
		ft_position_start_end(&list);
	}
	last_child = pid;
	wait_childs(var, last_child);
	list_strclear(&list_heredoce);
}

void	wait_childs(t_var *var, pid_t last_child)
{
	int		j;
	int		state;
	pid_t	pid;

	j = 0;
	while (j < (var->n_cmd - 1) * 2)
		close(var->fd[j++]);
	j = 0;
	while (j < var->n_cmd)
	{
		pid = wait(&state);
		if (pid == last_child)
		{
			if (WIFEXITED(state))
				state_exit = WEXITSTATUS(state);
			else if (WIFSIGNALED(state))
				state_exit = WTERMSIG(state);
		}
		j++;
	}
}

int	ft_serche_for_redir_in(t_list *last_list)
{
	while (last_list && last_list->type_d != PIPE_LINE)
	{
		if (last_list->type_d == REDIR_IN)
			return (0);
		last_list = last_list->next;
	}
	return (1);
}

void	ft_serche_for_heredoce(t_list *last_list, t_var *var, t_list_str **list_heredoce)
{
	int	file;
	int	other_hd;

	other_hd = 0;
	while (last_list)
	{
		if (last_list->type_d == HERE_DOC)
		{
			file = ft_open_heredoc(last_list, var);
			list_stradd_back(list_heredoce, new_list_str(NULL, file));
		}
		last_list = last_list->next;
	}
}

int	ft_listchr(t_list *list, int type)
{
	while (list && list->type_d != PIPE_LINE)
	{
		if (list->type_d == type)
			return (0);
		list = list->next;
	}
	return (1);
}

void	ft_serche_for_DOC(t_list *last_list, t_list *env_list, t_var *var, t_list_str **list_heredoc)
{
	int	file;
	int	other_inf;
	int	other_outf;

	other_inf = 0;
	other_outf = 0;
	while (last_list && last_list->type_d != PIPE_LINE)
	{
		if (last_list->type_d == HERE_DOC)
		{
			if (other_inf == 1)
			{
				close(var->std_in);
				other_inf = 0;
			}
			other_inf = 1;
			var->std_in = (*list_heredoc)->fd;
			*list_heredoc = (*list_heredoc)->next;
		}
		else if (last_list->type_d == REDIR_IN)
		{
			file = ft_open_infile(last_list, var, env_list);
			if (ft_listchr(last_list, HERE_DOC) == 0)
				close(file);
			else
			{
				if (other_inf == 1)
				{
					close(var->std_in);
					other_inf = 0;
				}
				other_inf = 1;
				var->std_in = file;
			}
		}
		else if (last_list->type_d == REDIR_OUT || last_list->type_d == DREDIR_OUT)
		{
			if (other_outf == 1)
			{
				close(var->std_out);
				other_outf = 0;
			}
			other_outf = 1;
			if (last_list->type_d == REDIR_OUT)
				var->std_out = ft_open_outfile(last_list, var, env_list);
			else
				var->std_out = ft_open_append_file(last_list, var, env_list);
		}
		last_list = last_list->next;
	}
}

void	ft_duplicate(t_var *var)
{
	if (var->num_cmd == 0)
	{
		if (var->std_in != 0)
			dup2(var->std_in, STDIN_FILENO);
		if (var->n_cmd != 1)
			dup2(var->fd[1], STDOUT_FILENO);
		if (var->std_out != 1)
			dup2(var->std_out, STDOUT_FILENO);
	}
	else
	{
		dup2(var->fd[(var->num_cmd - 1) * 2], STDIN_FILENO);
		if (var->num_cmd != var->n_cmd - 1)
			dup2(var->fd[(var->num_cmd - 1) * 2 + 3], STDOUT_FILENO);
		if (var->std_out != 1)
			dup2(var->std_out, STDOUT_FILENO);
		if (var->std_in != 0)
			dup2(var->std_in, STDIN_FILENO);
	}
	if (var->std_in != 0)
		close(var->std_in);
	if (var->std_out != 1)
		close(var->std_in);
}

char	**return_cmd(char **cmd, char *str, char **paths, char *cm)
{
	free(cmd[0]);
	cmd[0] = str;
	free_double(paths);
	free(cm);
	return (cmd);
}

char	*check_cmd_is_exit(char **paths, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmd);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}


char	**get_paths(t_list *env_list, char **cmd)
{
	char	*var;
	char	*value;
	char	**paths;

	var = "PATH";
	value = NULL;
	while (env_list)
	{
		if (ft_strncmp(var, env_list->content, ft_strlen(var)) == 0)
			value = &env_list->content[ft_strlen(var) + 1];
		env_list = env_list->next;
	}
	if (!value)
	{
		write (2, "bash: ", 6);
		write (2, cmd[0], ft_strlen(cmd[0]));
		write (2, ": command not found\n", 20);
		exit (1);
	}
	paths = ft_split(value, ':');
	return (paths);
}

char	**check_cmd(t_list *last_list, t_list *env_list)
{
	char	**paths;
	char	**cmd;
	char	*cm;
	char	*str;

	cmd = last_list->cmd;
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
		return (cmd);
	if (ft_strcmp(cmd[0], ""))
	{
		paths = get_paths(env_list, cmd);
		cm = ft_strjoin("/", cmd[0]);
		str = check_cmd_is_exit(paths, cm);
		if (str)
			return (return_cmd(cmd, str, paths, cm));
		free_double(paths);
		free(cm);
	}
	write (2, "bash: ", 6);
	write (2, cmd[0], ft_strlen(cmd[0]));
	write (2, ": command not found\n", 20);
	return (NULL);
}

void	ft_serche_for_cmd(t_list **last_list)
{
	while (*last_list && (*last_list)->type_d != PIPE_LINE)
	{
		if ((*last_list)->type_d == WORD)
			return ;
		*last_list = (*last_list)->next;
	}
}

void	ft_child_proccess(t_list *last_list, t_list *env_list, t_var *var, t_list_str **list_heredoc)
{
	int	j;
	int	len_error;
	char	**cmd;

	ft_serche_for_DOC(last_list, env_list, var, list_heredoc);
	ft_serche_for_cmd(&last_list);
	if (last_list->type_d != WORD)
		exit (0);
	cmd = check_cmd(last_list, env_list);
	ft_duplicate(var);
	j = 0;
	while (j < (var->n_cmd - 1) * 2)
		close(var->fd[j++]);
	if (execve(cmd[0], cmd, NULL) == -1)
	{
		len_error = ft_strlen(strerror(errno));
		write(2, "bash: ", 6);
		write (2, cmd[0], ft_strlen(cmd[0]));
		write (2, ": ", 2);
		write(2, strerror(errno), len_error);
		write (2, "\n", 1);
		exit (1);
	}
}
