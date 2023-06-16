/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:27:16 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/16 16:58:36 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

static void	input_redirect(t_pipex *pipex)
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
}

static void	here_doc(t_pipex *pipex)
{
	if (pipex == NULL)
		return ;
	printf("%s\n", HERE_DOC);// Fix this !!!!!!!!!!!!!!!!!
	return ;
}

void	set_input(t_pipex *pipex)
{
	if (pipex->mode & BIT_HERE_DOC)
		here_doc(pipex);
	else
		input_redirect(pipex);
}
