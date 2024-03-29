/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:41:56 by kamitsui          #+#    #+#             */
/*   Updated: 2023/03/25 15:42:14 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "ft_printf.h"
#include "process.h"
#include "conversion.h"
#include "va_arg.h"
#include "formalize.h"

void	octal(t_sm *machine)
{
	char				str[42];
	unsigned long long	num;
	int					base;

	ft_bzero(str, 42);
	base = 010;
	num = u_va_arg(machine);
	if ((machine->flag & BIT_HASH) != FALSE)
	{
		adjust_hash(str, machine);
		itoa_buff(num, &str[1], base, machine);
	}
	else
		itoa_buff(num, str, base, machine);
	formalize(str, machine);
}
//better idea
//	ft_bzero(str, 42);//42 is not better  >> xx_SIZE
