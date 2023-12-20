/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:02:34 by ayait-el          #+#    #+#             */
/*   Updated: 2023/12/20 10:50:08 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
void arr_swap(char **a, char **b)
{
  char *c;

  c = *a;
  *a = *b;
  *b = c;
}

void handle_quotes(char **arr)
{
  char **new;
  char *holder;

  new = "";
  i = 0;
  while (arr[i])
  {
    if (arr[i][0] == '"')
    {
      while (arr[i][ft_strlen(arr[i]) - 1] != '"')
      {
        i++;
      }
    }
    i++;
  }
}
*/

void	duplicate_streams(int input, int output)
{
	if (dup2(input, 0) == -1)
		(ft_printf_err("duplicating input = %d has failed\n", input), exit(1));
	if (dup2(output, 1) == -1)
		(ft_printf_err("duplicating output = %d has failed\n", output),
			exit(1));
}

void	free_array(void **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	duplicate_fds(int fd_in, int fd_out)
{
	if (dup2(fd_in, 0) == -1)
	{
		perror("duplicating error");
		exit(1);
	}
	if (dup2(fd_out, 1) == -1)
	{
		perror("duplicating error");
		exit(1);
	}
}

void	close_fd(int fd)
{
	int	status;

	status = close(fd);
	if (status == -1)
	{
    ft_printf_err("closing fd = %d: %s\n", fd, strerror(errno));
		exit(status);
	}
}

void	close_child_fds(int islastloop, int input_end, int *pip_to_use,
		int file2)
{
	close_fd(input_end);
	close_fd(file2);
	if (!islastloop)
	{
		close_fd(pip_to_use[1]);
		close_fd(pip_to_use[0]);
	}
}

void	close_parent_fds(int islastloop, pipe_t *pipe_holder, files_t *files)
{
	if (islastloop)
		close_fd(files->file2);
	close_fd(pipe_holder->input_end);
	pipe_holder->input_end = pipe_holder->pipe_to_use[0];
	if (!islastloop)
		close_fd(pipe_holder->pipe_to_use[1]);
}

void	wait_for_childern(int *children, int count)
{
	int	i;
	int	status;

	i = 0;
	while (i < count)
	{
		waitpid(children[i], &status, WUNTRACED);
		i++;
	}
}

// get's the PATH environment variable from env
char	**get_path_env(char **env)
{
	char	**paths;

	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			paths = ft_split(*env + 5, ':');
			if (!paths)
				return (NULL);
			return (paths);
		}
		env++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	**paths;
	size_t	i;
	char	*path;

	cmd = ft_strjoin("/", cmd);
	if (cmd == NULL)
		strjoin_failure("/", cmd);
	paths = get_path_env(env);
	if (!paths)
		return (free(cmd), NULL);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmd);
		if (path == NULL)
		{
			(free(cmd), free_array((void **)paths));
			strjoin_failure(paths[i], cmd);
		}
		if (!access(path, X_OK))
			return (free_array((void **)paths), free(cmd), path);
		free(path);
		i++;
	}
	return (NULL);
}

int	is_path(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '/')
			return (1);
		cmd++;
	}
	return (0);
}

void	wait_for_child(pid_t p)
{
	int	status;

	waitpid(p, &status, WUNTRACED);
	if (status != -1)
	{
		perror("waitpid() error");
		exit(errno);
	}
}


void	exec_cmd(char *cmd, char **args, char **env, int *pids)
{
	execve(cmd, args, env);
	perror("execve");
	free(pids);
	free_array((void **)args);
	exit(1);
}

void	parse_and_execute_cmd(char *cmd, int *pids, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		free(pids);
		(ft_printf_err("failed to split cmd='%s'\n", args[0]), exit(1));
	}
	if (is_path(args[0]))
	{
		check_cmd(args[0], pids, args);
		exec_cmd(args[0], args, env, pids);
	}
	else
	{
		path = get_path(args[0], env);
		if (!path)
			cmd_not_found(args[0], pids, args);
		else
		{
			check_cmd(path, pids, args);
			exec_cmd(path, args, env, pids);
		}
	}
}

void	fork_failure(int *pids, int fork_num)
{
	free(pids);
	(ft_printf_err("failed to fork in loop number %d\n", fork_num), exit(1));
}

void	spawn_child(app_args *args, pipe_t *pipe_holder, files_t *files,
		int loop)
{
	int	islastloop;

	islastloop = loop == args->argc - 3 - 1;
	if (islastloop)
		duplicate_streams(pipe_holder->input_end, files->file2);
	else
		duplicate_streams(pipe_holder->input_end, pipe_holder->pipe_to_use[1]);
	close_child_fds(islastloop, pipe_holder->input_end,
		pipe_holder->pipe_to_use, files->file2);
}

void	spawn_children(app_args *args, pipe_t *pipe_holder, int *pids,
		files_t *files)
{
	int	i;
	int	tmp[2];
	int	pid;

	i = 0;
	while (i < args->argc - 3)
	{
		pipe_holder->pipe_to_use = tmp;
		if (i != args->argc - 3 - 1 && pipe(pipe_holder->pipe_to_use) == -1)
			(ft_printf_err("failed to create pipe\n"), exit(1));
		pid = fork();
		if (pid == 0)
		{
			// TODO: change name
			spawn_child(args, pipe_holder, files, i);
			parse_and_execute_cmd(args->argv[i + 2], pids, args->env);
		}
		else if (pid == -1)
			fork_failure(pids, i);
		close_parent_fds(i == args->argc - 3 - 1, pipe_holder, files);
		pids[i] = pid;
		i++;
	}
}
