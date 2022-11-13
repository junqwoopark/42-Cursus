/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:27:12 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/12 00:05:42 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include "../lib/libft/libft.h"

# define ERR (-1)

int	ft_printf(const char *format, ...);
int	parse_format(const char *format, va_list ap);
int	print_format(const char type, va_list ap, int *ret);
int	is_null_ptr(void *ptr);
int	ft_put_int_base(int nbr, char *base);
int	ft_put_ul_base(unsigned long nbr, char *base);
int	ft_put_ptr(ssize_t nbr);
int	ft_put_str(const char *str);
int	ft_put_char(char c);

#endif
