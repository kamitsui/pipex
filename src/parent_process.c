/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:04:27 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/16 16:20:56 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <sys/wait.h>

void	parent_process(int pipefd[2])
{
	pid_t	terminal_pid;

	close(pipefd[WRITE_END]);
	if (dup2(pipefd[READ_END], STDIN_FILENO) == -1)
	{
		close(pipefd[READ_END]);
		ft_errno_exit("dup2");
	}
	terminal_pid = waitpid(-1, NULL, WNOHANG);
	if (terminal_pid == -1)
		ft_errno_exit("waitpid");
}

