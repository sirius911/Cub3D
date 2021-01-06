/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:42:50 by clorin            #+#    #+#             */
/*   Updated: 2020/12/24 11:42:53 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		init_player(t_player *player)
{
	player->coord.x = -1;
	player->coord.y = -1;
	player->radius = 2;
	player->turn_dir = 0;
	player->walk_dir = 0;
	player->rot_angle = 0;
	player->move_speed = 10.0;
	player->rot_speed = 4 * (M_PI / 180);
}

static int			valid_pos_player(t_game *game, int x, int y, char dir)
{
	if (game->player.coord.x == -1 && game->player.coord.y == -1)
	{
		game->player.coord.x = (x * game->window.tile_size) + (game->window.tile_size / 2);
		game->player.coord.y = (y * game->window.tile_size) + (game->window.tile_size / 2);
		if(dir == 'E')
			game->player.rot_angle = 0;
		else if(dir == 'S')
			game->player.rot_angle = M_PI / 2;
		else if(dir == 'W')
			game->player.rot_angle = M_PI;
		else
			game->player.rot_angle = 3 * M_PI / 2;
		return (TRUE);
	}
	else
	{
		ft_putstr_fd("Error\nDuplicate player position\n", 2);
		return (FALSE);
	}
}

int			check_player_pos(t_game *game)
{
	unsigned int	x;
	unsigned int	y;
	int				ret;

	y = 0;
	ret = FALSE;
	while (y < game->map.num_rows)
	{
		x = 0;
		while (x < game->map.num_cols)
		{
			if (ft_strchr("NSEW", game->map.tab[y][x]))
			{
				game->map.tab[y][x] = '0';
				ret = valid_pos_player(game, x, y, game->map.tab[y][x]);
			}
			x++;
		}
		y++;
	}
	if (game->player.coord.x == -1)
		ft_putstr_fd("Error\nNo player position\n", 2);
	return (ret);
}

void		update_player(t_game *game)
{
	float			move_step;
	t_point			new_pos;

	game->player.rot_angle += game->player.turn_dir * game->player.rot_speed;
	move_step = game->player.walk_dir * game->player.move_speed;
	new_pos.x = game->player.coord.x + cos(game->player.rot_angle) * move_step;
	new_pos.y = game->player.coord.y + sin(game->player.rot_angle) * move_step;
	if (!is_wall_at(game, new_pos))
	{
		game->player.coord = new_pos;
	}
}