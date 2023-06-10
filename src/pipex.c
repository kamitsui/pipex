/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:43:55 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/10 19:57:40 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>// for debug
#include <unistd.h>// for debug
#include <string.h>// fordebug

// leaks check
//__attribute__((destructor)) static void destructor()
//{
//	system("leaks -q pipex");
//}

int	main(int argc, char **argv, char **env)
{
	char	*str_err;
	int		result = 0;

	if (argc < 5)
	{
		str_err = "Insufficient arguments!\n";
		write(STDERR_FILENO, str_err, ft_strlen(str_err));
		return (1);
	}
	// Here_Doc
	if (ft_strnequ(argv[1], "here_doc", ft_strlen(argv[1])) == true)
		printf("%s\n", argv[1]);
	// Multiple pipe
	else
	{
		result = multiple_pipes(argc, argv, env);
//		if (multiple_pipes(argc, argv, env) == false)
//			return (1);
	}
	system("leaks -q pipex");
	return (result);
}
