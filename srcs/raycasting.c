/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:55:30 by clorin            #+#    #+#             */
/*   Updated: 2021/01/05 11:55:33 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		fill_ray(t_ray *ray, float dist, t_point wall, float angle)
{
	ray->dist = dist;
	ray->wall_hit = wall;
	ray->angle = angle;
}

static void		wall(t_game *game, t_ray *ray, t_point touch)
{
	if (type_wall(game, touch) == '1')
	{
		if (ray->hit_vert)
		{
			if (is_ray_facing_left(ray->angle))
				ray->id = EAST;
			else
				ray->id = WEST;
		}
		else
		{
			if (is_ray_facing_up(ray->angle))
				ray->id = NORTH;
			else
				ray->id = SOUTH;
		}
	}
	else
		ray->id = SPRITE;
}

static void		typ_ray(t_game *game, t_ray *ray, int vert)
{
	t_point		touch;

	touch = ray->wall_hit;
	ray->hit_vert = vert;
	if (vert && is_ray_facing_left(ray->angle))
		touch.x -= 1;
	if (!vert && is_ray_facing_up(ray->angle))
		touch.y -= 1;
	wall(game, ray, touch);
}

static t_ray	wall_hit(float ray_angle, t_game *game)
{
	float		vert_hit_distance;
	float		horz_hit_distance;
	t_point		horz_coord_wall;
	t_point		vert_coord_wall;
	t_ray		ray;

	ray_angle = normalize_angle(ray_angle);
	horz_coord_wall = horz_wall_hit(ray_angle, game);
	vert_coord_wall = vert_wall_hit(ray_angle, game);
	horz_hit_distance = distance(game->player.coord, horz_coord_wall);
	vert_hit_distance = distance(game->player.coord, vert_coord_wall);
	if (vert_hit_distance < horz_hit_distance)
	{
		fill_ray(&ray, vert_hit_distance, vert_coord_wall, ray_angle);
		typ_ray(game, &ray, TRUE);
	}
	else
	{
		fill_ray(&ray, horz_hit_distance, horz_coord_wall, ray_angle);
		typ_ray(game, &ray, FALSE);
	}
	return (ray);
}

t_ray			**cast_all_rays(t_game *game)
{
	float		ray_angle;
	int			i;
	t_ray		*ray;
	t_ray		**tab_rays;

	tab_rays = (t_ray**)malloc(sizeof(t_ray) * game->win.num_rays);
	if (!tab_rays)
	{
		ft_putstr_fd("Error\nMalloc() fail\n", 2);
		game_close(game);
	}
	ray_angle = game->player.rot_angle - (FOV_ANGLE / 2);
	i = 0;
	while (i < game->win.num_rays)
	{
		ray = (t_ray*)malloc(sizeof(t_ray));
		*ray = wall_hit(ray_angle, game);
		tab_rays[i] = ray;
		ray_angle += FOV_ANGLE / game->win.num_rays;
		i++;
	}
	return (tab_rays);
}
