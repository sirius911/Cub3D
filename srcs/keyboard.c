/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:30:17 by clorin            #+#    #+#             */
/*   Updated: 2021/01/04 13:30:21 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	deal_key(int key, t_game *game)
{
	if (key == KEY_ESC)
	{
		game_close(game);
		exit(0);
	}
	else if (key == KEY_RIGHT)
	{
		game->player.turn_dir = 1;
	}
	else if (key == KEY_LEFT)
	{
		game->player.turn_dir = -1;
	}
	else if (key == KEY_UP)
	{
		game->player.walk_dir = 1;
	}
	else if (key == KEY_DOWN)
	{
		game->player.walk_dir = -1;
	}
	else
	{
		ft_putstr("key = ");
		ft_putnbr(key);
		ft_putchar('\n');
	}
	update_player(game);
	render(game);
	// update_player(window);
	// mlx_destroy_image (window->mlx_ptr, window->image.img);
	// init_images(window);
	// minimap(window);
	// cast_all_rays(window);
	// print_player(window);
	// mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->image.img, 0, 0);
	return (0);
}

int	release_key(int key, t_game *game)
{
	if (key == KEY_RIGHT)
	{
		game->player.turn_dir = 0;
	}
	else if (key == KEY_LEFT)
	{
		game->player.turn_dir = 0;
	}
	else if (key == KEY_UP)
	{
		game->player.walk_dir = 0;
	}
	else if (key == KEY_DOWN)
	{
		game->player.walk_dir = 0;
	}
	return (0);
}
