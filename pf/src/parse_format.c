/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 23:54:25 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/14 02:12:23 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	parse_format(const char *format, va_list ap)
{
	int	ret;

	ret = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (print_format(*format, ap, &ret) == ERR)
				return (ERR);
		}
		else
		{
			ft_putchar_fd(*format, 1);
			ret++;
		}
		format++;
	}
	return (ret);
}
