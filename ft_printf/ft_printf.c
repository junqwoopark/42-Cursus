/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:26:58 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/07 20:09:29 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	init_options(t_options *p_options)
{
	p_options->left = 0;
	p_options->zero = 0;
	p_options->width = 0;
	p_options->prec = -1;
	p_options->type = 0;
	p_options->padd = 0;
	p_options->is_minus = 0;
}

t_options	get_options(va_list *ap, char **p_format, t_options *p_options)
{
	init_options(p_options);
	if (**p_format == '-')
	{
		p_options->left = 1;
		(*p_format)++;
	}
	if (**p_format == '0')
	{
		p_options->zero = 1;
		(*p_format)++;
	}
	set_width_or_prec(&(p_options->width), ap, p_format);
	while (ft_isdigit(**p_format) || **p_format == '*')
		(*p_format)++;
	if (**p_format == '.')
	{
		(*p_format)++;
		set_width_or_prec(&(p_options->prec), ap, p_format);
	}
	while (ft_isdigit(**p_format) || **p_format == '*')
		(*p_format)++;
	p_options->type = **p_format;
	return (*p_options);
}

int	print(t_options options, va_list *ap)
{
	if (options.type == 'c')
		return (print_c(&options, ap));
	else if (options.type == '%')
		return (print_percent(&options));
	else if (options.type == 's')
		return (print_s(&options, ap));
	else if (options.type == 'p')
		return (print_p(&options, ap));
	else if (options.type == 'd' || options.type == 'i')
		return (print_d(&options, ap, "0123456789"));
	else if (options.type == 'u')
		return (print_ui(&options, ap, "0123456789"));
	else if (options.type == 'x')
		return (print_ui(&options, ap, "0123456789abcdef"));
	else if (options.type == 'X')
		return (print_ui(&options, ap, "0123456789ABCDEF"));
	return (1);
}

int	parse_format(va_list ap, char *format)
{
	int			result;
	t_options	options;

	result = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 0)
				break ;
			options = get_options(&ap, &format, &options);
			result += print(options, &ap);
		}
		else
			result += ft_putchar_fd(*format, 1);
		format++;
	}
	return (result);
}

int	ft_printf(const char *format, ...)
{
	int		result;
	va_list	ap;

	va_start(ap, format);
	result = parse_format(ap, (char *)format);
	va_end(ap);
	return (result);
}
