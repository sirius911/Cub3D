/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:16:51 by clorin            #+#    #+#             */
/*   Updated: 2020/12/24 15:16:53 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		valid_resol(t_game *game)
{
	int			resol_x;
	int			resol_y;

	if (!game->save)
	{
		game->win.mlx_ptr = mlx_init();
		if (!game->win.mlx_ptr)
			return (msg_err(FAIL_MLX, ""));
		mlx_get_screen_size(game->win.mlx_ptr, &resol_x, &resol_y);
		if (game->win.width > resol_x)
			game->win.width = resol_x;
		if (game->win.height > resol_y)
			game->win.height = resol_y;
		game->win.num_rays = game->win.width;
	}
	return (TRUE);
}

int				setup_color(t_game *game, char **tab)
{
	int			color;

	if (tab[1])
	{
		color = parse_color(tab[1]);
		if (color == -1)
			return (msg_err(BAD_COLOR, ""));
	}
	else
		return (msg_err(BAD_COLOR, "Couldn't parse color"));
	if (ft_strequ(tab[0], "F"))
		game->win.f_color = color;
	else
		game->win.c_color = color;
	return (TRUE);
}
