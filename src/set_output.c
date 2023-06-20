/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:48:55 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/20 21:58:03 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <fcntl.h>

void	set_output(t_pipex *pipex)
{
	int		fdout;

	if (access(pipex->out_file, F_OK) == 0
		&& access(pipex->out_file, W_OK) == -1)
		ft_errno_exit(pipex->out_file);
	else
	{
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
}
