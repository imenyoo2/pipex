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

//#ifdef DEBUG
//  LOG(fprintf(stderr, "closing fd = %d\n", fd));
//#endif

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

void close_fds(int p1[2], int p2[2], int p3[2])
{
  close_fd(p1[0], 0);
  close_fd(p1[1], 0);
  close_fd(p2[0], 0);
  close_fd(p2[1], 0);
  close_fd(p3[0], 0);
  close_fd(p3[1], 0);
}

void exit_with_error(char *msg, int status)
{
  size_t len;

  len = ft_strlen(msg);
  write(2, msg, len);
  exit(status);
}

char *get_path(char *cmd, char **env)
{
  char **paths;
  size_t i;
  char *path;

  cmd = ft_strjoin("/", cmd);
  if (cmd == NULL)
    exit_with_error("malloc failed\n", 1);
  while (*env)
  {
    if (ft_strncmp(*env, "PATH=", 5) == 0)
    {
      paths = ft_split(*env + 5, ':');

      i = 0;
      while (paths[i])
      {
        if (path = ft_strjoin(paths[i], cmd), path == NULL)
          exit_with_error("malloc failed\n", 1);
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

/*
int pipe2processes(int p1[2], int p2[2], int p3[2], char **cmds, char **env)
{
  pid_t pid1;
  pid_t pid2;
  char **argv;
  char *file_path;

  pid1 = fork();
  if (pid1 == 0)
  {
    duplicate_fds(p1[0], p2[1]);
    close_fds(p1, p2, p3);
    argv = ft_split(cmds[0], ' ');
    if (argv == NULL)
      exit_with_error("failed parsing command\n", 1);
    if (is_path(cmds[0]))
      execve(get_path(cmds[0], env), argv, env);
    else
      execve(cmds[0], argv, env);
    perror("execve:");
    exit(1);
  }
  pid2 = fork();
  if (pid2 == 0)
  {
    duplicate_fds(p2[0], p3[1]);
    close_fds(p1, p2, p3);
    argv = ft_split(cmds[1], ' ');
    if (argv == NULL)
      exit_with_error("failed parsing command\n", 1);
    if (is_path(cmds[1]))
      execve(get_path(cmds[1], env), argv, env);
    else
      execve(cmds[1], argv, env);
    perror("execve:");
    exit(1);
  }
  //wait_for_child(pid1);
}
*/

/*
void execute(char *cmd)
{
  if (is_path(cmd))
    execve();
}
*/

int main(int argc, char **argv, char **env)
{
  int file1;
  int file2;
  int *pids;
  int p1[2];
  int p2[2];
  int input_end;
  int i;
  int *pip_to_use;
  int pid;

  if (argc < 3)
    ft_printf_err(1, "not enough arguments\n", 1);
  file1 = open(argv[1], O_RDONLY);
  if (file1 == -1)
    ft_printf_err(1, "couldn't open file %s\n", argv[1], 1);
  file2 = open(argv[argc - 1], O_WRONLY);
  if (file2 == -1)
    ft_printf_err(1, "couldn't open file %s\n", argv[argc - 1], 1);
  if (pipe(p1) == -1)
    ft_printf_err(1, "failed to create pipe\n");
  if (pipe(p2) == -1)
    ft_printf_err(1, "failed to create pipe\n");
  if (dup2(file1, p1[1]) == -1)
    ft_printf_err(1, "failed to duplicate\n");
  if (dup2(file2, p2[0]) == -1)
    ft_printf_err(1, "failed to duplicate\n");
  if (pids = malloc(sizeof(int) * (argc - 3)), pids == NULL)
    ft_printf_err(1, "failed to malloc pids\n");
  close_fd(file1, 0);
  close_fd(file2, 0);
  input_end = p1[0];
  i = 0;

#ifdef DEBUG
  LOG(fprintf(stderr, "p1 = [%d, %d], p2 = [%d, %d]\n", p1[0], p1[1], p2[0], p2[1]));
#endif

  while (i < argc - 3)
  {
    int tmp[2];
    if (i == argc - 4)
    {
      input_end = p2[0];
      pip_to_use = p2;
    }
    else if (pip_to_use = tmp, pipe(pip_to_use) == -1)
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

      if (dup2(input_end, 0) == -1 || dup2(pip_to_use[1], 1) == -1)
      {
        free(pids);
        ft_printf_err(1, "couldn't duplicate\n");
      }

#ifdef DEBUG
      LOG(fprintf(stderr, "%d: duplication done!\n", pid));
#endif

      close_fd(input_end, 0);
      close_fd(pip_to_use[1], 0);
      close_fd(pip_to_use[0], 1);
      if (i == 0)
        close_fd(p1[1], 0);
//      else if (i == argc - 4)
//        close_fd(p2[0], 1);

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
//    if (i == 0)
//      close_fd(p1[1], 0);
//    else if (i == argc - 4)
//      close_fd(p2[0], 0);
//    close_fd(pip_to_use[1], 0);
    //close_fd(input_end, 1);
    input_end = pip_to_use[0];
    pids[i] = pid;
    i++;
  }
  //waiting loop:
  i = 0;
  while (i < argc - 3)
  {
    int status;
    write(2, "waiting for child processes\n", 28);
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

/*
int main(int argc, char **argv, char **env)
{
  int fd[2];
  char buffer[1024];
  int input = open("input", O_RDONLY | O_WRONLY);
  int readed;

  pipe(fd);
  pid_t pid = fork();
  if (pid == 0)
  {
//    readed = read(fd[0], buffer, 30);
//    write(file1, buffer, readed);
    close(fd[0]);
    int file1 = open("file1", O_RDONLY);
    dup2(file1, 0);
    dup2(fd[1], 1);
    close(file1);
    close(fd[1]);
    char *args[] = {"cat", NULL};
    execve("/bin/cat", args, env);
    write(2, "error", 5);
    exit(1);
  }
  pid_t pid2 = fork();
  if (pid2 == 0)
  {
    int file2 = open("file2", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    close(fd[1]);
    if (dup2(file2, 1) == -1)
      perror("duplicating file2");
    if (dup2(fd[0], 0) == -1)
      perror("duplicating fd[0]");
    close(file2);
    close(fd[0]);
    char *args[] = {"wc", "-l", NULL};
    execve("/usr/bin/wc", args, env);
    exit(1);
  }
  int status2;
  close(fd[0]);
  close(fd[1]);
  waitpid(pid, &status2, WUNTRACED);
  fprintf(stderr, "%s\n", strerror(status2));
  //waitpid(pid2, &status2, WUNTRACED);
  fprintf(stderr, "%s\n", strerror(status2));
  //waitpid(pid, &status2, WUNTRACED);
  close(input);
}
*/
