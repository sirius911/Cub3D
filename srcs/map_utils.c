/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:08:25 by clorin            #+#    #+#             */
/*   Updated: 2021/01/05 11:08:27 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				find_color(int wall)
{
	if (wall == NORTH)
		return (MAGENTA);
	if (wall == EAST)
		return (BLUE);
	if (wall == SOUTH)
		return (YELLOW);
	if (wall == WEST)
		return (CYAN);
	if (wall == SPRITE)
		return (GREEN);
	return (NONE);
}

int				is_wall_at(t_game *game, t_point pos)
{
	unsigned int		map_grid_index_x;
	unsigned int		map_grid_index_y;

	if (pos.x < 0 || pos.x > game->win.width ||
		pos.y < 0 || pos.y > game->win.height)
		return (TRUE);
	map_grid_index_x = floor(pos.x / game->win.t_size);
	map_grid_index_y = floor(pos.y / game->win.t_size);
	if (map_grid_index_x >= game->map.num_cols ||
		map_grid_index_y >= game->map.num_rows)
		return (TRUE);
	return (game->map.tab[map_grid_index_y][map_grid_index_x] != '0');
}

char			type_wall(t_game *game, t_point pos)
{
	unsigned int		map_grid_index_x;
	unsigned int		map_grid_index_y;

	map_grid_index_x = floor(pos.x / game->win.t_size);
	map_grid_index_y = floor(pos.y / game->win.t_size);
	return (game->map.tab[map_grid_index_y][map_grid_index_x]);
}
