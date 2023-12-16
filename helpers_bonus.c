/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:02:34 by ayait-el          #+#    #+#             */
/*   Updated: 2023/12/16 17:48:38 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	duplicate_streams(int input, int output)
{
	if (dup2(input, 0) == -1)
		(ft_printf_err("duplicating input = %d has failed\n", input), exit(1));
	if (dup2(output, 1) == -1)
		(ft_printf_err("duplicating output = %d has failed\n", output), exit(1));
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

void	close_fd(int fd, int debug)
{
	int	status;

	status = close(fd);
	if (status == -1)
	{
		// TODO: CHANGE THIS
		perror("closing error");
		if (debug)
			ft_printf_err("closing fd = %d\n", fd);
    exit(status);
	}
}

void	close_child_fds(int islastloop, int input_end, int *pip_to_use,
		int file2)
{
	close_fd(input_end, 0);
	close_fd(file2, 0);
	if (!islastloop)
	{
		close_fd(pip_to_use[1], 0);
		close_fd(pip_to_use[0], 0);
	}
}

void	close_parent_fds(int islastloop, pipe_t *pipe_holder, files_t *files)
{
	if (islastloop)
		close_fd(files->file2, 0);
	close_fd(pipe_holder->input_end, 0);
	pipe_holder->input_end = pipe_holder->pipe_to_use[0];
	if (!islastloop)
		close_fd(pipe_holder->pipe_to_use[1], 0);
}

// TODO: don't exit if a child fails
void	wait_for_childern(int *children, int count)
{
	int	i;
	int	status;

	i = 0;
	while (i < count)
	{
		waitpid(children[i], &status, WUNTRACED);
//		if (status != 0)
//		{
//      ft_printf_err("the %dth child has failed with status: %d\n", i, status);
//			exit(1);
//		}
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
      (free(cmd), free_array((void **) paths));
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

// void  f()
//{
//  system("leaks a.out");
//}

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
	(ft_printf_err("failed to fork child number %d\n", fork_num), exit(1));
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

	i = 0 + 1 * is_herdoc(args->argv);
  //ft_printf_err("i = %d\n", i);
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
		// TODO: maybe close open pids here;
		else if (pid == -1)
			fork_failure(pids, i);
		close_parent_fds(i == args->argc - 3 - 1, pipe_holder, files);
		pids[i] = pid;
		i++;
	}
}

int is_herdoc(char **argv)
{
  if (ft_strncmp(argv[1], "here_doc", 9) == 0)
    return (1);
  else
    return (0);
}

void write_herdoc_msg(int argc, char *line_to_free)
{
  if (argc == 5)
  {
    if (write(1, "heredoc> ", 9) == -1)
    {
      free(line_to_free);
      ft_printf_err("writing herdoc msg: %s\n", strerror(errno));
      exit(1);
    }
  }
  else
  {
    if (write(1, "pipe heredoc> ", 14) == -1)
    {
      free(line_to_free);
      ft_printf_err("writing herdoc msg: %s\n", strerror(errno));
      exit(1);
    }
  }
}

char *read_line()
{
  char *line;

  line = get_next_line(0);
  if (!line)
    (ft_printf_err("failed reading a line from stdin\n"), exit(1));
  return (line);
}

void write_line(int fd, char *line)
{
  int len;
  int index;

  len = strlen(line);
  index = 0;
  while (len > 1024)
  {
    if (write(fd, &line[index], 1024) == -1)
    {
      free(line);
      ft_printf_err("write_line: %s\n", strerror(errno));
      exit(1);
    }
    len -= 1024;
    index += 1024;
  }
  if (write(fd, &line[index], len) == -1)
  {
    free(line);
    ft_printf_err("write_line: %s\n", strerror(errno));
    exit(1);
  }
  free(line);
}

int get_heredoc_input(int *pids, app_args *args)
{
  int herdoc_pipe[2];
  int pid;
  char *line;
  char *limiter;
  int limiter_len;

  limiter = args->argv[2];
  limiter_len = ft_strlen(limiter);
  if (pipe(herdoc_pipe) == -1)
    (ft_printf_err("create herdoc_pipe: %s\n", strerror(errno)), exit(1));
  pid = fork();
  if (pid == 0)
  {
    write_herdoc_msg(args->argc, NULL);
    line = read_line();
    while (!(!ft_strncmp(line, limiter, limiter_len) && line[limiter_len] == '\n'))
    {
      write_line(herdoc_pipe[1], line);
      write_herdoc_msg(args->argc, line);
      line = read_line();
    }
    free(line);
    close_fd(herdoc_pipe[0], 0);
    close_fd(herdoc_pipe[1], 0);
    exit(0);
  }
  else if (pid == -1)
    fork_failure(pids, 0);
  else
  {
    pids[0] = pid;
    close_fd(herdoc_pipe[1], 0);
  }
  return (herdoc_pipe[0]);
}
