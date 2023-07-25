/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:29:59 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/25 10:03:30 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe(t_var *var, int num_pipe)
{
	int	i;

	i = 0;
	while (i < num_pipe)
	{
		if (pipe(var->fd + i * 2) == -1)
		{
			write (2, "Error: Failed to pipe\n", 22);
			free(var->fd);
			return (1);
		}
		i++;
	}
	return (0);
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

void	ft_execution(t_list *last_list, t_env **env_list, t_var *var)
{
	int	num_pipe;

	num_pipe = ft_num_pipe(last_list);
	if (num_pipe != 0)
	{
		var->fd = (int *)malloc(sizeof(int) * num_pipe * 2);
		if (!(var->fd))
			affiche_error();
		if (ft_pipe(var, num_pipe) == 1)
			return ;
	}
	exec_child(last_list, env_list, var, num_pipe);
	if (num_pipe != 0)
		free(var->fd);
}
void	ft_position_start_end(t_list **last_list, t_list_str **list_heredoce_tmp)
{
	while (*last_list && (*last_list)->type_d != PIPE_LINE)
	{
		if ((*last_list)->type_d == HERE_DOC)
			*list_heredoce_tmp = (*list_heredoce_tmp)->next;
		*last_list = (*last_list)->next;
	}
	if (*last_list && (*last_list)->type_d == PIPE_LINE)
		*last_list = (*last_list)->next;
}

void	error_fork(void)
{
	write (2, "Error: Failed to fork\n", 22);
	exit (1);
}

void	init_var(t_var *var, int num_pipe)
{
	var->n_cmd = num_pipe + 1;
	var->num_cmd = 0;
	var->std_in = 0;
	var->std_out = 1;
	var->error_DOC = 0;
}

int	ft_serche_in_list(t_list *last_list, char *cmd)
{
	while (last_list && (last_list)->type_d != PIPE_LINE)
	{
		if ((last_list)->type_d == WORD)
		{
			if(ft_strcmp(cmd, last_list->cmd[0]) == 0)
				return (0);
		}
		last_list = (last_list)->next;
	}
	return (1);
}

int	ft_is_builting_cmd(t_list *last_list, t_var *var)
{
	if (ft_serche_in_list(last_list, "/usr/bin/cd") == 0
		|| ft_serche_in_list(last_list, "cd") == 0
		|| ft_serche_in_list(last_list, "/bin/pwd") == 0
		|| ft_serche_in_list(last_list, "pwd") == 0
		|| ft_serche_in_list(last_list, "/usr/bin/env") == 0
		|| ft_serche_in_list(last_list, "env") == 0
		|| ft_serche_in_list(last_list, "/bin/echo") == 0
		|| ft_serche_in_list(last_list, "echo") == 0
		|| ft_serche_in_list(last_list, "unset") == 0
		|| ft_serche_in_list(last_list, "export") == 0
		|| ft_serche_in_list(last_list, "exit") == 0)
	{
		var->is_built = 1;
		return (0);
	}
	return (1);
}

void	exec_child(t_list *last_list, t_env **env_list, t_var *var, int num_pipe)
{
	pid_t		pid;
	t_list		*list;
	t_list_str	*list_heredoce;
	t_list_str	*list_heredoce_tmp;
	pid_t		last_child;

	list = last_list;
	list_heredoce = NULL;
	init_var(var, num_pipe);
	ft_serche_for_heredoce(last_list, var, &list_heredoce);
	if (get_value(-1) == 4)
	{
		list_strclear(&list_heredoce);
		return ;
	}
	list_heredoce_tmp = list_heredoce;
	if (var->n_cmd == 1 && ft_is_builting_cmd(last_list, var) == 0)
	{
		ft_serche_for_DOC(last_list, *env_list, var, &list_heredoce);
		ft_serche_for_cmd(&last_list);
		if (var->error_DOC != 1)
			ft_builtins(last_list, env_list, var);
		return ;
	}
	while (var->num_cmd < var->n_cmd)
	{
		if (ft_serche_in_list(last_list, "./minishell") == 0)
			signal(SIGINT, nothing_minishell);
		else
		{
			signal(SIGINT, nothing);
			signal(SIGQUIT, nothing);
		}
		pid = fork();
		if (pid == -1)
			error_fork();
		if (pid == 0)
			ft_child_proccess(list, env_list, var, &list_heredoce_tmp);
		(var->num_cmd)++;
		ft_position_start_end(&list, &list_heredoce_tmp);
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

	(void)last_child;
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
			{
				state_exit = WTERMSIG(state);
				if (state_exit == 3)
					state_exit = 131;
				else if (state_exit == 2)
					state_exit = 130;
				else if (state_exit == 11)
					state_exit = 0;
			}
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

void	serch_for_heredoc(t_var *var, t_list_str **list_heredoc, int *other_inf)
{
	if (*other_inf == 1)
	{
		close(var->std_in);
		*other_inf = 0;
	}
	*other_inf = 1;
	var->std_in = (*list_heredoc)->fd;
	*list_heredoc = (*list_heredoc)->next;
}
void	serch_for_inf(t_list *last_list, t_var *var, t_env *env_list, int *other_inf)
{
	int	file;

	file = ft_open_infile(last_list, var, env_list);
	if (file != -1)
	{
		if (ft_listchr(last_list, HERE_DOC) == 0)
			close(file);
		else
		{
			if (*other_inf == 1)
			{
				close(var->std_in);
				*other_inf = 0;
			}
			*other_inf = 1;
			var->std_in = file;
		}
	}
}

void	serch_for_outf(t_list *last_list, t_env *env_list, t_var *var, int *other_outf)
{
	int	file;

	if (last_list->type_d == REDIR_OUT)
		file = ft_open_outfile(last_list, var, env_list);
	else
		file = ft_open_append_file(last_list, var, env_list);
	if (file != -1)
	{
		if (*other_outf == 1)
		{
			close(var->std_out);
			*other_outf = 0;
		}
		*other_outf = 1;
		var->std_out = file;
	}
}

void	ft_serche_for_DOC(t_list *last_list, t_env *env_list, t_var *var, t_list_str **list_heredoc)
{
	int	other_inf;
	int	other_outf;

	other_inf = 0;
	other_outf = 0;
	while (last_list && last_list->type_d != PIPE_LINE)
	{
		if (last_list->type_d == HERE_DOC)
			serch_for_heredoc(var, list_heredoc, &other_inf);
		else if (last_list->type_d == REDIR_IN)
			serch_for_inf(last_list, var, env_list, &other_inf);
		else if (last_list->type_d == REDIR_OUT || last_list->type_d == DREDIR_OUT)
			serch_for_outf(last_list, env_list, var, &other_outf);
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
		close(var->std_out);
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


char	**get_paths(t_env *env_list, char **cmd)
{
	char	*var;
	char	*value;
	char	**paths;
	t_env	*tmp;

	var = "PATH";
	tmp = env_list;
	value = NULL;
	while (env_list)
	{
		if (ft_strncmp(var, env_list->content, ft_strlen(var)) == 0)
			value = &env_list->content[ft_strlen(var) + 1];
		env_list = env_list->next;
	}
	if (!value)
		value = tmp->hide_path;
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

char	**check_cmd(t_list *last_list, t_env *env_list)
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


void	ft_child_proccess(t_list *last_list, t_env **env_list, t_var *var, t_list_str **list_heredoc)
{
	int		j;
	int		len_error;
	char	**cmd;
	DIR		*dir;

	ft_serche_for_DOC(last_list, *env_list, var, list_heredoc);
	ft_serche_for_cmd(&last_list);
	if (last_list->type_d != WORD)
		exit (0);
	cmd = check_cmd(last_list, *env_list);
	ft_duplicate(var);
	j = 0;
	while (j < (var->n_cmd - 1) * 2)
		close(var->fd[j++]);
	if (!cmd)
		exit(127);
	if (ft_builtins(last_list, env_list, var) == 1)
	{
		if (execve(cmd[0], cmd, (*env_list)->env) == -1)
		{
			dir = opendir(cmd[0]);
			if (dir)
			{
				write (2, "bash: ", 6);
				write (2, cmd[0], ft_strlen(cmd[0]));
				write (2, ": is a directory\n", 17);
				closedir(dir);
				exit (126);
			}
			len_error = ft_strlen(strerror(errno));
			write(2, "bash: ", 6);
			write (2, cmd[0], ft_strlen(cmd[0]));
			write (2, ": ", 2);
			write(2, strerror(errno), len_error);
			write (2, "\n", 1);
			exit (127);
		}
	}
	exit(0);
}
