/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:59:34 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/10 19:56:43 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>// for debug
#include <unistd.h>// for debug

void	initialize_args(int argc, char **argv, char **env, t_args *args)
{
	args->in_file = argv[1];
	args->out_file = argv[argc - 1];
	args->cmds = &argv[2];
	args->num_cmds = argc - 3;
	args->env = env;
}

//int	ft_execvp(const char *file, char *const argv[])
//{
//}

#include <string.h>

void	child_process(int pipefd[2], char *arguments[])
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
//	set_input();
//	set_output();
//	ft_execvp(file, cmd_args);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(1);
}

//int	create_process(t_args *args, int pipefd[2])// return last status
void	create_process(t_args *args, int pipefd[2])
{
	pid_t	pid;
	int		i;
	int		j;
	char	**cmd_args;

	i = 0;
	printf("num_cmds: %d\n", args->num_cmds);
	while (i < args->num_cmds)
	{
		cmd_args = ft_split(args->cmds[i], ' ');
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
			child_process(pipefd, cmd_args);
		j = 0;
		while (cmd_args[j] != NULL)
		{
			free(cmd_args[j]);
			j++;
		}
		free(cmd_args);
//		printf("pid:%d\n", pid);// child pid
		i++;
	}
}

int	multiple_pipes(int argc, char **argv, char **env)
{
	t_args	args;
	int		pipefd[2];
	int		i;
	int		status;
//	int		result;

	initialize_args(argc, argv, env, &args);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	create_process(&args, pipefd);
//	result = create_process(&args, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	i = 0;
	while (i < args.num_cmds)
	{
		wait(&status);
		i++;
	}
//	return (result);
	return (0);
}
// Debug code : in else (Multiple pipe)
//		printf("%s\n", args.file1);
//		printf("%s\n", args.file2);
//		int	i = 0;
//		while (i <= args.num_cmds)
//		{
//			printf("%s\n", args.cmds[i]);
//			i++;
//		}
//		printf("%d\n", args.num_cmds);
//		printf("\nenv:\n");
//		int	j = 0;
//		while (args.env[j] != NULL)
//		{
//			printf("%s\n", args.env[j]);
//			j++;
//		}
