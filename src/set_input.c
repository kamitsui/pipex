/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:27:16 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/16 16:29:03 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

void	input_err_handle(t_pipex *pipex)
{
	int		err_number;
	char	*err_message;

	err_number = errno;
	err_message = strerror(err_number);
	printf("bash: %s: %s\n", pipex->in_file, err_message);// Must Fix
	exit (1);
}

void	input_redirect(t_pipex *pipex)
{
	int		fdin;

	if (access(pipex->in_file, F_OK | R_OK) == 0)
	{
		fdin = open(pipex->in_file, O_RDONLY);
		if (fdin == -1)
		{
			perror("open");
			exit (1);
		}
		if (dup2(fdin, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit (1);
		}
		close(fdin);
	}
	else
		ft_errno_exit(pipex->in_file);
//		input_err_handle(pipex);
}
// Must Fix
		//ft_printf("bash: %s: %s\n", pipex->in_file, err_message);

void	here_doc(t_pipex *pipex)
{
	if (pipex == NULL)
		return ;
	printf("%s\n", HERE_DOC);
	return ;
}

void	set_input(t_pipex *pipex, int pipefd[2], int i)
{
	if (i != 0)
	{
		if (dup2(pipefd[READ_END], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit (1);
		}
	}
	else
	{
		if (pipex->mode & BIT_HERE_DOC)
			here_doc(pipex);
		else
			input_redirect(pipex);
	}
}
