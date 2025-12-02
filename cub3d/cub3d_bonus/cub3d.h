/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:47:22 by cade-jes          #+#    #+#             */
/*   Updated: 2025/12/02 16:12:30 by clfouger         ###   ########.fr       */
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

# define PLANE_FACTOR 0.80

/* minimap */
# define MINIMAP_SCALE 30
# define MN_1 0x000000
# define MN_0 0x606060
# define MN_CX 200
# define MN_CY 200
# define MN_R 150

# define MOUSE_X 960
# define MOUSE_Y 540
# define MOUSE_SENS 0.0006

# define PLAYER 0xb00000
# define FOV 0x999999
# define FLOOR 0x202020
# define ROOF 0x505050

# define RST "\033[0m"
# define BOLD "\033[1m"
# define RED "\033[31m"
# define GRN "\033[32m"

# define MAP_CHAR_WALL '1'
# define MAP_CHAR_EMPTY '0'
# define MAP_CHAR_SPACE ' '
# define MAP_CHAR_CRACKED '2'
# define MAP_CHAR_CRACKED2 '3'
# define MAP_CHAR_CRACKED3 '4'
# define MAP_CHAR_HOLE '5'
# define MAP_PLAYER_N 'N'
# define MAP_PLAYER_S 'S'
# define MAP_PLAYER_W 'W'
# define MAP_PLAYER_E 'E'
# define MAP_HAMMER 'H'

typedef struct s_minimap
{
	int						dx;
	int						dy;
	int						sx;
	int						sy;
	int						err;
	int						e2;
}							t_mini;

/* directions for textures/indexing */
typedef enum e_dir
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
}							t_dir;

/* small image wrapper to match common cub3d styles */
typedef struct s_img
{
	void					*ptr;
	void					*addr;
	int						w;
	int						h;
	int						bpp;
	int						line;
	int						endian;
}							t_img;

typedef struct s_player
{
	double					posx;
	double					posy;
	double					dirx;
	double					diry;
	double					planex;
	double					planey;
}							t_player;

typedef struct g_mlx
{
	void					*mlx;
	void					*win;
	t_img					*no;
	t_img					*so;
	t_img					*we;
	t_img					*ea;
	t_img					*so_crack;
	t_img					*so_crack2;
	t_img					*so_crack3;
	t_img					*wall_hole1;
	t_img					*wall_hole2;
	t_img					*hammer_sprite;
	t_img					*floor_sprite;
	t_img					*roof_sprite;
	t_img					*screamers[3];
	char					*no_path;
	char					*so_path;
	char					*we_path;
	char					*ea_path;
	unsigned int			floor_color;
	unsigned int			ceil_color;
	int						wall_hole_frame;
	int						wall_hole_counter;
}							t_mlx;

typedef struct g_key
{
	int						w;
	int						a;
	int						s;
	int						d;
	int						r;
	int						l;
	int						ctrl;
}							t_key;

typedef struct g_parse
{
	int						no;
	int						so;
	int						we;
	int						ea;
	char					*no_path;
	char					*so_path;
	char					*we_path;
	char					*ea_path;
}							t_parse;

typedef struct s_ray
{
	double					camera_x;
	double					ray_dir_x;
	double					ray_dir_y;
	int						map_x;
	int						map_y;
	double					side_dist_x;
	double					side_dist_y;
	double					delta_dist_x;
	double					delta_dist_y;
	int						step_x;
	int						step_y;
	int						side;
	double					perp_wall_dist;
	int						line_height;
	int						draw_start;
	int						draw_end;
	double					wall_x;
	int						tex_x;
	double					tex_step;
	double					tex_pos;
}							t_ray;

typedef struct g_2v
{
	int						x;
	int						y;
}							t_2v;

typedef struct s_hammer
{
	int						x;
	int						y;
	int						active;
	double					angle;
}							t_hammer;

typedef struct s_hammer_list
{
	t_hammer				*hammer;
	struct s_hammer_list	*next;
}							t_hammer_list;

