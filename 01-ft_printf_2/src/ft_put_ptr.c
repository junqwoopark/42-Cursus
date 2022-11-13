/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:51:30 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/11 23:59:53 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_put_ptr(ssize_t nbr)
{
	int	ret;

	ret = 0;
	ret += write(1, "0x", 2);
	ret += ft_put_ul_base(nbr, "0123456789abcdef");
	return (ret);
}
