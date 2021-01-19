/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 13:06:45 by clorin            #+#    #+#             */
/*   Updated: 2021/01/18 13:07:14 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

static void			sort_sprites(t_sprite *sprites, int nb_sprites)
{
	t_sprite		tmp;
	int				i;
	int				j;

	i = 0;
	while (i < nb_sprites)
	{
		j = i;
		while (j < nb_sprites)
		{
			if (sprites[i].dist < sprites[j].dist)
			{
				tmp = sprites[j];
				sprites[j] = sprites[i];
				sprites[i] = tmp;
				i = 0;
			}
			j++;
		}
		i++;
	}
}

static float		sprite_angle(t_point sprite_pos, t_point player_pos,
		float player_rot_angle)
{
	float			dx;
	float			dy;
	float			angle;

	dx = sprite_pos.x - player_pos.x;
	dy = sprite_pos.y - player_pos.y;
	angle = atan2(dy, dx) - player_rot_angle;
	return (angle);
}

static int			sprite_visible(float angle_sprite)
{
	if (angle_sprite < -M_PI)
		angle_sprite += 2 * M_PI;
	if (angle_sprite >= M_PI)
		angle_sprite -= 2 * M_PI;
	if (angle_sprite < 0)
		angle_sprite = -angle_sprite;
	return (angle_sprite < (FOV_ANGLE / 2));
}

static int			get_tex_color(t_texture tex, int x, int y)
{
	char			*dst;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >  tex.width)
		x = tex.width;
	if (y > tex.height)
		y = tex.height;
	dst = tex.data + (y * tex.line_length + x * tex.bits_per_pixel / 8);
	return (*(unsigned int*)dst);
}

static void			draw_sprite(t_game *game, t_sprite sprite, t_point pos, t_point offset)
{
	int				color;
	int				no_color;

	no_color = get_tex_color(game->tex[SPRITE], 0, 0);
	offset.y = (pos.y + (sprite.height / 2.0) - (game->win.height / 2.0)) * (game->tex[SPRITE].height / sprite.height);
	if (offset.y < 0)
		offset.y = 0;
	color = get_tex_color(game->tex[SPRITE],offset.x, offset.y);
	if (color != no_color)
		ft_mlx_pixel_put(&game->win, sprite.first_x + pos.x, pos.y, color);
}

static void			render_sprite(t_game *game, t_sprite sprite)
{
	t_point			point;
	t_point			offset;
	float			dist_ray;

	point.x = -1;
	while(sprite.first_x + point.x < 0)
		point.x++;
	while(++point.x < sprite.height && sprite.first_x + point.x < game->win.width)
	{
		dist_ray = game->tab_rays[(int)(sprite.first_x + point.x)].dist;
		if (dist_ray > game->tab_sprite[sprite.index].dist)
		{
			offset.x = point.x * game->tex[SPRITE].width / sprite.height;
			point.y = sprite.top_pixel - 1;
			while (++point.y < sprite.bot_pixel)
				draw_sprite(game, sprite, point, offset);
		}
	}
}

static void 		sprite_data(t_game *game, t_sprite *sprite)
{
	int				i;
	int				top;
	int				bot;

	i = -1;
	while (++i < game->nb_sprite)
	{
		if (sprite[i].is_visible)
		{
			sprite[i].index = i;
			sprite[i].height = (game->dist_proj_plane) /
			(cos(sprite[i].angle) * sprite[i].dist);
			top = (game->win.height / 2.0) - (sprite[i].height / 2);
			if (top < 0)
				top = 0;
			bot = (game->win.height / 2.0) + (sprite[i].height / 2);
			if (bot > game->win.height)
				bot = game->win.height;
			sprite[i].top_pixel = top;
			sprite[i].bot_pixel = bot;
			sprite[i].first_x = game->dist_proj_plane * tan(sprite[i].angle)
			+ (game->win.width / 2) - (sprite[i].height / 2);
			render_sprite(game, sprite[i]);
		}
	}
}

int					scan_sprite(t_game *game)
{
	int				nb;

	nb = 0;
	while (nb < game->nb_sprite)
	{
		game->tab_sprite[nb].dist = distance(game->player.coord,
			game->tab_sprite[nb].pos);
		game->tab_sprite[nb].angle = sprite_angle(game->tab_sprite[nb].pos,
			game->player.coord, game->player.rot_angle);
		game->tab_sprite[nb].is_visible = sprite_visible(game->tab_sprite[nb].angle);
		nb++;
	}
	sort_sprites(game->tab_sprite, game->nb_sprite);
	sprite_data(game, game->tab_sprite);
	return (1);
}