typedef struct s_hammer_draw
{
	double					dx;
	double					dy;
	double					distance;
	double					angle;
	double					relative_angle;
	int						screen_x;
	int						sprite_height;
}							t_hammer_draw;

typedef struct s_pov
{
	t_img					*empty1;
	t_img					*empty2;
	t_img					*hammer1;
	t_img					*hammer2;
	t_img					*hammer_hit1;
	t_img					*hammer_hit2;
	t_img					*hammer_hit3;
	t_img					*hammer_pow;
	t_img					*hammer_crack;
	t_img					*hammer_boom;
	int						current_frame;
	int						frame_counter;
	int						animation_speed;
	int						is_attacking;
	int						attack_frame;
	int						attack_type;
}							t_pov;

typedef struct s_map_data
{
	char			**map;
	int				line_count;
	int				map_started;
}					t_map_data;

typedef struct g_hub
{
	t_mlx					*mlx;
	char					**map;
	t_key					*key;
	t_img					*img;
	t_img					*frame;
	t_player				*player;
	t_ray					*ray;
	t_hammer_list			*hammers;
	int						has_hammer;
	t_pov					*pov;
	int						is_moving;
	int						door_broken;
	int						timer_active;
	int						timer_seconds;
	int						screamer_counter;
	int						show_screamer;
	int						screamer_index;
	int						screamer_display_time;
	int						ambiance_started;
	int						total_screamers;
	int						screamer_sound_played;
	int						final_screamer_active;
	int						final_screamer_frame;
	int						final_screamer_counter;
	int						fade_to_black_progress;
	pid_t					footstep_pid;
	pid_t					ambiance_pid;
	pid_t					music_pid;
	pid_t					end_sound_pid;
}							t_hub;

void						msg_error(char *s1, char *s2, char *s3);
void						ft_exit(t_hub *hub, int i);
t_hub						*creat_hub(void);
t_ray						*creat_ray(t_hub *hub);
void						init_hub_timer_values(t_hub *hub);

/* exit helpers */
void						free_basic_textures(t_hub *hub);
void						free_crack_textures(t_hub *hub);
void						free_hole_textures(t_hub *hub);
void						free_sprite_textures(t_hub *hub);

/* init helpers */
int							load_wall(t_mlx *mlx, t_img *img, char *path);
void						load_basic_walls(t_hub *hub);
void						load_crack_walls(t_hub *hub);
void						load_hole_walls(t_hub *hub);
void						load_sprite_textures(t_hub *hub);
void						free_image(t_hub *hub, int i);

/* images / textures */
void						load_img(t_hub *hub);
void						load_textures(t_hub *hub);

/* colors */
int							get_color(t_hub *hub, char *str);

/* parsing tokens */
void						no_parse(char *filename, t_parse *parse,
								t_hub *hub);
void						so_parse(char *filename, t_parse *parse,
								t_hub *hub);
void						we_parse(char *filename, t_parse *parse,
								t_hub *hub);
void						ea_parse(char *filename, t_parse *parse,
								t_hub *hub);

/* parsing helpers */
void						parse_map(char *filename, t_hub *hub);
t_img						*creat_img(t_hub *hub);
void						skip_whitespace(char **str);

/* map checking functions */
void						check_map_char(t_hub *hub);
void						check_player(char **map, t_hub *hub);
void						check_cracked_walls(t_hub *hub);
int							is_map_line(char *line);
char						**read_map_from_file(char *filename, t_hub *hub);
int							wall_check(t_hub *hub, char *trim);
void						check_map_closed(t_hub *hub);
int							get_map_height(char **map);
int							get_map_width(char **map);
char						**copy_map(char **map);
void						find_player_pos(char **map, int *px, int *py);

/* map parsing helper functions */
char						**resize_map_array(char **map, int old_size,
								int new_size);
char						*clean_map_line(char *line);
char						**process_map_line(char **map, char *line,
								int *line_count, int *map_started);
int							open_map_file(char *filename, t_hub *hub);
int							process_line(t_hub *hub, char *line,
								t_map_data *data);

/* main parsing functions */
void						parse_cub_file(int argc, char **argv, t_hub *hub);
void						init_player(t_hub *hub);

