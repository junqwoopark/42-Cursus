/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:47:12 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/20 00:56:18 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_movable(t_game *game, t_pos pos)
{
	if (0 <= pos.x && pos.x < game->map.height
		&& 0 <= pos.y && pos.y < game->map.width)
	{
		if (game->map.lines[pos.x][pos.y] == '1')
			return (0);
		else if (game->map.lines[pos.x][pos.y] == 'E'
			&& game->map.elements[COLLECT] != 0)
			return (0);
		return (1);
	}
	return (0);
}

static void	change_board(t_game *game, t_pos n_pos)
{
	game->map.lines[game->player.pos.x][game->player.pos.y] = '0';
	game->player.move += 1;
	printf("player move : %d\n", game->player.move);
	if (game->map.lines[n_pos.x][n_pos.y] == 'C')
		game->map.elements[COLLECT] -= 1;
	else if (game->map.lines[n_pos.x][n_pos.y] == 'E')
	{
		printf("You succeeded in escaping!!!\n");
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
		exit(0);
	}
	put_img(game, game->player.pos.x, game->player.pos.y);
	game->map.lines[n_pos.x][n_pos.y] = 'P';
	game->player.pos.x = n_pos.x;
	game->player.pos.y = n_pos.y;
	put_img(game, game->player.pos.x, game->player.pos.y);
}

void	player_move(int key, t_game *game)
{
	t_pos	n_pos;

	n_pos.x = game->player.pos.x;
	n_pos.y = game->player.pos.y;
	if (key == KEY_W)
		n_pos.x = n_pos.x - 1;
	else if (key == KEY_A)
		n_pos.y = n_pos.y - 1;
	else if (key == KEY_S)
		n_pos.x = n_pos.x + 1;
	else if (key == KEY_D)
		n_pos.y = n_pos.y + 1;
	if (is_movable(game, n_pos))
		change_board(game, n_pos);
}
