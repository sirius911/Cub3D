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

void		free_image(t_image *image)
{
	if (image->img)
	{
		free(image->img);
		image->img = NULL;
		ft_putstr("free image->img ...ok\n");		
	}
	if (image->addr)
	{
		free(image->addr);
		image->addr = NULL;
		ft_putstr("free image->adr ...ok\n");
	}
}

void		creat_images(t_window *window)
{
	window->image.img = mlx_new_image(window->mlx_ptr, window->screen_width, window->screen_height);
	window->image.addr = mlx_get_data_addr(window->image.img, &window->image.bits_per_pixel, &window->image.line_length, &window->image.endian);
}
