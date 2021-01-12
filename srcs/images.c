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

void		creat_images(t_win *win)
{
	win->image.img = mlx_new_image(win->mlx_ptr, win->width, win->height);
	win->image.addr = mlx_get_data_addr(win->image.img,
	&win->image.bits_per_pixel, &win->image.line_length, &win->image.endian);
}

void		free_image(t_win *win)
{
	mlx_destroy_image(win->mlx_ptr, win->image.img);
	win->image.img = NULL;
	win->image.addr = NULL;
}
