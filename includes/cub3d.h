/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 14:13:30 by clorin            #+#    #+#             */
/*   Updated: 2021/01/12 16:04:47 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <float.h>
# include "../libft/libft.h"
# include "mlx.h"

# define FALSE 0
# define TRUE 1
# define FOV_ANGLE 1.04719755
# define WALL_STRIP_WIDTH 1
# define KEY_A 97
# define KEY_W 119
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC	65307//53//
# define KEY_M		109//46
# define KEY_LEFT	65361//123//
# define KEY_RIGHT	65363//124//
# define KEY_UP		65362//126//
# define KEY_DOWN	65364//125//
# define SIZE_MINI_MAP 0.2
# define NONE 0xFF000000
# define GRAY 0x00AAAAAA
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define MAGENTA 0x00FF00FF
# define YELLOW 0x00FFFF00
# define CYAN 0x0000FFFF
# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3
# define SPRITE 4

typedef struct	s_point
{
	float			x;
	float			y;
}				t_point;

typedef struct	s_ray
{
	float			angle;
	t_point			wall_hit;
	float			dist;
	int				top_pixel;
	int				bot_pixel;
	int				hit_vert;
	int				id;
}				t_ray;

typedef struct	s_map
{
	char			*name;
	char			**tab;
	unsigned int	num_rows;
	unsigned int	num_cols;
}				t_map;

typedef struct	s_image
{
	void			*img;
	char			*addr;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}				t_image;

typedef struct	s_player
{
	t_point			coord;
	float			radius;
	int				turn_dir;
	int				walk_dir;
	int				trans_dir;
	float			rot_angle;
	float			move_speed;
	float			rot_speed;
}				t_player;

typedef struct	s_texture
{
	void			*tex_ptr;
	char			*data;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}				t_texture;

typedef struct 	s_sprite
{
	
}				t_sprite;

typedef struct	s_win
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				width;
	int				height;
	int				num_rays;
	t_image			image;
	int				f_color;
	int				c_color;
	unsigned int	t_size;

}				t_win;

typedef struct	s_game
{
	t_win			win;
	t_map			map;
	t_player		player;
	int				save;
	t_texture		tex[5];
	int				nb_sprite;
	int				is_map;
}				t_game;

void			init_map(t_map *map, char *file_name);
void			init_player(t_player *player);
void			init_image(t_image *image);
void			init_win(t_win *win);
void			free_tab(char **tab);
void			free_rays(t_ray **tab, int len);
int				is_number(char *str);
int				setup_resol(t_game *game, char **tab);
int				setup_color(t_game *game, char **tab);
int				parse_color(char *str);
int				create_trgb(int t, int r, int g, int b);
int				parse_line(char *line, t_game *game, t_list **list);
int				parse_tab(t_game *game, char *line, t_list **list);
void			free_list(void *data);
int				map_setup(t_game *game, t_list *list);
void			free_map(t_map *map);
void			game_close(t_game *game);
void			free_win(t_win *win);
void			free_image(t_win *win);
int				check_map(t_game *game);
int				free_map_setup(t_list *list, int result);
int				check_player_pos(t_game *game);
void			creat_images(t_win *win);
int				deal_key(int key, t_game *game);
int				release_key(int key, t_game *game);
void			render(t_game *game);
void			cube(t_win *win, t_point point, int size, int color);
void			draw_lines(t_win *win, t_point a, t_point b, int color);
void			update_player(t_game *game);
int				is_wall_at(t_game *game, t_point pos);
int				is_sprite_at(t_game *game, t_point pos);
char			type_wall(t_game *game, t_point pos);
float			normalize_angle(float angle);
float			distance(t_point a, t_point b);
int				is_ray_facing_down(float angle);
int				is_ray_facing_up(float angle);
int				is_ray_facing_right(float angle);
int				is_ray_facing_left(float angle);
t_point			horz_wall_hit(float ray_angle, t_game *game);
t_point			vert_wall_hit(float ray_angle, t_game *game);
t_ray			**cast_all_rays(t_game *game);
int				find_color(int wall);
void			rect(t_win *win, t_point a, t_point coord, int color);
void			clear_image(t_win *win);
void			ft_mlx_pixel_put(t_win *win, int x, int y, int color);
int				init_texture(t_game *game, char *file, int nb);
void			free_texture(t_win *win, t_texture texture[5]);
int				parse_texture(t_game *game, char **tab);
void			right_trim(char *str);
/*
				BONUS
*/
void			render_ray_map(t_game *game, t_ray **rays);
void			render_player(t_game *game);
void			render_map(t_game *game);
void			fact_vect(t_point *point, float fact);
void			cpy_point(t_point *dst, t_point *src);
void			add_val_point(t_point *point, float val);
void			ft_print_list(t_list *list);

#endif
