/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:33:53 by clorin            #+#    #+#             */
/*   Updated: 2021/01/12 13:33:58 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int		color_minimap(char wall)
{
	if (wall == '0')
		return (WHITE);
	if (wall == '1')
		return (GRAY);
	if (wall == ' ')
		return (-1);
	else
		return (RED);
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
			color = color_minimap(game->map.tab[y][x]);
			if (color != -1)
			{
				point.x = x * SIZE_MINI_MAP;
				point.y = y * SIZE_MINI_MAP;
				cube(&game->win, point,
				10, color);
			}
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
