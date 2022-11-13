/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:45:26 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/20 00:53:06 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_map(t_map *map, char *map_file)
{
	check_file_extension(map_file, ".ber");
	read_map(map, map_file);
	check_map(map);
}

static void	init_player(t_game *game)
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
				game->player.pos.x = r;
				game->player.pos.y = c;
			}
			c++;
		}
		r++;
	}
}

static void	init_mlx(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (game->mlx.mlx_ptr == NULL)
		exit_with_error("mlx_init() error");
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr,
			game->map.width * 32, game->map.height * 32, "so_long");
	if (game->mlx.win_ptr == NULL)
		exit_with_error("mlx_new_window() error");
}

static void	init_img(t_game *game)
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
