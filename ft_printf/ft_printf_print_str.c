/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:17:22 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/07 20:08:13 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(t_options *options, va_list *ap)
{
	if (options -> width > 1)
	{
		options -> padd = options -> width - 1;
		if (options -> left == 1)
		{
			ft_putchar_fd((char)va_arg(*ap, int), 1);
			while ((options -> padd)--)
				ft_putchar_fd(' ', 1);
		}
		else
		{
			while ((options -> padd)--)
				ft_putchar_fd(' ', 1);
			ft_putchar_fd((char)va_arg(*ap, int), 1);
		}
		return (options->width);
	}
	else
	{
		ft_putchar_fd((char) va_arg(*ap, int), 1);
		return (1);
	}
}

int	print_percent(t_options *options)
{
	if (options -> width > 1)
	{
		options -> padd = options -> width - 1;
		if (options -> left == 1)
		{
			ft_putchar_fd(37, 1);
			while ((options -> padd)--)
				ft_putchar_fd(' ', 1);
		}
		else
		{
			while ((options -> padd)--)
				ft_putchar_fd(' ', 1);
			ft_putchar_fd(37, 1);
		}
		return (options->width);
	}
	else
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
}

int	ft_putstr_len(char *str, size_t len)
{
	int	ret;

	ret = 0;
	while (*str && len--)
	{
		ret += ft_putchar_fd(*str, 1);
		str++;
	}
	return (ret);
}

int	print_s(t_options *options, va_list *ap)
{
	char	*s;
	int		ret;

	ret = 0;
	s = (char *) va_arg(*ap, char *);
	if (s == NULL)
		return (ft_putstr_fd("(null)", 1));
	if (options->prec == -1 || options->prec >= (int) ft_strlen(s))
		options->prec = ft_strlen(s);
	if ((size_t) options->width > ft_strlen(s))
		options->padd = options->width - options->prec;
	if (options -> left == 1)
	{
		ret += ft_putstr_len(s, options->prec);
		while ((options -> padd)--)
			ret += ft_putchar_fd(' ', 1);
	}
	else
	{
		while ((options -> padd)--)
			ret += ft_putchar_fd(' ', 1);
		ret += ft_putstr_len(s, options->prec);
	}
	return (ret);
}
