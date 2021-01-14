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

int			init_texture(t_game *game, char *file, int nb)
{
	int				fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nCouldn't open file texture :(", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(")\n", 2);
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
	printf("%s -> %s\n", tab[0], tab[1]);
	if (ft_strequ(*tab, "NO"))
		return (init_texture(game, tab[1], NORTH));
	else if (ft_strequ(*tab, "SO"))
		return (init_texture(game, tab[1], SOUTH));
	else if (ft_strequ(*tab, "WE"))
		return (init_texture(game, tab[1], WEST));
	else if (ft_strequ(*tab, "EA"))
		return (init_texture(game, tab[1], EAST));
	else if (ft_strequ(*tab, "S"))
		return (init_texture(game, tab[1], SPRITE));
	return (FALSE);
}

void		free_texture(t_win *win, t_texture texture[5])
{
	int				i;

	i = 0;
	while (i < 5)
		mlx_destroy_image(win->mlx_ptr, texture[i++].tex_ptr);
}
