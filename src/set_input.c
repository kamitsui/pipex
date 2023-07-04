/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:27:16 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/04 19:27:46 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>

static int	input_redirect(t_pipex *pipex)
{
	int	fdin;
	int	status;

	status = 0;
	if (access(pipex->in_file, F_OK | R_OK) == 0)
	{
		fdin = open(pipex->in_file, O_RDONLY);
		if (fdin == -1)
			perror("open");
		if (dup2(fdin, STDIN_FILENO) == -1)
			perror("dup2");
		close(fdin);
	}
	else
	{
		fdin = open("/dev/null", O_RDONLY);
		if (fdin == -1)
			perror("open");
		if (dup2(fdin, STDIN_FILENO) == -1)
			perror("dup2");
		close(fdin);
		status = ft_errno_set_status(pipex->in_file) != 0;
	}
	return (status);
}

static void	write_to_pipefd(int fd, char *end_of_block)
{
	char	*line;

	write(STDIN_FILENO, PROMPT, ft_strlen(PROMPT));
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (ft_strnequ(line, end_of_block, ft_strlen(end_of_block)) == true)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
		write(STDIN_FILENO, PROMPT, ft_strlen(PROMPT));
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(fd);
	exit(0);
}

static int	here_doc(t_pipex *pipex)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe(pipefd) == -1)
		ft_perr_exit("pipe");
	pid = fork();
	if (pid == -1)
		ft_perr_exit("fork");
	else if (pid == 0)
	{
		close(pipefd[READ_END]);
		write_to_pipefd(pipefd[WRITE_END], pipex->limiter);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(pipefd[WRITE_END]);
		dup2(pipefd[READ_END], STDIN_FILENO);
		close(pipefd[READ_END]);
	}
	return (status);
}

int	set_input(t_pipex *pipex)
{
	int	status;

	if (pipex->mode & BIT_HERE_DOC)
		status = here_doc(pipex);
	else
		status = input_redirect(pipex);
	return (status);
}
