/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:03:11 by ayait-el          #+#    #+#             */
/*   Updated: 2023/12/19 19:43:46 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// TODO: make sure you didn't include something you shouldn't
# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include "./printf/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

/*
# ifdef DEBUG
#  define KNRM "\x1B[0m"
#  define KRED "\x1B[31m"
#  define KGRN "\x1B[32m"
#  define KYEL "\x1B[33m"
#  define KBLU "\x1B[34m"
#  define KMAG "\x1B[35m"
#  define KCYN "\x1B[36m"
#  define KWHT "\x1B[37m"

#  define LOG(x)             \
	fprintf(stderr, KRED); \
	x;                     \
	fprintf(stderr, KNRM); \
	fflush(stderr)
# endif
*/

typedef struct files
{
	int		file1;
	int		file2;
}			files_t;

typedef struct pipe
{
	int		*pipe_to_use;
	int		input_end;
}			pipe_t;

typedef struct app_args
{
	int		argc;
	char	**argv;
	char	**env;
	int		herdoc;
}			app_args;

// helpers1
void		open_files(int argc, char **argv, files_t *files);
void		duplicate_streams(int input, int output);
void		free_array(void **arr);
void		duplicate_fds(int fd_in, int fd_out);
void		close_fd(int fd);

// helpers2
void		close_child_fds(int islastloop, int input_end, int *pip_to_use,
				int file2);
void		close_parent_fds(int islastloop, pipe_t *pipe_holder,
				files_t *files);
void		usage(void);

// helpers3
int			is_path(char *cmd);
void		exec_cmd(char *cmd, char **args, char **env, int *pids);
void		parse_and_execute_cmd(char *cmd, int *pids, char **env);
char		**get_path_env(char **env);
char		*get_path(char *cmd, char **env);

// helpers4
void		spawn_children(app_args *args, pipe_t *pipe_holder, int *pids,
				files_t *files);
void		wait_for_child(pid_t p);
void		wait_for_childern(int *children, int count);

// error handlers
void		strjoin_failure(char *first_arg, char *second_arg);
void		check_cmd(char *cmd, int *pids, char **args);
void		cmd_not_found(char *cmd, int *pids, char **args);
void	fork_failure(int *pids, int fork_num);

void		spawn_child(app_args *args, pipe_t *pipe_holder, files_t *files,
				int loop);

#endif
