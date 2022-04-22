/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 23:53:39 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/14 11:00:40 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	print_format(char type, va_list ap, int *ret)
{
	if (type == 'c')
		*ret += ft_put_char(va_arg(ap, int));
	else if (type == '%')
		*ret += ft_put_char('%');
	else if (type == 's')
		*ret += ft_put_str((char *)va_arg(ap, size_t));
	else if (type == 'p')
		*ret += ft_put_ptr(va_arg(ap, size_t));
	else if (type == 'd')
		*ret += ft_put_int_base(va_arg(ap, int), "0123456789");
	else if (type == 'i')
		*ret += (ft_put_int_base(va_arg(ap, int), "0123456789"));
	else if (type == 'u')
		*ret += ft_put_ul_base(va_arg(ap, unsigned int), "0123456789");
	else if (type == 'x')
		*ret += ft_put_ul_base(va_arg(ap, unsigned int), "0123456789abcdef");
	else if (type == 'X')
		*ret += ft_put_ul_base(va_arg(ap, unsigned int), "0123456789ABCDEF");
	else
		return (ERR);
	return (*ret);
}
