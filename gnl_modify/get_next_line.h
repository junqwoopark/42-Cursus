/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:48:02 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/08 22:30:35 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <unistd.h>
# include <stdlib.h>

// get_next_line.c
void	ft_cpycat(char	*dst, char *src1, char *src2, size_t idx);
char	*malloc_ret(char *tmp, char *buff, size_t *idx);
char	*get_next_line(int fd);
void	ft_buffcpy(char	*buff, size_t idx);
int		update_buff(char *buff, size_t idx);

// get_next_line_utils.c
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(void *dst, const void *src, size_t len);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_bufflen(const char *s);
void	*ft_calloc(size_t count, size_t size);

#endif
