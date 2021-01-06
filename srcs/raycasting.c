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

t_point			wall_hit(float ray_angle, t_game *game)
{
	float		vert_hit_distance;
	float		horz_hit_distance;
	t_point		horz_coord_wall;
	t_point		vert_coord_wall;

	ray_angle = normalize_angle(ray_angle);
	horz_coord_wall = horz_wall_hit(ray_angle, game);
	vert_coord_wall = vert_wall_hit(ray_angle, game);
	if (horz_coord_wall.x >= 0)
		horz_hit_distance = distance(game->player.coord, horz_coord_wall);
	else
		horz_hit_distance = FLT_MAX;
	if (vert_coord_wall.x >= 0)
		vert_hit_distance = distance(game->player.coord, vert_coord_wall);
	else
		vert_hit_distance = FLT_MAX;
	if (vert_hit_distance < horz_hit_distance)
		return (vert_coord_wall);
	else
		return (horz_coord_wall);
}

void			ft_print(void *x)
{
	t_point		*p;
	p = (t_point *)x;
	printf("(%f, %f)\n", p->x, p->y);
}

t_point			**cast_all_rays(t_game *game)
{
	float		ray_angle;
	int			i;
	t_point		*point;
	t_point		**rays;

	rays = (t_point**)malloc(sizeof(t_point) * game->window.num_rays);
	if(!rays)
	{
		ft_putstr_fd("Error\nMalloc() fail\n", 2);
		game_close(game);
	}
	ray_angle = game->player.rot_angle - (FOV_ANGLE / 2);
	i = 0;
	while (i < game->window.num_rays)
	{
		point = (t_point*)malloc(sizeof(t_point));
		*point = wall_hit(ray_angle, game);
		rays[i] = point;
		ray_angle += FOV_ANGLE / game->window.num_rays;
		i++;
	}
	return (rays);
}