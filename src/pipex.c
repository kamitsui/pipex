/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:43:55 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/07 19:26:45 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <stdio.h>// for debug
#include <unistd.h>// for debug

typedef struct s_args
{
	char	*file1;
	char	*file2;
	char	**cmds;
	int		num_cmds;
	char	**env;
} t_args;


void	initialize_args(int argc, char **argv, char **env, t_args *args)
{
	args->file1 = argv[1];
	args->file2 = argv[argc - 1];
	args->cmds = &argv[2];
	args->num_cmds = argc - 4;
	args->env = env;
}

//bool	child_process(t_args *args, int pipefd[][2])
bool	child_process(t_args *args, int **pipefd)
{
	return true;
}

//bool	create_pipes(t_args *args, int pipefd[][2])
bool	create_pipes(t_args *args, int **pipefd)// Deprecated : for 
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < args->num_cmds)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return false;
		}
		else if (pid == 1)
		{
//			if (child_process(args, pipefd) == false)
			if (child_process(args, (int **)pipefd) == false)
				return false;
		}
		i++;
	}
	return true;
}

bool	multiple_pipes(int argc, char **argv, char **env)
{
	// Declaration structure
	t_args	args;
	// Initialize structure
	initialize_args(argc, argv, env, &args);
	int		pipefd[args.num_cmds - 1][2];
	// Create Pipes & Child Process
//	if (create_pipes(&args, pipefd) == false)
	if (create_pipes(&args, (int **)pipefd) == false)
		return false;
	return true;
}

int	main(int argc, char **argv, char **env)
{
// Error Handring : Insufficent argments
	if (argc < 5)
	{
		//perror("Insufficient arguments!\n");// not recommended
		char	*str_err = "Insufficient arguments!\n";
		write(STDERR_FILENO, str_err, ft_strlen(str_err));// Fix !! -> ft_fprintf();
		return false;
	}
	// Here_Doc
	if (ft_strnequ(argv[1], "here_doc", ft_strlen(argv[1])) == true)
		printf("%s\n", argv[1]);

	// Multiple pipe
	else
	{
		if (multiple_pipes(argc, argv, env) == false)
		return 1;
	}
	return 0;
}
//		// Debug code : in else (Multiple pipe)
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
