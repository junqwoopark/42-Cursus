/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:50:04 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/20 00:51:33 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_with_error(char *error_message)
{
	printf("Error\n%s", error_message);
	exit(1);
}

void	put_img(t_game *game, int r, int c)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = game->mlx.mlx_ptr;
	win_ptr = game->mlx.win_ptr;
	mlx_put_image_to_window(mlx_ptr, win_ptr, game->img.road, c * 64, r * 64);
	if (game->map.lines[r][c] == '1')
		mlx_put_image_to_window(mlx_ptr, win_ptr,
			game->img.wall, c * 64, r * 64);
	else if (game->map.lines[r][c] == 'C')
		mlx_put_image_to_window(mlx_ptr, win_ptr,
			game->img.collect, c * 64, r * 64);
	else if (game->map.lines[r][c] == 'P')
		mlx_put_image_to_window(mlx_ptr, win_ptr,
			game->img.player, c * 64, r * 64);
	else if (game->map.lines[r][c] == 'E')
		mlx_put_image_to_window(mlx_ptr, win_ptr,
			game->img.exit, c * 64, r * 64);
}

void	draw_game(t_game *game)
{
	int	r;
	int	c;

	r = 0;
	while (r < game->map.height)
	{
		c = 0;
		while (c < game->map.width)
		{
			put_img(game, r, c);
			c++;
		}
		r++;
	}
}

int	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	exit(0);
}

int	key_input(int key, t_game *game)
{
	if (key == KEY_ESC)
		exit_game(game);
	else if (key == KEY_A || key == KEY_S || key == KEY_D || key == KEY_W)
		player_move(key, game);
	return (0);
}
