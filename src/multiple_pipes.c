/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:59:34 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/08 20:47:55 by kamitsui         ###   ########.fr       */
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
	args->file1 = argv[1];
	args->file2 = argv[argc - 1];
	args->cmds = &argv[2];
	args->num_cmds = argc - 4;
	args->env = env;
}

//int	ft_execvp(const char *file, char *const argv[])
//{
//}

#include <string.h>
#define MAX_ARGS 10

void	child_process(t_args *args, int pipefd[2], int i)
{
	char	*command;
	char	*arguments[MAX_ARGS];// ??
	int		arg_count;
	char	*token;

	token = strtok(args->cmds[i], " ");
	command = token;
	arg_count = 0;
	while (token != NULL && arg_count < MAX_ARGS - 1)
	{
		arguments[arg_count] = token;
		arg_count++;
		token = strtok(NULL, " ");
	}
	arguments[arg_count] = NULL;
// Print the arguments
	int	j = 0;
	while (j < arg_count)
	{
		printf("Argument %d %s\n", j, arguments[j]);
		j++;
	}
//	set_input();
//	set_output();
//	ft_execvp(file, cmd_argv);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(1);
}

void	create_process(t_args *args, int pipefd[2])
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < args->num_cmds)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
			child_process(args, pipefd, i);
		i++;
	}
}

int	multiple_pipes(int argc, char **argv, char **env)
{
	t_args	args;
	int		pipefd[2];
	int		i;
	int		status;

	initialize_args(argc, argv, env, &args);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	create_process(&args, pipefd);
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
