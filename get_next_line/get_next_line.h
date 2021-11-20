/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:48:02 by junkpark          #+#    #+#             */
/*   Updated: 2021/11/20 19:46:56 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>

char	*get_next_line(int fd);
int		update_buff(char *s_buff, size_t idx);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(void *dst, const void *src, size_t len);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
char	*free_tmp(char *tmp);
void	ft_cpycat(char *dst, char *src1, char *src2, size_t idx);

#endif
