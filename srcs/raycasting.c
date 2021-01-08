/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:55:30 by clorin            #+#    #+#             */
/*   Updated: 2021/01/05 11:55:33 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				is_ray_facing_down(float angle)
{
	return (angle > 0 && angle < M_PI);
}

int				is_ray_facing_up(float angle)
{
	return (!is_ray_facing_down(angle));
}

int				is_ray_facing_right(float angle)
{
	return (angle < 0.5 * M_PI || angle > 1.5 * M_PI);
}

int				is_ray_facing_left(float angle)
{
	return (!is_ray_facing_right(angle));
}

t_point			inter_verti(float ray_angle, t_game *game)
{
	t_point			intercept;
	t_point			player;
	unsigned int	tile_size;

	player = game->player.coord;
	tile_size = game->window.tile_size;
	intercept.x = floor(player.x / tile_size) * tile_size;
	if (is_ray_facing_right(ray_angle))
		intercept.x += tile_size;
	intercept.y = player.y + (intercept.x - player.x) * tan(ray_angle);
	return (intercept);
}

t_point			inter_horiz(float ray_angle, t_game *game)
{
	t_point			intercept;
	t_point			player;
	unsigned int	tile_size;

	player = game->player.coord;
	tile_size = game->window.tile_size;
	intercept.y = floor(player.y / tile_size) * tile_size;
	if (is_ray_facing_down(ray_angle))
		intercept.y += tile_size;
	intercept.x = player.x + (intercept.y - player.y) / tan(ray_angle);
	return (intercept);
}

t_point			step_horz(float ray_angle, t_window window)
{
	t_point			step;

	step.y = window.tile_size;
	if (is_ray_facing_up(ray_angle))
		step.y *= -1;
	step.x = window.tile_size / tan(ray_angle);
	if (is_ray_facing_left(ray_angle) && step.x > 0)
		step.x *= -1;
	if (is_ray_facing_right(ray_angle) && step.x < 0)
		step.x *= -1;
	return (step);
}

t_point			step_vert(float ray_angle, t_window window)
{
	t_point			step;

	step.x = window.tile_size;
	if (is_ray_facing_left(ray_angle))
		step.x *= -1;
	step.y = window.tile_size * tan(ray_angle);
	if (is_ray_facing_up(ray_angle) && step.y > 0)
		step.y *= -1;
	if (is_ray_facing_down(ray_angle) && step.y < 0)
		step.y *= -1;
	return (step);
}

t_point			horz_wall_hit(float ray_angle, t_game *game)
{
	t_point		intercept;
	t_point		step;
	t_point		next_touch;
	t_point		to_check;
	t_point		no_point;

	no_point.x = -1;
	no_point.y = -1;
	intercept = inter_horiz(ray_angle, game);
	step = step_horz(ray_angle, game->window);
	next_touch = intercept;
	while (next_touch.x >= 0 && next_touch.x <= game->window.screen_width
		&& next_touch.y >= 0 && next_touch.y <= game->window.screen_height)
	{
		to_check = next_touch;
		if (is_ray_facing_up(ray_angle))
			to_check.y -= 1;
		if (is_wall_at(game, to_check))
			return (next_touch);
		next_touch.x += step.x;
		next_touch.y += step.y;
	}
	return (no_point);
}

t_point			vert_wall_hit(float ray_angle, t_game *game)
{
	t_point		intercept;
	t_point		step;
	t_point		next_touch;
	t_point		to_check;
	t_point		no_point;

	no_point.x = -1;
	no_point.y = -1;
	intercept = inter_verti(ray_angle, game);
	step = step_vert(ray_angle, game->window);
	next_touch = intercept;
	while (next_touch.x >= 0 && next_touch.x <= game->window.screen_width
		&& next_touch.y >= 0 && next_touch.y <= game->window.screen_height)
	{
		to_check = next_touch;
		if (is_ray_facing_left(ray_angle))
			to_check.x -= 1;
		if (is_wall_at(game, to_check))
			return (next_touch);
		next_touch.x += step.x;
		next_touch.y += step.y;
	}
	return (no_point);
}

void			fill_ray(t_ray *ray, float dist, t_point wall, float angle)
{
	ray->dist = dist;
	ray->wall_hit = wall;
	ray->ray_angle = angle;
}

void			wall(t_game *game, t_ray *ray, t_point touch, int hz)
{
	if (type_wall(game, touch) == '1')
	{
		if(!hz)
		{
			if (is_ray_facing_left(ray->ray_angle))
				ray->wall_content = EAST;
			else
				ray->wall_content = WEST;
		}
		else
		{
			if (is_ray_facing_up(ray->ray_angle))
				ray->wall_content = NORTH;
			else
				ray->wall_content = SOUTH;
		}
	}
	else
		ray->wall_content = SPRITE;	
}

void			typ_ray(t_game *game, t_ray *ray, int hz)
{
	t_point		touch;

	touch = ray->wall_hit;
	if (!hz && is_ray_facing_left(ray->ray_angle))
		touch.x -= 1;
	if (hz && is_ray_facing_up(ray->ray_angle))
		touch.y -= 1;
	wall(game, ray, touch, hz);
}

t_ray			wall_hit(float ray_angle, t_game *game)
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
		typ_ray(game, &ray, FALSE);
	}
	else
	{
		fill_ray(&ray, horz_hit_distance, horz_coord_wall, ray_angle);
		typ_ray(game, &ray, TRUE);
	}
	return (ray);
}

t_ray			**cast_all_rays(t_game *game)
{
	float		ray_angle;
	int			i;
	t_ray		*ray;
	t_ray		**tab_rays;


	tab_rays = (t_ray**)malloc(sizeof(t_ray) * game->window.num_rays);
	if(!tab_rays)
	{
		ft_putstr_fd("Error\nMalloc() fail\n", 2);
		game_close(game);
	}
	ray_angle = game->player.rot_angle - (FOV_ANGLE / 2);
	i = 0;
	// game->window.num_rays = 1;
	while (i < game->window.num_rays)
	{
		ray = (t_ray*)malloc(sizeof(t_ray));
		*ray = wall_hit(ray_angle, game);
		tab_rays[i] = ray;
		ray_angle += FOV_ANGLE / game->window.num_rays;
		i++;
	}
	return (tab_rays);
}