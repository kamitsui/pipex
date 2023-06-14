/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:02:41 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/14 20:57:07 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//int	ft_execvp(const char *file, char *const argv[])
//{
//}


void	child_process(t_pipex *pipex, int pipefd[2], char *arguments[], int i)
{
// Deleate ! may be...
	if (arguments == NULL)
		return ;

//	char	*command;

// Debug Code
//	int	j = 0;
//	while (arguments[j] != NULL)
//	{
//		printf("\targuments[%d]\t%s\n", j, arguments[j]);
//		free(arguments[j]);// for split()
//		j++;
//	}
	set_input(pipex, pipefd, i);
	set_output(pipex, pipefd, i);
	close(pipefd[READ_END]);
	close(pipefd[WRITE_END]);
//	char *test_message = "write from i=0";
//	if (i == 0)
//		write(STDOUT_FILENO, test_message, ft_strlen(test_message));
//	ft_execvp(file, cmd_args);
	exit(1);
}
