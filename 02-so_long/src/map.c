/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:49:15 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/20 00:53:29 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	set_map_lines(t_map *map, int fd)
{
	int		idx;
	char	*line;
	char	*tmp;
	char	*one_line;

	idx = 0;
	tmp = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		one_line = ft_strjoin(tmp, line);
		if (one_line == NULL)
			exit_with_error("malloc error");
		free(line);
		free(tmp);
		tmp = one_line;
		idx++;
		line = get_next_line(fd);
	}
	map->height = idx;
	map->lines = ft_split(tmp, '\n');
	free(tmp);
	if (map->lines == NULL)
		exit_with_error("map error");
}

void	read_map(t_map *map, char *map_file)
{
	int		fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		exit_with_error("check map file");
	set_map_lines(map, fd);
	check_map(map);
	close(fd);
}
