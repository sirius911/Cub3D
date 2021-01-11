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

void		init_texture(t_game *game, char *file)
{
	int			x;
	int			y;
	(void)file;
	// int			img_width;
	// int			img_height;
	// void		*img;

	printf("mlx_ptr = %p\n", game->win.mlx_ptr);
	ft_putstr("Init texture ...");
	// printf("mlx_ptr = %p\n", game->win.mlx_ptr);
	// img = mlx_xpm_file_to_image(game->win.mlx_ptr,
	// file, &img_width, &img_height);
	// if (img)
	// {
	// 	ft_putstr("chargement texture ok;\n");
	// }
	// else
	// 	ft_putstr("Error\nBad texture file\n");
	game->texture.data = (int *)malloc(sizeof(int) * 64 * 64);
	if (game->texture.data)
	{
		x = 0;
		while(x < 64)
		{
			y = 0;
			while(y < 64)
			{
				game->texture.data[(64 * y) + x] = (x % 8 && y % 8) ? BLUE : BLACK;
				y++;
			}
			x++;
		}
	}
}

void		free_texture(t_texture *texture)
{
	free(texture->file);
	free(texture->data);
}
