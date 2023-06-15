/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:48:55 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/15 18:56:24 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

void	output_err_handle(t_pipex *pipex)
{
	int		err_number;
	char	*err_message;

	err_number = errno;
	err_message = strerror(err_number);
	printf("bash: %s: %s\n", pipex->out_file, err_message);// Must fix
	exit (1);
}
// Must Fix
//	printf("bash: %s: %s\n", pipex->out_file, err_message);

void	output_redirect(t_pipex *pipex)
{
	int		fdout;

	if (pipex->mode & BIT_OVER_RIDE)
		fdout = open(pipex->out_file, O_WRONLY | O_CREAT | O_TRUNC, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		fdout = open(pipex->out_file, O_WRONLY | O_CREAT | O_APPEND, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fdout == -1)
		ft_perr_exit("open");
	if (dup2(fdout, STDOUT_FILENO) == -1)
		ft_perr_exit("dup2");
	close(fdout);
}

void	set_output(t_pipex *pipex, int pipefd[2], int i)
{
	if (i != pipex->num_cmds - 1)
	{
		printf("i:%d STDOUT: pipefd[1]\n", i);
		if (dup2(pipefd[WRITE_END], STDOUT_FILENO) == -1)
			ft_perr_exit("dup2");
	}
	else
	{
		printf("i:%d STDOUT: file2\n", i);
		if (access(pipex->out_file, F_OK) == 0
			&& access(pipex->out_file, W_OK) == -1)
			output_err_handle(pipex);
		else
			output_redirect(pipex);
	}
}
