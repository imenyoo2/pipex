/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:29:57 by ayait-el          #+#    #+#             */
/*   Updated: 2023/12/16 16:15:44 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_files(int argc, char **argv, files_t *files, pipe_t *pipe_holder)
{
  if (access(argv[1], R_OK) == -1 && !is_herdoc(argv))
    (ft_printf_err("%s: %s\n", argv[1], strerror(errno)), exit(1));
  if (access(argv[argc - 1], W_OK) == -1)
    (ft_printf_err("%s: %s\n", argv[argc - 1], strerror(errno)), exit(1));
  if (!is_herdoc(argv))
  {
    files->file1 = open(argv[1], O_RDONLY);
    if (files->file1 == -1)
      (ft_printf_err("couldn't open file %s\n", argv[1]), exit(1));
  }
	files->file2 = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0700);
	if (files->file2 == -1)
		(ft_printf_err("couldn't open file %s\n", argv[argc - 1]), exit(1));
}

void usage()
{
  ft_printf_err("Usage:\n\t./pipex input_file cmd1 cmd2 ... cmdN output_file\n");
}

int	main(int argc, char **argv, char **env)
{
	files_t		files;
	pipe_t		pipe_holder;
	int			*pids;
	app_args	args;

	// atexit(f);
	args.argv = argv;
	args.argc = argc;
	args.env = env;
	if (argc < 3 + 1 * is_herdoc(args.argv))
		(ft_printf_err("not enought arguments\n"), usage(), exit(1));
	open_files(argc, argv, &files, &pipe_holder);
	pids = malloc(sizeof(int) * (argc - 3 + 1 * is_herdoc(args.argv)));
	if (pids == NULL)
		(ft_printf_err("failed to malloc pids\n"), exit(1));
  if (is_herdoc(args.argv))
    pipe_holder.input_end = get_heredoc_input(pids, &args);
  else
    pipe_holder.input_end = files.file1;
	spawn_children(&args, &pipe_holder, pids, &files);
	// waiting loop:
	wait_for_childern(pids, argc - 3);
	return (0);
}
