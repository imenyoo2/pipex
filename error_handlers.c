/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:31:06 by ayait-el          #+#    #+#             */
/*   Updated: 2023/12/16 21:36:56 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	strjoin_failure(char *first_arg, char *second_arg)
{
	ft_printf_err("ft_strjoin(\"%s\", \"%s\") has failed\n", first_arg,
		second_arg);
	exit(1);
}

void	check_cmd(char *cmd, int *pids, char **args)
{
	if (access(cmd, X_OK) == -1)
		ft_printf_err("%s: %s\n", cmd, strerror(errno));
	else
		return ;
	free(pids);
	free_array((void **)args);
	exit(1);
}

void	cmd_not_found(char *cmd, int *pids, char **args)
{
	ft_printf_err("%s: command not found\n", cmd);
	free(pids);
	free_array((void **)args);
	exit(1);
}
