/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 11:22:52 by clorin            #+#    #+#             */
/*   Updated: 2021/01/10 11:23:41 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		init_texture(t_game *game)
{
	int				i;

	i = 0;
	while (i < 5)
	{
		game->tex[i].tex_ptr = NULL;
		game->tex[i].data = NULL;
		game->tex[i].width = 0;
		game->tex[i].height = 0;
		game->tex[i].bits_per_pixel = 0;
		game->tex[i].line_length = 0;
		game->tex[i].endian = 0;
		i++;
	}
}

int			load_texture(t_game *game, char *file, int nb)
{
	int				fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCouldn't open file texture :(%s)\n", file);
/*		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(")\n", 2);*/
		return (FALSE);
	}
	close(fd);
	game->tex[nb].tex_ptr = mlx_xpm_file_to_image(game->win.mlx_ptr,
	file, &game->tex[nb].width, &game->tex[nb].height);
	if (game->tex[nb].tex_ptr)
	{
		game->tex[nb].data = mlx_get_data_addr(game->tex[nb].tex_ptr,
			&game->tex[nb].bits_per_pixel,
		&game->tex[nb].line_length, &game->tex[nb].endian);
		return (TRUE);
	}
	else
		ft_putstr_fd("Error\nBad texture file\n", 2);
	return (FALSE);
}

int			parse_texture(t_game *game, char **tab)
{
	if (ft_strequ(*tab, "NO"))
		return (load_texture(game, tab[1], NORTH));
	else if (ft_strequ(*tab, "SO"))
		return (load_texture(game, tab[1], SOUTH));
	else if (ft_strequ(*tab, "WE"))
		return (load_texture(game, tab[1], WEST));
	else if (ft_strequ(*tab, "EA"))
		return (load_texture(game, tab[1], EAST));
	else if (ft_strequ(*tab, "S"))
		return (load_texture(game, tab[1], SPRITE));
	return (FALSE);
}

void		free_texture(t_win *win, t_texture texture[5])
{
	int				i;

	i = 0;
	while (i < 5)
	{
		if (win->mlx_ptr && texture[i].tex_ptr)
		{
			mlx_destroy_image(win->mlx_ptr, texture[i].tex_ptr);
			texture[i].tex_ptr = NULL;
			texture[i].data = NULL;
		}
		i++;
	}
}
