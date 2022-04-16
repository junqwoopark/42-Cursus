/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 00:58:02 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/16 21:54:13 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	exit_with_error(char *error_message)
{
	printf("Error\n%s", error_message);
	exit(1);
}

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
	if (ft_strncmp(extension, file_extension, ft_strlen(extension)))
		exit_with_error("check file extension");
}

void	set_map_lines(t_map *map, int fd)
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

void	check_surrounded_by_walls(t_map *map)
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

void	check_element(t_map *map)
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

void	check_map_rectangle(t_map *map)
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

void	init_map(t_map *map, char *map_file)
{
	check_file_extension(map_file, ".ber");
	read_map(map, map_file);
	check_map(map);
}

void	init_player(t_game *game)
{
	int	r;
	int	c;

	game->player.move = 0;
	r = 0;
	while (r < game->map.height)
	{
		c = 0;
		while (c < game->map.width)
		{
			if (game->map.lines[r][c] == 'P')
			{
				game->player.x = r;
				game->player.y = c;
			}
			c++;
		}
		r++;
	}
}

void	init_mlx(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (game->mlx.mlx_ptr == NULL)
		exit_with_error("mlx_init() error");
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr,
			game->map.width * 64, game->map.height * 64, "so_long");
	if (game->mlx.win_ptr == NULL)
		exit_with_error("mlx_new_window() error");
}

void	init_img(t_game *game)
{
	int	width;
	int	height;

	game->img.collect = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			"./asset/collect.xpm", &width, &height);
	game->img.exit = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			"./asset/exit.xpm", &width, &height);
	game->img.player = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			"./asset/player.xpm", &width, &height);
	game->img.wall = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			"./asset/wall.xpm", &width, &height);
	game->img.road = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			"./asset/road.xpm", &width, &height);
	if (!(game->img.collect && game->img.exit
			&&game->img.player && game->img.wall && game->img.road))
		exit_with_error("init_img() error");
}

void	init_game(t_game *game, char *map_file)
{
	init_map(&(game->map), map_file);
	init_player(game);
	init_mlx(game);
	init_img(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		exit_with_error("argc is not 2");
	init_game(&game, argv[1]);
	mlx_loop(game.mlx.mlx_ptr);
}
