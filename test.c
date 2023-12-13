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

int main(int argc, char **argv, char **env)
{
  int file1;
  int file2;
  int *pids;
  int input_end;
  int i;
  int *pip_to_use;
  int pid;
  //atexit(f);
  if (argc < 3)
    ft_printf_err(1, "not enough arguments\n", 1);
  file1 = open(argv[1], O_RDONLY);
  if (file1 == -1)
    ft_printf_err(1, "couldn't open file %s\n", argv[1], 1);
  file2 = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0700);
  if (file2 == -1)
    ft_printf_err(1, "couldn't open file %s\n", argv[argc - 1], 1);
  if (pids = malloc(sizeof(int) * (argc - 3)), pids == NULL)
    ft_printf_err(1, "failed to malloc pids\n");
  input_end = file1;
  i = 0;

#ifdef DEBUG
  LOG(fprintf(stderr, "p1 = [%d, %d], p2 = [%d, %d]\n", p1[0], p1[1], p2[0], p2[1]));
#endif

  while (i < argc - 3)
  {
    int tmp[2];
    if (pip_to_use = tmp, i != argc - 4 && pipe(pip_to_use) == -1)
      ft_printf_err(1, "failed to create pipe\n");

    pid = fork();

#ifdef DEBUG
    LOG(fprintf(stderr, "%d: forking\n", pid));
#endif

    if (pid == 0)
    {
      // add protection

#ifdef DEBUG
      LOG(fprintf(stderr, "%d: input_end = %d\n", pid, input_end));
      LOG(fprintf(stderr, "%d: pip_to_use = %p, p1 = %p, p2 = %p\n", pid, pip_to_use, p1, p2));
#endif

      if (i == argc - 4)
        duplicate_streams(input_end, file2);
      else
        duplicate_streams(input_end, pip_to_use[1]);

#ifdef DEBUG
      LOG(fprintf(stderr, "%d: duplication done!\n", pid));
#endif

      close_fd(input_end, 0);
      close_fd(file2, 0);
      if (i != argc - 4)
      {
        close_fd(pip_to_use[1], 0);
        close_fd(pip_to_use[0], 0);
      }

      char **args = ft_split(argv[i + 2], ' ');

#ifdef DEBUG
      LOG(fprintf(stderr, "%d: args = [%s, %s, %s]\n", pid, args[0], args[1], args[2]));
#endif

      if (!args)
      {
        free(pids);
        ft_printf_err(1, "failed to split cmd='%s'\n", args[0]);
      }
      if (is_path(args[0]))
      {
        if (!access(args[0], X_OK))
        {
          execve(args[0], args, env);
          perror("execve");
          free(pids);
          free_array((void **) args);
          exit(1);
        }
        else
        {
          free(pids);
          free_array((void **) args);
          ft_printf_err(1, "%s not found!\n", args[0]);
        }
      }
      else
      {
#ifdef DEBUG
      LOG(fprintf(stderr, "%d: searching for path\n", pid));
#endif
        char *path = get_path(args[0], env);
        if (!path)
        {
          free(pids);
          free_array((void **) args);
          ft_printf_err(1, "%s not found!\n", args[0]);
        }
        else
        {
#ifdef DEBUG
      LOG(fprintf(stderr, "%d: executing cmd = %s\n", pid, path));
#endif
          execve(path, args, env);
          perror("execve");
          free(pids);
          free_array((void **) args);
          exit(1);
        }
      }
    }
    else if (pid == -1)
    {
      // TODO: maybe close open pids here;
      free(pids);
      ft_printf_err(1, "failed to fork in loop number %d\n", i);
    }
    if (i == argc - 4)
      close_fd(file2, 0);
    close_fd(input_end, 0);
    input_end = pip_to_use[0];
    if (i != argc - 4)
      close_fd(pip_to_use[1], 0);
    pids[i] = pid;
    i++;
  }
  //waiting loop:
  i = 0;
  while (i < argc - 3)
  {
    int status;
    waitpid(pids[i], &status, WUNTRACED);
    if (status != 0)
    {
      write(2, "a child process has failed\n", 27);
      exit(1);
    }
    i++;
  }
  return (0);
}
