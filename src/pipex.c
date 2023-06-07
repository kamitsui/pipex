/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:43:55 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/07 15:29:12 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <stdio.h>// for debug

typedef struct s_args
{
	char	*file1;
	char	*file2;
	char	**cmds;
	int		num_cmds;
} t_args;


int	main(int argc, char **argv, char **env)
{
// Error Handring : Insufficent argments


	// Here_Doc
	if (ft_strnequ(argv[1], "here_doc", ft_strlen(argv[1])) == true)
		printf("%s\n", argv[1]);

	// Multiple pipe
	else
	{
		//printf("multiple pipex\n");
		// Declaration structure
		t_args	args;
		// Initialize structure
		args.file1 = argv[1];
		args.file2 = argv[argc - 1];
		args.cmds = &argv[2];
		args.num_cmds = argc - 4;
		// Debug code : in else (Multiple pipe)
		printf("%s\n", args.file1);
		printf("%s\n", args.file2);
		int	i = 0;
		while (i <= args.num_cmds)
		{
			printf("%s\n", args.cmds[i]);
			i++;
		}
		printf("%d\n", args.num_cmds);
	}
	printf("\nenv:\n");
	int	j = 0;
	while (env[j] != NULL)
	{
		printf("%s\n", env[j]);
		j++;
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
// Debug code : argc, argv, env
//	printf("\narvc:%d\n", argc);
//	printf("\nenv:\n");
//	int	j = 0;
//	while (env[j] != NULL)
//	{
//		printf("%s\n", env[j]);
//		j++;
//	}
