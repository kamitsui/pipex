/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:43:55 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/08 12:07:39 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
//#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>// for debug
#include <unistd.h>// for debug

int	main(int argc, char **argv, char **env)
{
	char	*str_err;

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
		if (multiple_pipes(argc, argv, env) == false)
			return (1);
	}
	return (0);
}
