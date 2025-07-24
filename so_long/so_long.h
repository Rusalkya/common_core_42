/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:18:47 by clfouger          #+#    #+#             */
/*   Updated: 2025/07/23 15:55:18 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdint.h>
# include <stdlib.h>

# define TILE_SIZE 64
# define MAP_ROWS 7

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}			t_img;

typedef struct s_counts
{
	int		p;
	int		c;
	int		e;
	int		v;
}			t_counts;

typedef struct s_anim
{
	void	*frame1;
	void	*frame2;
	int		width;
	int		height;
}			t_anim;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		width;
	int		height;
	char	*filename;

	t_img	player_base[4];
	t_anim	player_run[4];
	int		player_dir;
	int		player_frame;
	int		player_x;
	int		player_y;

	int		villain_x;
	int		villain_y;
	int		villain_dir;
	t_img	villain_base[4];
	int		villain_frame;

	t_img	item;
	int		total_items;
	int		collected_items;

	t_img	floor;
	t_img	wall_1;
	t_img	wall_3;
	t_img	wall_dd;
	t_img	wall_gg;
	t_img	wall_d;
	t_img	wall_g;

	t_img	exit;
	t_img	noexit;

	int		move_count;
}			t_game;

// main.c
int		init_game(t_game *g);
int		main(int argc, char **argv);
// map/maped.c
void	draw_tile(t_game *g, void *img, int x, int y);
void	draw_wall_sprite(t_game *g, int x, int y);
void	map_setting(t_game *g);
// map/map.c
int		read_map(const char *file, t_game *g);
void	free_map(char **map);
// map/map_checking.c
int		validate_map(t_game *g);
// display/display_player.c
void	find_player(t_game *g);
int		load_player_images(t_game *g);
int		load_player_animsud(t_game *g);
int		load_player_animslr(t_game *g);
// display/display_villain.c
void	find_villain(t_game *g);
int		load_villain_images(t_game *g);
// display/display_map.c
int		load_wall_images(t_game *game);
int		load_other_images(t_game *game);
void	update_exit_sprite(t_game *g);
void	check_items(t_game *g, int x, int y);
// display/display.c
void	display_move_count(t_game *g);
// verif.c
int		game_is_ok(t_game *g, const char *filename);
// cleaning.c
int		clean_everything(t_game *g);
// controls.c
int		handle_input_player(int keycode, t_game *g);
int		handle_input_villain(int keycode, t_game *g);
int		game_loop(t_game *g);
// control_player.c
int		handle_input_player(int keycode, t_game	*g);

#endif
