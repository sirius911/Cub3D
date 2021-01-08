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
	printf("init window ...");
	window->mlx_ptr = NULL;
	window->win_ptr = NULL;
	window->screen_width = 0;
	window->screen_height = 0;
	window->sky_color = 0;
	window->floor_color = 0;
	window->tile_size = 0;
	window->image.img = NULL;
	printf("ok\n");
}

void		free_window(t_window *window)
{
	//printf("mlx_ptr = %p\twin_ptr = %p\n", window->mlx_ptr, window->win_ptr);
	if (window->mlx_ptr && window->win_ptr)
	{
		if (window->image.img)
			free_image(window);
		//ft_putstr("mlx_destroy_window...");
		mlx_destroy_window(window->mlx_ptr, window->win_ptr);
		// ft_putstr("ok\n");
	}
	//ft_putstr("free mlx_ptr...");
	free(window->mlx_ptr);
	window->mlx_ptr = NULL;
	//ft_putstr("ok\n");
	//ft_putstr("free win_ptr...");
	//free(window->win_ptr);
	window->win_ptr = NULL;
	//ft_putstr("ok\n");
}
