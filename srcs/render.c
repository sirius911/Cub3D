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

static void			show_line(t_game *game, int x, t_ray ray, float wall_height)
{
	int				i;
	int				off_x;
	int				off_y;
	char			*dst;

	i = 0;
	while (i < ray.top_pixel)
		ft_mlx_pixel_put(&game->win, x, i++, game->win.c_color);
	if (ray.hit_vert)
		off_x = (int)(fmod(ray.wall_hit.y, 1.0) * game->tex[ray.id].width);
	else
		off_x = (int)(fmod(ray.wall_hit.x, 1.0) * game->tex[ray.id].width);
	while (i < ray.bot_pixel)
	{
		off_y = (i + (wall_height / 2.0) - (game->win.height / 2.0)) *
		(game->tex[ray.id].height / wall_height);
		dst = game->tex[ray.id].data + (off_y * game->tex[ray.id].line_length
		+ off_x * (game->tex[ray.id].bits_per_pixel) / 8);
		ft_mlx_pixel_put(&game->win, x, i++, *(unsigned int*)dst);
	}
	while (i < game->win.height)
		ft_mlx_pixel_put(&game->win, x, i++, game->win.f_color);
}

void				gen_3d(t_game *game, t_ray *tab_rays)
{
	int				i;
	float			perp_dist;
	float			wall_height;
	int				top_pixel;
	int				bot_pixel;

	i = 0;
	while (i < game->win.num_rays)
	{
		perp_dist = tab_rays[i].dist * cos(tab_rays[i].angle -
			game->player.rot_angle);
		wall_height = game->dist_proj_plane / perp_dist;
		top_pixel = (game->win.height / 2.0) - ((int)wall_height / 2);
		if (top_pixel < 0)
			top_pixel = 0;
		bot_pixel = (game->win.height / 2) + ((int)wall_height / 2);
		if (bot_pixel > game->win.height)
			bot_pixel = game->win.height;
		tab_rays[i].top_pixel = top_pixel;
		tab_rays[i].bot_pixel = bot_pixel;
		show_line(game, i, tab_rays[i], wall_height);
		i++;
	}
}

int					render(t_game *game)
{
	//t_ray			**tab_rays;

	//game->tab_rays = cast_all_rays(game);
	cast_all_rays(game);
	gen_3d(game, game->tab_rays);
	if (game->is_minimap)
	{
		render_map(game);
		render_ray_map(game, game->tab_rays);
		render_player(game);
	}
	scan_sprite(game);
	//free_rays(game);
	mlx_put_image_to_window(game->win.mlx_ptr, game->win.win_ptr,
	game->win.image.img, 0, 0);
	return (TRUE);
}
