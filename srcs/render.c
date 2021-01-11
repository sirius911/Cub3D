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

void			render_map(t_game *game)
{
	unsigned int	x;
	unsigned int	y;
	int				color;
	t_point			point;

	y = 0;
	while (y < game->map.num_rows)
	{
		x = 0;
		while (x < game->map.num_cols)
		{
			if (game->map.tab[y][x] == '0')
				color = WHITE;
			else if (game->map.tab[y][x] == '1')
				color = GRAY;
			else
				color = NONE;
			point.x = x * game->win.t_size * SIZE_MINI_MAP;
			point.y = y * game->win.t_size * SIZE_MINI_MAP;
			cube(&game->win, point,
				game->win.t_size * SIZE_MINI_MAP, color);
			x++;
		}
		y++;
	}
}

void			render_player(t_game *game)
{
	t_point			a;
	t_point			b;

	cpy_point(&a, &game->player.coord);
	fact_vect(&a, SIZE_MINI_MAP);
	add_val_point(&a, -3.0);
	cube(&game->win, a, 6, RED);
	add_val_point(&a, 3.0);
	b.x = a.x + cos(game->player.rot_angle) * 10;
	b.y = a.y + sin(game->player.rot_angle) * 10;
	draw_lines(&game->win, a, b, BLACK);
}

void			render_ray_map(t_game *game, t_ray **rays)
{
	t_point			wall_point;
	t_point			player;
	t_ray			ray;
	int				i;

	i = 0;
	cpy_point(&player, &game->player.coord);
	fact_vect(&player, SIZE_MINI_MAP);
	while (i < game->win.num_rays)
	{
		ray = *rays[i];
		wall_point = ray.wall_hit;
		fact_vect(&wall_point, SIZE_MINI_MAP);
		draw_lines(&game->win, player, wall_point, RED);
		i++;
	}
}

static void			show_line(t_game *game, int x, t_ray ray, int wall_height)
{
	int				i;
	int				tex_color;
	int				off_x;
	int				off_y;
	int				dis_top;

	i = 0;
	while (i < ray.top_pixel)
		ft_mlx_pixel_put(&game->win, x, i++, game->win.c_color);
	if (ray.id == EAST || ray.id == WEST)
		off_x = (int)ray.wall_hit.y % game->win.t_size;
		//off_x = ((int)ray.wall_hit.y % 1) * 64;
	else
		off_x = (int)ray.wall_hit.x % game->win.t_size;
		//off_x = ((int)ray.wall_hit.x % 1) * 64;
	while (i < ray.bot_pixel)
	{
		dis_top = i + wall_height / 2 - game->win.height / 2;// * (64/wall_height);
		off_y = dis_top * ((float)64 / wall_height); 
		tex_color = game->texture.data[(64 * off_y) + off_x ];;
		ft_mlx_pixel_put(&game->win, x, i++, tex_color);
	}
	while (i < game->win.height)
		ft_mlx_pixel_put(&game->win, x, i++, game->win.f_color);
}

void			gen_3d(t_game *game, t_ray **tab_rays)
{
	int				i;
	float			perp_dist;
	float			wall_height;
	int				top_pixel;
	int				bot_pixel;

	i = 0;
	while (i < game->win.num_rays)
	{
		perp_dist = tab_rays[i]->dist * cos(tab_rays[i]->angle -
			game->player.rot_angle);
		wall_height = (game->win.t_size / perp_dist) * (game->win.width / 2)
		/ tan(FOV_ANGLE / 2);
		top_pixel = (game->win.height / 2) - ((int)wall_height / 2);
		if (top_pixel < 0)
			top_pixel = 0;
		bot_pixel = (game->win.height / 2) + ((int)wall_height / 2);
		if (bot_pixel > game->win.height)
			bot_pixel = game->win.height;
		tab_rays[i]->top_pixel = top_pixel;
		tab_rays[i]->bot_pixel = bot_pixel;
		show_line(game, i, *tab_rays[i], (int)wall_height);
		i++;
	}
}

void			render(t_game *game)
{
	t_ray			**tab_rays;

	tab_rays = cast_all_rays(game);
	gen_3d(game, tab_rays);
	render_map(game);
	render_ray_map(game, tab_rays);
	render_player(game);
	free_rays(tab_rays, game->win.num_rays);
	mlx_put_image_to_window(game->win.mlx_ptr, game->win.win_ptr,
		game->win.image.img, 0, 0);
}
