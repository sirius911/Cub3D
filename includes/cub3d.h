/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 14:13:30 by clorin            #+#    #+#             */
/*   Updated: 2020/12/23 14:15:45 by clorin           ###   ########.fr       */
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
//# define PI 3.14159265
# define FOV_ANGLE 1.04719755
# define WALL_STRIP_WIDTH 1
# define KEY_ESC	53
# define KEY_M		46
# define KEY_LEFT	123
# define KEY_RIGHT	124
# define KEY_UP		126
# define KEY_DOWN	125
# define SIZE_MINI_MAP 0.3
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

typedef struct	s_point
{
	float			x;
	float			y;
}				t_point;

typedef struct	s_ray
{
	float			ray_angle;
	t_point			wall_hit;
	float			dist;
	int				was_hit_vert;
	int				facing_up;
	int				facing_down;
	int				facing_left;
	int				facing_right;
	int				wall_content;
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
	float			rot_angle;
	float			move_speed;
	float			rot_speed;
}				t_player;

typedef struct	s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				screen_width;
	int				screen_height;
	int				num_rays;
	t_image			image;
	int				floor_color;
	int				sky_color;
	unsigned int	tile_size;

}				t_window;

typedef struct	s_game
{
	t_window		window;
	t_map			map;
	t_player		player;
	int				save;
}				t_game;

void			init_map(t_map *map, char *file_name);
void			init_player(t_player *player);
void			init_image(t_image *image);
void			init_window(t_window *window);
void			free_tab(void **tab);
void			free_rays(t_point **tab, int len);
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
void			free_window(t_window *window);
void			free_image(t_image *image);
int				check_map(t_game *game);
int				check_player_pos(t_game *game);
void			creat_images(t_window *window);
int				deal_key(int key, t_game *game);
int				release_key(int key, t_game *game);
void			render(t_game *game);
void			cube(t_window *window, t_point point, int size, int color);
void			draw_lines(t_window *window, t_point a, t_point b, int color);
void			update_player(t_game *game);
int				is_wall_at(t_game *game, t_point pos);
float			normalize_angle(float angle);
float			distance(t_point a, t_point b);
t_point			**cast_all_rays(t_game *game);
void			ft_print_list(t_list *list);

#endif
