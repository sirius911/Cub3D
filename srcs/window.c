/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:40:40 by clorin            #+#    #+#             */
/*   Updated: 2020/12/24 11:41:08 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		init_window(t_window *window)
{
	window->mlx_ptr = NULL;
	window->win_ptr = NULL;
	window->screen_width = 0;
	window->screen_height = 0;
	window->sky_color = 0;
	window->floor_color = 0;
	window->tile_size = 0;
}

void		free_window(t_window *window)
{
	mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	ft_putstr("mlx_destroy_window...ok\n");
	free(window->mlx_ptr);
	ft_putstr("free mlx_ptr...ok\n");
	window->win_ptr = NULL;
	free_image(&window->image);
}
