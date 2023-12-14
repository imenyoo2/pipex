#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "./libft/libft.h"
#include "./printf/ft_printf.h"
#include <errno.h>
#include "pipex.h"
#include <stdio.h>


void init_state(int argc, char **argv, files_t *files, pipe_t *pipe_holder)
{
  if (argc < 3)
    ft_printf_err(1, "not enough arguments\n", 1);
  files->file1 = open(argv[1], O_RDONLY);
  if (files->file1 == -1)
    ft_printf_err(1, "couldn't open file %s\n", argv[1], 1);
  files->file2 = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0700);
  if (files->file2 == -1)
    ft_printf_err(1, "couldn't open file %s\n", argv[argc - 1], 1);
  pipe_holder->input_end = files->file1;
}

void duplicate_streams(int input, int output)
{
      if (dup2(input, 0) == -1)
        ft_printf_err(1, "duplicating input = %d has failed\n", input);
      if (dup2(output, 1) == -1)
        ft_printf_err(1, "duplicating output = %d has failed\n", output);
}

void free_array(void **arr)
{
  size_t i;

  i = 0;
  while (arr[i])
  {
    free(arr[i]);
    i++;
  }
  free(arr);
}

void duplicate_fds(int fd_in, int fd_out)
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

void close_fd(int fd, int debug)
{
  int status;

  status = close(fd);
  if (status == -1)
  {
    // TODO: CHANGE THIS
    perror("closing error");
    if (debug)
    {
      ft_printf_err(status, "closing fd = %d\n", fd); fflush(stderr);
    }
    else
      exit(status);
  }
}

void close_child_fds(int islastloop, int input_end, int *pip_to_use, int file2)
{
  close_fd(input_end, 0);
  close_fd(file2, 0);
  if (!islastloop)
  {
    close_fd(pip_to_use[1], 0);
    close_fd(pip_to_use[0], 0);
  }
}

void close_parent_fds(int islastloop, pipe_t *pipe_holder, files_t *files)
{
  if (islastloop)
    close_fd(files->file2, 0);
  close_fd(pipe_holder->input_end, 0);
  pipe_holder->input_end = pipe_holder->pipe_to_use[0];
  if (!islastloop)
    close_fd(pipe_holder->pipe_to_use[1], 0);
}

// TODO: don't exit if a child fails
void wait_for_childern(int *children, int count)
{
  int i;
  int status;

  i = 0;
  while (i < count)
  {
    waitpid(children[i], &status, WUNTRACED);
    if (status != 0)
    {
      write(2, "a child process has failed\n", 27);
      exit(1);
    }
    i++;
  }
}


char *get_path(char *cmd, char **env)
{
  char **paths;
  size_t i;
  char *path;

  cmd = ft_strjoin("/", cmd);
  if (cmd == NULL)
    ft_printf_err(1, "ft_strjoin(\"/\", cmd:'%s') has failed\n", cmd);
  while (*env)
  {
    if (ft_strncmp(*env, "PATH=", 5) == 0)
    {
      paths = ft_split(*env + 5, ':');

      i = 0;
      while (paths[i])
      {
        if (path = ft_strjoin(paths[i], cmd), path == NULL)
          ft_printf_err(1, "ft_strjoin(paths[i]: %s, cmd:'%s') has failed\n", paths[i], cmd);
        if (!access(path, X_OK))
          return (free_array((void **) paths), free(cmd), path);
        free(path);
        i++;
      }
      return (NULL);
    }
    env++;
  }
  return (NULL);
}

int is_path(char *cmd)
{
  while (*cmd)
  {
    if (*cmd == '/')
      return (1);
    cmd++;
  }
  return (0);
}

void wait_for_child(pid_t p)
{
  int status;

  waitpid(p, &status, WUNTRACED);
  if (status != -1)
  {
    perror("waitpid() error");
    exit(errno);
  }
}

//void  f()
//{
//  system("leaks a.out");
//}

void exec_cmd(char *cmd, char **args, char **env, int *pids)
{
  execve(cmd, args, env);
  perror("execve");
  free(pids);
  free_array((void **) args);
  exit(1);
}

// TODO: change to use perror
void cmd_not_found(char *cmd, int *pids, char **args)
{
  free(pids);
  free_array((void **) args);
  ft_printf_err(1, "%s not found!\n", cmd);
}

void parse_and_execute_cmd(char *cmd, int *pids, char **env)
{
  char **args = ft_split(cmd, ' ');
  if (!args)
  {
    free(pids);
    ft_printf_err(1, "failed to split cmd='%s'\n", args[0]);
  }
  if (is_path(args[0]))
  {
    if (!access(args[0], X_OK))
      exec_cmd(args[0], args, env, pids);
    else
      cmd_not_found(args[0], pids, args);
  }
  else
  {
    char *path = get_path(args[0], env);
    if (!path)
      cmd_not_found(args[0], pids, args);
    else
      exec_cmd(path, args, env, pids);
  }
}

void spawn_children(app_args *args, pipe_t *pipe_holder, int *pids, files_t *files)
{
  int i;
  int tmp[2];
  int pid;

  i = 0;
  while (i < args->argc - 3)
  {
    if (pipe_holder->pipe_to_use = tmp, i != args->argc - 3 - 1 && pipe(pipe_holder->pipe_to_use) == -1)
      ft_printf_err(1, "failed to create pipe\n");
    pid = fork();
    if (pid == 0)
    {
      if (i == args->argc - 3 - 1)
        duplicate_streams(pipe_holder->input_end, files->file2);
      else
        duplicate_streams(pipe_holder->input_end, pipe_holder->pipe_to_use[1]);
      close_child_fds(i == args->argc - 3 - 1, pipe_holder->input_end, pipe_holder->pipe_to_use, files->file2);
      parse_and_execute_cmd(args->argv[i + 2], pids, args->env);
    }
    else if (pid == -1)
    {
      // TODO: maybe close open pids here;
      free(pids);
      ft_printf_err(1, "failed to fork in loop number %d\n", i);
    }
    close_parent_fds(i == args->argc - 3 - 1, pipe_holder, files);
    pids[i] = pid;
    i++;
  }
}

int main(int argc, char **argv, char **env)
{
  files_t files;
  pipe_t pipe_holder;
  int *pids;
  app_args args;
  //atexit(f);

  args.argv = argv;
  args.argc = argc;
  args.env = env;
  init_state(argc, argv, &files, &pipe_holder);
  if (pids = malloc(sizeof(int) * (argc - 3)), pids == NULL)
    ft_printf_err(1, "failed to malloc pids\n");
  spawn_children(&args, &pipe_holder, pids, &files);
  //waiting loop:
  wait_for_childern(pids, argc - 3);
  return (0);
}
