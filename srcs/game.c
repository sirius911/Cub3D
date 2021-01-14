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

void		init_game(t_game *game, int save)
{
	game->save = save;
	game->is_minimap = FALSE;
	game->nb_sprite = 0;
}

void		game_close(t_game *game)
{
	free_texture(&game->win, game->tex);
	free_map(&game->map);
	free_win(&game->win);
}
