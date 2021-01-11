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
	int			img_width;
	int			img_height;
	void		*img;

	printf("Init texture ...\n");

game->texture.data = (int *)malloc(sizeof(int) * 64 * 64);
	if (game->texture.data)
	{
		printf("creation texture a l'addr = %p;\n", game->texture.data);
		x = 0;
		while(x < 64)
		{
			y = 0;
			while(y < 64)
			{
				game->texture.data[(64 * y) + x] = (unsigned int)(x % 8 && y % 8) ? BLUE : BLACK;
				y++;
			}
			x++;
		}
	}

	img = mlx_xpm_file_to_image(game->win.mlx_ptr,
	file, &img_width, &img_height);
	if (img)
	{
		printf("chargement texture a l'addr = %p;\n", game->texture.addr);
		
		mlx_get_data_addr(img, &game->texture.bits_per_pixel,
		&game->texture.line_length, &game->texture.endian);
		game->texture.addr = img;
		game->texture.width = img_width;
		game->texture.height = img_height;
		printf("taille = (%d, %d)\n", img_width, img_height);
		printf("bits_per_pixel = %d\n", game->texture.bits_per_pixel);
		printf("line_length = %d\n", game->texture.line_length);
		printf("endian = %d\n", game->texture.endian);
	}
	else
		ft_putstr("Error\nBad texture file\n");
	printf("sizoef(int) = %lu", sizeof(int*));
	
}

void		free_texture(t_win *win, t_texture *texture)
{
	//free(texture->file);
	free(texture->data);
	mlx_destroy_image(win->mlx_ptr, texture->addr);
	texture->addr = NULL;
}
