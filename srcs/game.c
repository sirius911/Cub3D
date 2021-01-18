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
	init_win(&game->win);
	init_map(&game->map);
	init_player(&game->player);
	init_texture(game);
	game->tab_sprite = NULL;
	game->save = save;
	game->is_minimap = FALSE;
	game->nb_sprite = 0;
	game->in_map = FALSE;
}

static int	check_data_game(t_game *game)
{
	if (!game->tex[NORTH].file)
		return (msg_err(TEXT_MISSING,"North"));
	if (!game->tex[SOUTH].file)
		return (msg_err(TEXT_MISSING,"South"));
	if (!game->tex[EAST].file)
		return (msg_err(TEXT_MISSING,"East"));
	if (!game->tex[WEST].file)
		return (msg_err(TEXT_MISSING,"West"));
	if (!game->tex[SPRITE].file)
		return (msg_err(TEXT_MISSING,"Sprite"));
	if (game->win.f_color == -1)
		return (msg_err(COLOR_MISSING,"Floor"));
	if (game->win.c_color == -1)
		return (msg_err(COLOR_MISSING,"Ceil"));
	if (!game->in_map)
		return (msg_err("No map !",""));
	return (TRUE);
}

int			valid_game(t_game *game, t_list *list, int ret)
{
	if (!ret)
	{
		ft_lstclear(&list, &free_list);
		return (FALSE);
	}
	ret = map_setup(game, list) && check_map(game);
	ft_lstclear(&list, &free_list);
	if (!ret)
		return (FALSE);
	if (game->win.width == 0 || game->win.height == 0)
		return (msg_err(NO_RESOLUTION,""));
	if (check_data_game(game))
	{
		return (load_textures(game));
	}
	return (FALSE);
}

void		run_game(t_game *game)
{
	printf("screen size : width = %d\theight = %d\n", game->win.width, game->win.height);
	if (game->save)
		printf("TODO : save\n");
	else
	{
		game->win.win_ptr = mlx_new_window(game->win.mlx_ptr,
		game->win.width, game->win.height, game->map.name);
		creat_images(&game->win);
		printf("nb sprites = %d\n", game->nb_sprite);
		mlx_hook(game->win.win_ptr, 33, 1L << 17, &game_close, game);
		mlx_hook(game->win.win_ptr, 2, 1L << 0, &deal_key, game);
		mlx_hook(game->win.win_ptr, 3, 1L << 1, &release_key, game);
		render(game);
		mlx_loop(game->win.mlx_ptr);
	}
}

int			game_close(t_game *game)
{
	free_sprite(game);
	free_texture(&game->win, game->tex);
	free_map(&game->map);
	free_win(&game->win);
	return (TRUE);
}
