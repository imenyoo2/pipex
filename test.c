/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:29:57 by ayait-el          #+#    #+#             */
/*   Updated: 2023/12/15 16:09:12 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	init_state(argc, argv, &files, &pipe_holder);
	pids = malloc(sizeof(int) * (argc - 3));
	if (pids == NULL)
		(ft_printf_err("failed to malloc pids\n"), exit(1));
	spawn_children(&args, &pipe_holder, pids, &files);
	// waiting loop:
	wait_for_childern(pids, argc - 3);
	return (0);
}
