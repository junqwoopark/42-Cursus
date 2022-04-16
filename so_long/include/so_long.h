/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:28:14 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/16 21:35:49 by junkpark         ###   ########.fr       */
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

enum e_elements
{
	COLLECT,
	EXIT,
	PLAYER
};

typedef struct s_map
{
	int		height;
	int		width;
	char	**lines;
	int		elements[3];
}	t_map;

typedef struct s_player
{
	int	x;
	int	y;
	int	move;
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

#endif
