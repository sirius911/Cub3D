/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:40:40 by clorin            #+#    #+#             */
/*   Updated: 2020/12/24 11:41:08 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		init_win(t_win *win)
{
	printf("init win ...");
	win->mlx_ptr = NULL;
	win->win_ptr = NULL;
	win->width = 0;
	win->height = 0;
	win->c_color = 0;
	win->f_color = 0;
	win->t_size = 0;
	//win->image->img = NULL;
	printf("ok\n");
}

void		free_win(t_win *win)
{
	//printf("mlx_ptr = %p\twin_ptr = %p\n", win->mlx_ptr, win->win_ptr);
	if (win->mlx_ptr && win->win_ptr)
	{
		if (win->image.img)
			free_image(win);
		//ft_putstr("mlx_destroy_win...");
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		// ft_putstr("ok\n");
	}
	//ft_putstr("free mlx_ptr...");
	free(win->mlx_ptr);
	win->mlx_ptr = NULL;
	//ft_putstr("ok\n");
	//ft_putstr("free win_ptr...");
	//free(win->win_ptr);
	win->win_ptr = NULL;
	//ft_putstr("ok\n");
}
