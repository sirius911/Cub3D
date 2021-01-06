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
	// a.x = (game->player.coord.x * SIZE_MINI_MAP) - 3;
	// a.y = (game->player.coord.y * SIZE_MINI_MAP) - 3;
	cube(&game->window, a, 6, RED);
	add_val_point(&a, 3.0);
	// a.x += 3;
	// a.y += 3;
	b.x = a.x + cos(game->player.rot_angle) * 10;
	b.y = a.y + sin(game->player.rot_angle) * 10;
	draw_lines(&game->window, a, b, BLACK);
}

static void		render_ray(t_game *game, t_point **rays)
{
	t_point		wall_point;
	t_point		player;
	int			i;

	i = 0;
	cpy_point(&player, &game->player.coord);
	fact_vect(&player, SIZE_MINI_MAP);
	while (i < game->window.num_rays)
	{
		// ft_print(rays[i]);
		wall_point = *rays[i];
		fact_vect(&wall_point, SIZE_MINI_MAP);
		draw_lines(&game->window, player, wall_point, MAGENTA);
		i++;
	}
}

void		render(t_game *game)
{
	t_point			**rays;
	mlx_destroy_image (game->window.mlx_ptr, game->window.image.img);
	creat_images(&game->window);
	render_map(game);
	render_player(game);
	rays = cast_all_rays(game);
	render_ray(game, rays);
	free_rays(rays, game->window.num_rays);
	mlx_put_image_to_window(game->window.mlx_ptr, game->window.win_ptr, game->window.image.img, 0, 0);
}
