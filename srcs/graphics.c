/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:47:04 by clorin            #+#    #+#             */
/*   Updated: 2020/12/24 15:47:06 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		ft_mlx_pixel_put(t_window *window, int x, int y, int color)
{
	char		*dst;

	if (x >= 0 && x < window->screen_width &&
		y >= 0 && y < window->screen_height)
	{
		dst = window->image.addr + (y * window->image.line_length +
			x * (window->image.bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void		draw_lines(t_window *window, t_point a, t_point b, int color)
{
	t_point		c;
	float		length;
	t_point		add_point;
	float		i;

	c.x = b.x - a.x;
	c.y = b.y - a.y;
	length = sqrt(c.x * c.x + c.y * c.y);
	add_point.x = c.x / length;
	add_point.y = c.y / length;
	c.x = a.x;
	c.y = a.y;
	i = 0.0;
	while (i < length)
	{
		ft_mlx_pixel_put(window, c.x, c.y, color);
		c.x += add_point.x;
		c.y += add_point.y;
		i++;
	}
}

int			create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void		cube(t_window *window, t_point a, int size, int color)
{
	int			i;
	int			j;

	j = 0;
	while (j <= size)
	{
		i = 0;
		while (i <= size)
		{
			ft_mlx_pixel_put(window, a.x + i, a.y + j, color);
			i++;
		}
		j++;
	}
}

void		rect(t_window *window, t_point a, t_point coord, int color)
{
	int			i;
	int			j;

	j = 0;
	while (j < coord.x)
	{
		i = 0;
		while (i < coord.y)
		{
			ft_mlx_pixel_put(window, a.x + j, a.y + i, color);
			i++;
		}
		j++;
	}
}
