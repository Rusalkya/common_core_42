/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:47:22 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/27 16:16:38 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>

# define WIN_W 1920
# define WIN_H 1080

# define MOVE_SPEED 0.035
# define ROT_SPEED 0.025

# define MINIMAP_ 25
# define PLANE_FACTOR 0.85

# define PLAYER	0xb00000
# define FOV	0x999999
# define MAP_1	0x000000
# define MAP_0	0x606060

# define RST "\033[0m"
# define BOLD "\033[1m"
# define RED "\033[31m"
# define GRN "\033[32m"

# define MAP_CHAR_WALL '1'
# define MAP_CHAR_EMPTY '0'
# define MAP_CHAR_SPACE ' '
# define MAP_PLAYER_N 'N'
# define MAP_PLAYER_S 'S'
# define MAP_PLAYER_W 'W'
# define MAP_PLAYER_E 'E'

/* directions for textures/indexing */
typedef enum e_dir
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
}					t_dir;

/* small image wrapper to match common cub3d styles */
typedef struct s_img
{
	void			*ptr;
	void			*addr;
	int				w;
	int				h;
	int				bpp;
	int				line;
	int				endian;
}					t_img;

typedef struct s_player
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
}					t_player;

typedef struct g_mlx
{
	void			*mlx;
	void			*win;
	t_img			*no;
	t_img			*so;
	t_img			*we;
	t_img			*ea;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	unsigned int	floor_color;
	unsigned int	ceil_color;
}					t_mlx;

typedef struct g_key
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				r;
	int				l;
}					t_key;

typedef struct s_ray
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	int				side;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				tex_x;
	double			tex_step;
	double			tex_pos;
}					t_ray;

typedef struct g_hub
{
	t_mlx			*mlx;
	char			**map;
	t_key			*key;
	t_img			*img;
	t_img			*frame;
	t_player		*player;
	t_ray			*ray;
}					t_hub;

typedef struct g_2v
{
	int				x;
	int				y;
}					t_2v;

typedef struct s_map_data
{
	char			**map;
	int				line_count;
	int				map_started;
}					t_map_data;

void				msg_error(char *s1, char *s2, char *s3);
void				ft_exit(t_hub *hub, int i);
t_hub				*creat_hub(void);

/* images / textures */
void				load_img(t_hub *hub);
void				load_textures(t_hub *hub);

/* colors */
int					get_color(t_hub *hub, char *str);

/* parsing tokens */
int					wall_check(t_hub *hub, char *trim);

/* parsing helpers */
void				parse_map(char *filename, t_hub *hub);

/* map checking functions */
void				check_map_char(t_hub *hub);
void				check_player(char **map, t_hub *hub);
void				check_map_closed(t_hub *hub);
int					is_map_line(char *line);

/* map validation helpers */
int					get_map_height(char **map);
int					get_map_width(char **map);
char				**copy_map(char **map);
void				find_player_pos(char **map, int *px, int *py);
void				flood_fill(char **map_copy, int x, int y, int *error);
char				**read_map_from_file(char *filename, t_hub *hub);

/* map parsing helper functions */
char				**resize_map_array(char **map, int old_size, int new_size);
char				*clean_map_line(char *line);
char				**process_map_line(char **map, char *line, int *line_count,
						int *map_started);
int					open_map_file(char *filename, t_hub *hub);

/* read_map_utils.c */
void				skip_whitespace(char **str);
void				free_map_array(char **map);
int					handle_color_line(t_hub *h, char *trim);
int					process_line(t_hub *hub, char *line, t_map_data *data);

/* main parsing functions */
void				parse_cub_file(int argc, char **argv, t_hub *hub);
void				init_player(t_hub *hub);

/* display */
int					frame(t_hub *hub);
void				draw_wall(t_hub *hub, t_ray *ray, int x);
void				raycasting_wall(t_hub *hub);
void				draw_roof_floor(t_img *frame, t_hub *hub);
void				init_dda(t_hub *hub, t_ray *ray, int i);
void				dda(t_hub *hub, t_ray *ray);

/* other */
void				init(t_hub *hub, t_mlx *mlx);
void				put_px(t_img *frame, int x, int y, unsigned int color);
unsigned int		get_px(const t_img *frame, int x, int y);
int					destroy(t_hub *hub);
void				init_tex_coords(t_ray *ray, t_img *tex);
t_mlx				*creat_mlx(t_hub *hub);
void				check_map_closed(t_hub *hub);
t_img				*creat_img(t_hub *hub);

/* movement functions */
void				move_player(t_hub *hub, int direction);
void				rotate_player(t_player *player, int direction);
void				init_dir_factors(double dir_factors[5][4]);
void				apply_movement(t_hub *hub, double new_x, double new_y);
void				process_movement(t_hub *hub);
int					key_release(int keybord, t_hub *hub);
int					key_press(int keybord, t_hub *hub);

#endif