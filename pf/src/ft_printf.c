/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:26:17 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/12 00:01:01 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		ret;
	va_list	ap;

	if (is_null_ptr((void *) format))
		return (ERR);
	va_start(ap, format);
	ret = parse_format(format, ap);
	va_end(ap);
	return (ret);
}
