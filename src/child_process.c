/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:02:41 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/04 18:35:05 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "pipex.h"
#include <unistd.h>

void	child_process(t_pipex *pipex, int pipefd[2], char **cmd_args, int i)
{
	char	*file;

	file = cmd_args[0];
	close(pipefd[READ_END]);
	if (i < pipex->num_cmds - 1)
	{
		if (dup2(pipefd[WRITE_END], STDOUT_FILENO) == -1)
		{
			close(pipefd[WRITE_END]);
			ft_errno_exit("dup2");
		}
	}
	close(pipefd[WRITE_END]);
	exec_file(file, cmd_args, pipex->env);
	ft_fprintf(stderr, "bash: %s: command not found\n", file);
	exit (127);
}
