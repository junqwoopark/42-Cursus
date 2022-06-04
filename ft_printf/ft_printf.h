/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:13:01 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/09 02:32:52 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft/libft.h"

typedef struct s_options
{
	int		left;
	int		zero;
	int		width;
	int		prec;
	char	type;
	int		padd;
	int		is_minus;
}	t_options;

// ft_printf_utils.c
int			ft_putsize_t_base_fd(size_t p, char *base, int fd, t_options *options);
int			ft_lensize_t_base(size_t p, char *base, t_options *options);
int			ft_lennbr_base(int n, char *base);
int			ft_putnbr_base_fd(int n, char *base, int fd);
void		set_width_or_prec(int	*ptr, va_list *ap, char **p_format);

// ft_printf_print.c
int			print_p(t_options *options, va_list *ap);
int			print_ui(t_options *options, va_list *ap, char *base);
int			print_d(t_options *options, va_list *ap, char *base);
int			print_c(t_options *options, va_list *ap);
int			print_percent(t_options *options);
int			print_s(t_options *options, va_list *ap);

// ft_printf.c
void		init_options(t_options *p_options);
t_options	get_options(va_list *ap, char **p_format, t_options *p_options);
int			print(t_options options, va_list *ap);
int			parse_format(va_list ap, char *format);
int			ft_printf(const char *format, ...);

#endif