/* display */
int							frame(t_hub *hub);
/* display */
int							frame(t_hub *hub);
void						draw_wall(t_hub *hub, t_ray *ray, int x);
void						raycasting_wall(t_hub *hub);
void						draw_roof_floor(t_hub *hub);
void						init_dda(t_hub *hub, t_ray *ray, int i);
void						dda(t_hub *hub, t_ray *ray);
void						init(t_hub *hub, t_mlx *mlx);
void						put_px(t_img *frame, int x, int y,
								unsigned int color);
unsigned int				get_px(const t_img *frame, int x, int y);
int							destroy(t_hub *hub);
void						init_tex_coords(t_ray *ray, t_img *tex);
t_mlx						*creat_mlx(t_hub *hub);
void						minimap(t_hub *hub);
void						draw_rays_on_minimap(t_hub *hub, t_ray *ray);
int							verif_draw_minimap(int x, int y);
int							mouse_move(int x, int y, t_hub *hub);
void						init_mouse(t_hub *hub);

/* movement functions */
void						move_player(t_hub *hub, int direction);
void						rotate_player(t_player *player, int direction);
void						init_dir_factors(double dir_factors[5][4]);
void						apply_movement(t_hub *hub, double new_x,
								double new_y);
void						process_movement(t_hub *hub);
int							key_release(int keybord, t_hub *hub);
int							key_press(int keybord, t_hub *hub);

/* hammer functions */
void						init_hammers(t_hub *hub);
void						render_hammers(t_hub *hub);
void						render_hammers_in_world(t_hub *hub);
void						check_hammer_collect(t_hub *hub);
void						add_hammer(t_hub *hub, int x, int y);
void						free_hammers(t_hammer_list *hammers);
void						init_hammer_draw(t_hammer_draw *d, t_hub *hub,
								t_hammer *hammer);
void						calc_hammer_screen_pos(t_hammer_draw *d,
								t_hub *hub);
void						get_tex_coord(int *tex_x, int stripe, t_hub *hub,
								int sh);

/* pov functions */
void						init_pov(t_hub *hub);
void						render_pov(t_hub *hub);
void						update_pov_animation(t_hub *hub);
void						free_pov(t_hub *hub);
void						start_hammer_attack(t_hub *hub);
void						update_hammer_attack(t_hub *hub);
int							mouse_click(int button, int x, int y, t_hub *hub);
t_img						*get_attacking_sprite(t_hub *hub);
t_img						*get_current_pov_sprite(t_hub *hub);
int							is_transparent(unsigned int color);

/* stains functions */
void						generate_stains(t_hub *hub);
void						free_stains(t_hub *hub);
void						render_stains_on_floor(t_hub *hub, int x, int y);
/* wall_hole animation */
void						update_wall_hole_animation(t_hub *hub);
t_img						*get_wall_hole_sprite(t_hub *hub);
void						flip_image_horizontal(t_img *img);

/* timer and screamer system */
void						update_timer(t_hub *hub);
void						render_screamer(t_hub *hub);
void						free_screamers(t_hub *hub);
void						render_red_filter(t_hub *hub);
void						render_timer_display(t_hub *hub);
void						update_screamer_display(t_hub *hub,
								long long current_time, long long *last_time);
void						update_timer_counter(t_hub *hub,
								long long current_time, long long *last_time);
void						render_screamer_loop(t_hub *hub, t_img *screamer,
								int *s);
void						render_red_filter_loop(t_hub *hub,
								int time_elapsed);
void						update_final_screamer(t_hub *hub);
void						render_final_fade(t_hub *hub);

/* sound system */
void						play_sound(char *sound_file);
void						play_hammer_sound(void);
void						play_air_hit_sound(void);
void						play_footstep_sound(t_hub *hub);
void						stop_footstep_sound(t_hub *hub);
void						play_screamer_sound(void);
void						play_music_sound(t_hub *hub);
void						play_ambiance_track(t_hub *hub, int track_num);
void						stop_all_sounds(t_hub *hub);
void						play_end_sound(t_hub *hub);

#endif
