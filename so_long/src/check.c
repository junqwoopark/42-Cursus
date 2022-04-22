/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:48:32 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/20 01:01:02 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_file_extension(char *file, char *file_extension)
{
	int		file_len;
	int		file_extension_len;
	char	*extension;

	file_len = ft_strlen(file);
	file_extension_len = ft_strlen(file_extension);
	if (file_len < file_extension_len)
		exit_with_error("check file extension");
	extension = ft_strrchr(file, '.');
	if (extension == NULL)
		exit_with_error("check file extension");
	if (ft_strncmp(extension, file_extension, ft_strlen(file_extension)))
		exit_with_error("check file extension");
}

static void	check_surrounded_by_walls(t_map *map)
{
	int	r;
	int	c;

	r = 0;
	while (r < map->height)
	{
		c = 0;
		while (c < map->width)
		{
			if (r == 0 || r == map->height - 1 || c == 0
				|| c == map->width - 1)
			{
				if (map->lines[r][c] != '1')
					exit_with_error("map error");
			}
			c++;
		}
		r++;
	}
}

static void	check_element(t_map *map)
{
	int	r;
	int	c;

	ft_bzero(map->elements, sizeof(map->elements));
	r = 0;
	while (r < map->height)
	{
		c = 0;
		while (c < map->width)
		{
			if (map->lines[r][c] == 'C')
				map->elements[COLLECT] += 1;
			else if (map->lines[r][c] == 'E')
				map->elements[EXIT] += 1;
			else if (map->lines[r][c] == 'P')
				map->elements[PLAYER] += 1;
			else if (map->lines[r][c] != '0' && map->lines[r][c] != '1')
				exit_with_error("map error");
			c++;
		}
		r++;
	}
	if (map->elements[COLLECT] < 1 || map->elements[EXIT] < 1
		|| map->elements[PLAYER] != 1)
		exit_with_error("map elements error");
}

static void	check_map_rectangle(t_map *map)
{
	int	r;

	r = 0;
	if (map->width >= 3 || map->height >= 3)
	{
		while (r < map->height)
		{
			if ((int) ft_strlen(map->lines[r]) != map->width)
				exit_with_error("map error");
			r++;
		}
	}
	else
		exit_with_error("map error");
}

void	check_map(t_map *map)
{
	map->width = ft_strlen(map->lines[0]);
	if (map->height == 0 || map->width == 0)
		exit_with_error("map error");
	check_surrounded_by_walls(map);
	check_element(map);
	check_map_rectangle(map);
}
