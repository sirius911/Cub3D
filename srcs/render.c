/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 14:00:47 by clorin            #+#    #+#             */
/*   Updated: 2021/01/04 14:00:50 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			fact_vect(t_point *point, float fact)
{
	point->x *= fact;
	point->y *= fact;
}

void			cpy_point(t_point *dst, t_point *src)
{
	dst->x = src->x;
	dst->y = src->y;
}

void			add_val_point(t_point *point, float val)
{
	point->x += val;
	point->y += val;
}

static void		render_map(t_game *game)
{
	unsigned int		x;
	unsigned int		y;
	int					color;
	t_point				point;

	y = 0;
	while (y < game->map.num_rows)
	{
		x = 0;
		while (x < game->map.num_cols){
			if (game->map.tab[y][x] == '0')
				color = WHITE;
			else if (game->map.tab[y][x] == '1')
				color = GRAY;
			else
				color = NONE;
			point.x = x * game->window.tile_size * SIZE_MINI_MAP;
			point.y = y * game->window.tile_size * SIZE_MINI_MAP;
			cube(&game->window, point,
				game->window.tile_size * SIZE_MINI_MAP, color);
			x++;
		}
		y++;
	}

}

static void		render_player(t_game *game)
{
	t_point			a;
	t_point			b;

	cpy_point(&a, &game->player.coord);
	fact_vect(&a, SIZE_MINI_MAP);
	add_val_point(&a, -3.0);
	cube(&game->window, a, 6, RED);
	add_val_point(&a, 3.0);
	b.x = a.x + cos(game->player.rot_angle) * 10;
	b.y = a.y + sin(game->player.rot_angle) * 10;
	draw_lines(&game->window, a, b, BLACK);
}

static void		render_ray_map(t_game *game, t_ray **rays)
{
	t_point		wall_point;
	t_point		player;
	t_ray		ray;
	int			i;

	i = 0;
	cpy_point(&player, &game->player.coord);
	fact_vect(&player, SIZE_MINI_MAP);
	while (i < game->window.num_rays)
	{
		// ft_print(rays[i]);
		ray = *rays[i];
		wall_point = ray.wall_hit;
		//printf("ray[%d] (%f,%f) = %x\n", i, ray.wall_hit.x, ray.wall_hit.y, ray.wall_content);
		fact_vect(&wall_point, SIZE_MINI_MAP);
		draw_lines(&game->window, player, wall_point, find_color(ray.wall_content));
		i++;
	}
}

static void		render_ray(t_game *game, t_ray **tab_rays)
{
	int			i;
	float		correct_wall_distance;
	float		wall_strip_height;
	float		distance_projection_plane;
	t_point		point;
	t_point		width_height;

	i = 0;
	distance_projection_plane = (game->window.screen_width / 2) / tan(FOV_ANGLE / 2);
	while (i < game->window.num_rays)
	{
		correct_wall_distance = tab_rays[i]->dist * cos(tab_rays[i]->ray_angle - game->player.rot_angle);
		wall_strip_height = (game->window.tile_size / correct_wall_distance) * distance_projection_plane;
		point.x = i * WALL_STRIP_WIDTH;
		point.y = 0;
		//rect(&game->window, point, WALL_STRIP_WIDTH,
		//(game->window.screen_height - wall_strip_height) / 2, game->window.sky_color);
		point.y = (game->window.screen_height - wall_strip_height) / 2;
		width_height.x = WALL_STRIP_WIDTH;
		width_height.y = wall_strip_height;
		rect(&game->window, point, width_height, 
		find_color(tab_rays[i]->wall_content));
		i++;
	}
}

void		render(t_game *game)
{
	t_ray			**tab_rays;

	clear_image(&game->window);
	tab_rays = cast_all_rays(game);
	render_ray(game, tab_rays);
	render_map(game);
	render_ray_map(game, tab_rays);
	render_player(game);
	free_rays(tab_rays, game->window.num_rays);
	mlx_put_image_to_window(game->window.mlx_ptr, game->window.win_ptr, game->window.image.img, 0, 0);
}
