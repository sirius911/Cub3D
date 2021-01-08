/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:41:57 by clorin            #+#    #+#             */
/*   Updated: 2020/12/24 11:42:01 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		init_image(t_image *image)
{
	image->img = NULL;
	image->addr = NULL;
	image->bits_per_pixel = 0;
	image->line_length = 0;
	image->endian = 0;
}

void		creat_images(t_window *window)
{
	window->image.img = mlx_new_image(window->mlx_ptr, window->screen_width, window->screen_height);
	window->image.addr = mlx_get_data_addr(window->image.img, &window->image.bits_per_pixel, &window->image.line_length, &window->image.endian);
}

void		free_image(t_window *window)
{
	// ft_putstr("mlx_destroy_image...");
	mlx_destroy_image(window->mlx_ptr, window->image.img);
	window->image.img = NULL;
	window->image.addr = NULL;
	// ft_putstr("ok\n");
}

void		clear_image(t_window *window)
{
	int		x;
	int		y;

	y = 0;
	while (y < window->screen_height)
	{
		x = 0;
		while (x < window->screen_width)
		{
			ft_mlx_pixel_put(window, x, y, window->floor_color);
			x++;
		}
		y++;
	}
}
