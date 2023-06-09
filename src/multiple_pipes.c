/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:59:34 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/09 22:13:55 by kamitsui         ###   ########.fr       */
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
	args->num_cmds = argc - 3;
	args->env = env;
}

//int	ft_execvp(const char *file, char *const argv[])
//{
//}

#include <string.h>
#define MAX_ARGS 10

void	child_process(t_args *args, int pipefd[2], int i)
{
//	char	*command;
	char	**arguments;// for split()
//	char	*arguments[MAX_ARGS];// for strtok()
//	int		arg_count;
//	char	*token;

// Debug Code
	printf("child process No:%d\n", i);
	printf("\tArgument\t%s\n", args->cmds[i]);

	arguments = ft_split(args->cmds[i], ' ');
	if (arguments == NULL)
	{
		perror("ft_split");
		exit(1);
	}
//	token = strtok(args->cmds[i], " ");
//	command = token;
//	arg_count = 0;
//	while (token != NULL && arg_count < MAX_ARGS - 1)
//	{
//		arguments[arg_count] = token;
//		arg_count++;
//		token = strtok(NULL, " ");
//	}
//	arguments[arg_count] = NULL;
// Debug Code
// Print the arguments
	int	j = 0;
	while (arguments[j] != NULL)
	{
		if (arguments[j] == NULL)
			break ;
		printf("\ttokenized\t%d %s\n", j, arguments[j]);
		free(arguments[j]);// for split()
		j++;
	}
	free(arguments);// for split()
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
	printf("num_cmds: %d\n", args->num_cmds);
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

// leaks check
__attribute__((destructor)) static void destructor()
{
	system("leaks -q pipex");
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
	destructor();
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
