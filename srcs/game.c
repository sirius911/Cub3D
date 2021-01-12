/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 13:39:25 by clorin            #+#    #+#             */
/*   Updated: 2020/12/30 13:39:32 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		game_close(t_game *game)
{
	free_texture(&game->win, &game->tex[0]);
	free_texture(&game->win, &game->tex[1]);
	free_texture(&game->win, &game->tex[2]);
	free_texture(&game->win, &game->tex[3]);
	free_map(&game->map);
	free_win(&game->win);
}
