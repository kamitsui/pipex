/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:27:16 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/20 21:58:52 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

static void	input_redirect(t_pipex *pipex)
{
	int		fdin;

	if (access(pipex->in_file, F_OK | R_OK) == 0)
	{
		fdin = open(pipex->in_file, O_RDONLY);
		if (fdin == -1)
			ft_perr_exit("open");
		if (dup2(fdin, STDIN_FILENO) == -1)
			ft_perr_exit("dup2");
		close(fdin);
	}
	else
		ft_errno_exit(pipex->in_file);
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
	exit(0);// exit(6);// ?????
}

static void	here_doc(t_pipex *pipex)
{
	int		pipefd[2];
	pid_t	pid;

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
}

void	set_input(t_pipex *pipex)
{
	if (pipex->mode & BIT_HERE_DOC)
		here_doc(pipex);
	else
		input_redirect(pipex);
}
