/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:59:34 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/08 12:06:50 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>// for debug
#include <unistd.h>// for debug

void	child_process(t_args args, int pipefd[2], int i)
{
	exit(1);
}

void	initialize_args(int argc, char **argv, char **env, t_args *args)
{
	args->file1 = argv[1];
	args->file2 = argv[argc - 1];
	args->cmds = &argv[2];
	args->num_cmds = argc - 4;
	args->env = env;
}

int	multiple_pipes(int argc, char **argv, char **env)
{
	t_args	args;
	int		pipefd[2];
	pid_t	pid;
	int		i;
	int		status;

	initialize_args(argc, argv, env, &args);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	i = 0;
	while (i < args.num_cmds)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
			child_process(args, pipefd, i);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	i = 0;
	while (i < args.num_cmds)
	{
		wait(&status);
		i++;
	}
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
