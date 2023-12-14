


#ifndef PIPEX_H
#define PIPEX_H

# ifdef DEBUG
#  define KNRM  "\x1B[0m"
#  define KRED  "\x1B[31m"
#  define KGRN  "\x1B[32m"
#  define KYEL  "\x1B[33m"
#  define KBLU  "\x1B[34m"
#  define KMAG  "\x1B[35m"
#  define KCYN  "\x1B[36m"
#  define KWHT  "\x1B[37m"

#  define LOG(x) fprintf(stderr, KRED); x; fprintf(stderr, KNRM); fflush(stderr)
# endif

typedef struct files
{
  int file1;
  int file2;
} files_t;

typedef struct pipe
{
  int *pipe_to_use;
  int input_end;
} pipe_t;

#endif
