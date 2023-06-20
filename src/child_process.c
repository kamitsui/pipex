/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:02:41 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/20 17:36:02 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <string.h>
#include <stdlib.h>
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
	//execvp(file, cmd_args);
	exec_file(file, cmd_args, pipex->env);
	ft_errno_exit(file);// Fix this !!!!!!!!!!!!!!
}

// Debug Code
//#include "get_next_line.h"//for debug
//void	debug_fileno(int i)
//{
//	char *line;
//	char *test_message;
//
//	if (i == 0)
//	{
//		test_message = "--- write from i=0 ---\n";
//		write(STDOUT_FILENO, test_message, ft_strlen(test_message));
//		line = get_next_line(STDIN_FILENO);
//		write(STDOUT_FILENO, line, ft_strlen(line));
//		free(line);
//	}
//	else
//	{
//		test_message = "--- write from i>0 ---\n";
//		write(STDOUT_FILENO, test_message, ft_strlen(test_message));
////	char *test_message1;
////	char *test_message2;
////	char *test_message3;
////		test_message1 = "--- write from i=";
////		test_message2 = ft_itoa(i);
////		test_message3 = " ---\n";
////		write(STDOUT_FILENO, test_message1, ft_strlen(test_message1));
////		write(STDOUT_FILENO, test_message2, ft_strlen(test_message2));
////		write(STDOUT_FILENO, test_message3, ft_strlen(test_message3));
////		free(test_message2);
//		while ((line = get_next_line(STDIN_FILENO)) != NULL)
//		{
//			write(STDOUT_FILENO, line, ft_strlen(line));
//			free(line);
//		}
//	}
//	exit (0);
//}

// Debug Code
//#include <stdio.h>// for debug
//void	debug_arguments(char *arguments[])
//{
//	int	j = 0;
//
//	while (arguments[j] != NULL)
//	{
//		printf("\targuments[%d]\t%s\n", j, arguments[j]);
//		free(arguments[j]);// for split()
//		j++;
//	}
//}
