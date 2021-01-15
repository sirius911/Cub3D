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
		{
			ft_putstr_fd("Error\nmlx_init() fail.\n", 2);
			return (FALSE);
		}
		mlx_get_screen_size(game->win.mlx_ptr, &resol_x, &resol_y);
		printf("screen_size = (%d,%d)\n", resol_x, resol_y);
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
		{
			ft_putstr_fd("Error\nBad color\n", 2);
			return (FALSE);
		}
	}
	else
	{
		ft_putstr_fd("Error\nCouldn't parse color for sky/floor\n", 2);
		return (FALSE);
	}
	if (ft_strequ(tab[0], "F"))
		game->win.f_color = color;
	else
		game->win.c_color = color;
	return (TRUE);
}
