
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "./libft/libft.h"
#include <errno.h>

int main(int argc, char **argv, char **env)
{
  int fd[2];

  pipe(fd);
  int p = fork();
  if (p == 0)
  {
    write(fd[0], "hello world...........", 22);
  }
  else
  {
    char buffer[22];
    read(fd[1], buffer, 10);
  }
}
