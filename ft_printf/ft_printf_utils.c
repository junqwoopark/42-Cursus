/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:40:00 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/07 18:30:54 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putsize_t_base_fd(size_t p, char *base, int fd)
{
	char	final[100];
	int		idx;
	int		ret;
	size_t	base_n;

	if (p == 0)
		return (ft_putchar_fd('0', 1));
	base_n = ft_strlen(base);
	idx = 0;
	while (p)
	{
		final[idx] = base[p % base_n];
		p = p / base_n;
		idx++;
	}
	ret = 0;
	while (--idx >= 0)
		ret += ft_putchar_fd(final[idx], fd);
	return (ret);
}

int	ft_lensize_t_base(size_t p, char *base)
{
	char	final[100];
	int		idx;
	size_t	base_n;

	base_n = ft_strlen(base);
	idx = 0;
	if (p == 0)
		return (1);
	while (p)
	{
		final[idx] = base[p % base_n];
		p = p / base_n;
		idx++;
	}
	return (idx);
}

int	ft_lennbr_base(int n, char *base)
{
	char			final[100];
	int				idx;
	unsigned int	tmp;
	size_t			base_n;

	base_n = ft_strlen(base);
	idx = 0;
	if (n < 0)
	{
		final[idx++] = '-';
		tmp = -n;
	}
	tmp = n;
	while (tmp)
	{
		final[idx] = base[tmp % base_n];
		tmp = tmp / base_n;
		idx++;
	}
	return (idx);
}

int	ft_putnbr_base_fd(int n, char *base, int fd)
{
	char			final[100];
	int				idx;
	int				ret;
	unsigned int	tmp;
	size_t			base_n;

	base_n = ft_strlen(base);
	idx = 0;
	tmp = n;
	if (n < 0)
		tmp = -n;
	while (tmp)
	{
		final[idx] = base[tmp % base_n];
		tmp = tmp / base_n;
		idx++;
	}
	ret = idx;
	while (--idx >= 0)
		ft_putchar_fd(final[idx], fd);
	return (ret);
}

void	set_width_or_prec(int	*ptr, va_list *ap, char **p_format)
{
	if (**p_format == '*')
		*ptr = (int)va_arg(*ap, int);
	else
		*ptr = ft_atoi(*p_format);
}
