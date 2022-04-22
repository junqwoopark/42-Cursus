/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 00:58:02 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/20 00:50:17 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		exit_with_error("argc is not 2");
	init_game(&game, argv[1]);
	draw_game(&game);
	mlx_hook(game.mlx.win_ptr, X_EVENT_KEY_PRESS, 0, key_input, &game);
	mlx_hook(game.mlx.win_ptr, X_EVENT_KEY_EXIT, 0, exit_game, &game);
	mlx_loop(game.mlx.mlx_ptr);
}
