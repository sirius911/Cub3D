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

// static int		mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey)
// {
// 	(void)mlx_ptr;
// 	*sizex = 1920;
// 	*sizey = 1080;
// 	return (0);
// }

static int		valid_mlx(t_game *game)
{
	int		resol_x;
	int		resol_y;

	if (!game->save)
	{
		game->win.mlx_ptr = mlx_init();
		mlx_get_screen_size(game->win.mlx_ptr, &resol_x, &resol_y);
		printf("screen_size = (%d,%d)\n", resol_x, resol_y);
		if (game->win.width > resol_x)
			game->win.width = resol_x;
		if (game->win.height > resol_y)
			game->win.height = resol_y;
		game->win.win_ptr = mlx_new_window(game->win.mlx_ptr,
		game->win.width, game->win.height, game->map.name);
		creat_images(&game->win);
		//game->win.image = creat_images(&game->win.mlx_ptr, game->win.width, game->win.height);
		game->win.num_rays = game->win.width / WALL_STRIP_WIDTH;
		return (TRUE);
	}
	return (FALSE);
}

int				setup_resol(t_game *game, char **tab)
{
	int		resol_x;
	int		resol_y;

	if (tab[1] && tab[2] && is_number(tab[1]) && is_number(tab[2]))
	{
		resol_x = ft_atoi(tab[1]);
		resol_y = ft_atoi(tab[2]);
		if (resol_x > 0 && resol_y > 0)
		{
			if (game->win.width == 0
				&& game->win.height == 0)
			{
				game->win.width = resol_x;
				game->win.height = resol_y;
				return (valid_mlx(game));
			}
			else
				ft_putstr_fd("Error\nResolution specified twice\n", 2);
		}
		else
			ft_putstr_fd("Error\nBad resolution\n", 2);
	}
	else
		ft_putstr_fd("Error\nCouldn't parse resolution\n", 2);
	return (FALSE);
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
