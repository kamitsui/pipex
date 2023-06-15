/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:02:41 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/15 18:21:38 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>// for debug
#include "get_next_line.h"//for debug

//int	ft_execvp(const char *file, char *const argv[])
//{
//}

// Debug Code : single pipe case OK
// ./pipex file1 "ls" "ls -l" file2
// cat file2
// --- write from i=1 ---
// --- write from i=0 ---
// aaaa
//		child 1		file1 -> STDIN -> write(message) & write(gnl) -> STDOUT
//		child 2		STDIN(STDOUT of child 1) -> write(gnl) -> STDOUT -> file2
void	debug_fileno(int i)
{
	char *line;
	char *test_message;

	if (i == 0)
	{
		test_message = "--- write from i=0 ---\n";
		write(STDOUT_FILENO, test_message, ft_strlen(test_message));
		line = get_next_line(STDIN_FILENO);
		write(STDOUT_FILENO, line, ft_strlen(line));
		free(line);
	}
	else
	{
		test_message = "--- write from i>0 ---\n";
		write(STDOUT_FILENO, test_message, ft_strlen(test_message));
//	char *test_message1;
//	char *test_message2;
//	char *test_message3;
//		test_message1 = "--- write from i=";
//		test_message2 = ft_itoa(i);
//		test_message3 = " ---\n";
//		write(STDOUT_FILENO, test_message1, ft_strlen(test_message1));
//		write(STDOUT_FILENO, test_message2, ft_strlen(test_message2));
//		write(STDOUT_FILENO, test_message3, ft_strlen(test_message3));
//		free(test_message2);
		while ((line = get_next_line(STDIN_FILENO)) != NULL)
		{
			write(STDOUT_FILENO, line, ft_strlen(line));
			free(line);
		}
	}
	exit (0);
}

// Debug Code
void	debug_arguments(char *arguments[])
{
	int	j = 0;

	while (arguments[j] != NULL)
	{
		printf("\targuments[%d]\t%s\n", j, arguments[j]);
		free(arguments[j]);// for split()
		j++;
	}
}

void	child_process(t_pipex *pipex, int pipefd[2], char *arguments[], int i)
{
	char	*file = arguments[0];
	char	**cmd_args = arguments;
// Deleate ! may be...
	if (arguments == NULL)
		return ;

//	debug_arguments(arguments);// for Debug
	set_input(pipex, pipefd, i);
	set_output(pipex, pipefd, i);
	close(pipefd[READ_END]);
	close(pipefd[WRITE_END]);
//	debug_arguments(arguments);
//	debug_fileno(i);// for Debug
	execvp(file, cmd_args);
//	ft_execvp(file, cmd_args);
	exit(1);
}
