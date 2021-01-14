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

static void			show_line(t_game *game, int x, t_ray ray, int wall_height)
{
	int				i;
	int				off_x;
	int				off_y;
	int				dis_top;
	char			*dst;

	i = 0;
	while (i < ray.top_pixel)
		ft_mlx_pixel_put(&game->win, x, i++, game->win.c_color);
	if (ray.hit_vert)
		off_x = (int)ray.wall_hit.y % game->win.t_size;
	else
		off_x = (int)ray.wall_hit.x % game->win.t_size;
	while (i < ray.bot_pixel)
	{
		dis_top = (i + wall_height / 2 - game->win.height / 2);
		off_y = dis_top * ((float)game->tex[ray.id].width / wall_height);
		dst = game->tex[ray.id].data + (off_y * game->tex[ray.id].line_length
		+ off_x * (game->tex[ray.id].bits_per_pixel) / 8);
		ft_mlx_pixel_put(&game->win, x, i++, *(unsigned int*)dst);
	}
	while (i < game->win.height)
		ft_mlx_pixel_put(&game->win, x, i++, game->win.f_color);
}

void				gen_3d(t_game *game, t_ray **tab_rays)
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

void				render(t_game *game)
{
	t_ray			**tab_rays;

	tab_rays = cast_all_rays(game);
	gen_3d(game, tab_rays);
	if (game->is_minimap)
	{
		render_map(game);
		render_ray_map(game, tab_rays);
		render_player(game);
	}
	free_rays(tab_rays, game->win.num_rays);
	mlx_put_image_to_window(game->win.mlx_ptr, game->win.win_ptr,
	game->win.image.img, 0, 0);
}
