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
	game->tab_sprite = NULL;
	game->save = save;
	game->is_minimap = FALSE;
	game->nb_sprite = 0;
	game->in_map = FALSE;
}

void		game_close(t_game *game)
{
	free_sprite(game);
	free_texture(&game->win, game->tex);
	free_map(&game->map);
	free_win(&game->win);
}

int			valid_game(t_game *game, t_list *list, int ret)
{
	if (ret)
		ret &= map_setup(game, list) && check_map(game);
	ft_lstclear(&list, &free_list);
	return (ret);
}