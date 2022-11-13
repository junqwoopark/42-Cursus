/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:28:14 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/20 01:01:47 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../lib/minilibx_opengl/mlx.h"
# include "../lib/libft/libft.h"
# include "../lib/libgnl/get_next_line.h"

enum e_x_events
{
	X_EVENT_KEY_PRESS = 2,
	X_EVENT_KEY_RELEASE = 3,
	X_EVENT_KEY_EXIT = 17
};

enum e_elements
{
	COLLECT,
	EXIT,
	PLAYER
};

enum e_keys
{
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_ESC = 53
};

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_map
{
	int		height;
	int		width;
	char	**lines;
	int		elements[3];
}	t_map;

typedef struct s_player
{
	t_pos	pos;
	int		move;
}	t_player;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

typedef struct s_img
{
	void	*player;
	void	*exit;
	void	*collect;
	void	*wall;
	void	*road;
}	t_img;

typedef struct s_game
{
	t_map		map;
	t_player	player;
	t_mlx		mlx;
	t_img		img;
}	t_game;

// check.c
void		check_file_extension(char *file, char *file_extension);
// static void	check_surrounded_by_walls(t_map *map);
// static void	check_element(t_map *map);
// static void	check_map_rectangle(t_map *map);
void		check_map(t_map *map);

// init.c
// static void	init_map(t_map *map, char *map_file);
// static void	init_player(t_game *game);
// static void	init_mlx(t_game *game);
// static void	init_img(t_game *game);
void		init_game(t_game *game, char *map_file);

// map.c
// static void	set_map_lines(t_map *map, int fd);
void		read_map(t_map *map, char *map_file);

// player.c
// static int	is_movable(t_game *game, t_pos pos);
// static void	change_board(t_game *game, t_pos n_pos);
void		player_move(int key, t_game *game);

// utils.c
void		exit_with_error(char *error_message);
void		put_img(t_game *game, int r, int c);
void		draw_game(t_game *game);
int			exit_game(t_game *game);
int			key_input(int key, t_game *game);

// main.c
int			main(int argc, char **argv);

#endif
