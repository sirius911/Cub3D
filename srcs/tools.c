/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:00:07 by clorin            #+#    #+#             */
/*   Updated: 2020/12/24 15:00:08 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			free_tab(char **tab)
{
	if (tab)
	{
		while (*tab)
		{
			free(*tab);
			tab++;
		}
		tab = NULL;
	}
}

void			free_rays(t_ray **tab, int len)
{
	int		i;

	i = 0;
	if (tab)
	{
		while (i < len)
		{
			free(tab[i]);
			i++;
		}
		tab = NULL;
	}
}

int				is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

void			free_list(void *data)
{
	free(data);
	data = NULL;
}

float			normalize_angle(float angle)
{
	while (angle >= 2 * M_PI)
		 	angle -= (2 * M_PI);
	while (angle < 0)
			angle += 2 * M_PI;
	return (angle);
}

float			distance(t_point a, t_point b)
{
	if (a.x >= 0 && b.x >= 0)
		return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
	else
		return (FLT_MAX);
}
