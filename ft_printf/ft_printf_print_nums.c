/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_nums.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:36:26 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/07 17:41:52 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	set_padd_precision(va_list *ap, char *base, t_options *options)
{
	unsigned int	u;
	int				len;

	u = (unsigned int) va_arg(*ap, unsigned int);
	if ((options->type == 'd' || options->type == 'i') && (int) u < 0)
	{
		u = (int) u * -1;
		options->is_minus = 1;
	}
	len = ft_lensize_t_base(u, base);
	if (len < options->prec)
	{
		len = options->prec;
		options->prec = options->prec - ft_lensize_t_base(u, base);
	}
	else if (options->prec != -1)
		options->prec = 0;
	if (len < options->width)
	{
		options->padd = options->width - len;
		if (options->is_minus && (options->type == 'i' || options->type == 'd'))
			options->padd -= 1;
	}
	return (u);
}

int	print_int(char *base, t_options *options, unsigned int u)
{
	int	ret;

	ret = 0;
	if (options->left)
	{
		if (options->is_minus)
			ret += ft_putchar_fd('-', 1);
		while (options->prec-- > 0)
			ret += ft_putchar_fd('0', 1);
		ret += ft_putsize_t_base_fd(u, base, 1);
		while (options->padd--)
			ret += ft_putchar_fd(' ', 1);
	}
	else
	{
		while (options->padd--)
			ret += ft_putchar_fd(' ', 1);
		if (options->is_minus)
			ret += ft_putchar_fd('-', 1);
		while (options->prec-- > 0)
			ret += ft_putchar_fd('0', 1);
		ret += ft_putsize_t_base_fd(u, base, 1);
	}
	return (ret);
}

int	print_p(t_options *options, va_list *ap)
{
	int			len;
	size_t		p;
	int			ret;

	ret = 0;
	p = (size_t)va_arg(*ap, size_t);
	len = 2 + ft_lensize_t_base(p, "0123456789abcdef");
	if (len < options->width)
		options->padd = options->width - len;
	if (options -> left == 1)
	{
		ret += ft_putstr_fd("0x", 1);
		ret += ft_putsize_t_base_fd(p, "0123456789abcdef", 1);
		while ((options -> padd)--)
			ret += ft_putchar_fd(' ', 1);
	}
	else
	{
		while ((options -> padd)--)
			ret += ft_putchar_fd(' ', 1);
		ret += ft_putstr_fd("0x", 1);
		ret += ft_putsize_t_base_fd(p, "0123456789abcdef", 1);
	}
	return (ret);
}

int	print_ui(t_options *options, va_list *ap, char *base)
{
	unsigned int	u;
	int				ret;

	u = set_padd_precision(ap, base, options);
	if (options->zero && !options->left && options->prec == -1)
	{
		options->prec = options->padd;
		options->padd = 0;
	}
	ret = print_int(base, options, u);
	return (ret);
}

int	print_d(t_options *options, va_list *ap, char *base)
{
	unsigned int	u;
	int				ret;

	u = set_padd_precision(ap, base, options);
	if (options->zero && !options->left && options->prec == -1)
	{
		options->prec = options->padd;
		options->padd = 0;
	}
	ret = print_int(base, options, u);
	return (ret);
}
