/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 10:00:11 by clorin            #+#    #+#             */
/*   Updated: 2020/12/31 10:00:51 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int		check_border_lr(t_map *map)
{
	unsigned int		i;

	i = 0;
	while (i < map->num_rows)
	{
		if ((map->tab[i][0] != ' ' && map->tab[i][0] != '1') ||
			(map->tab[i][map->num_cols - 1] != ' ' &&
			map->tab[i][map->num_cols - 1] != '1'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int		check_border_td(t_map *map)
{
	unsigned int		j;

	j = 0;
	while (j < map->num_cols)
	{
		if ((map->tab[0][j] != ' ' && map->tab[0][j] != '1') ||
			(map->tab[map->num_rows - 1][j] != ' ' &&
			map->tab[map->num_rows - 1][j] != '1'))
			return (FALSE);
		j++;
	}
	return (TRUE);
}

static int		check_space(t_map *map)
{
	unsigned int		i;
	unsigned int		j;

	i = 1;
	while (i < map->num_rows - 1)
	{
		j = 1;
		while (j < map->num_cols - 1)
		{
			if (map->tab[i][j] == '0')
			{
				if (map->tab[i - 1][j] == ' ' || map->tab[i + 1][j] == ' '
					|| map->tab[i][j - 1] == ' ' || map->tab[i][j + 1] == ' ')
					return (FALSE);
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

int				check_map(t_game *game)
{
	printf("check map...\n");
	if (!check_player_pos(game))
		return (FALSE);
	if (!check_border_lr(&game->map) || !check_border_td(&game->map) ||
		!check_space(&game->map))
	{
		ft_putstr_fd("Error\nMap isn't surrounded by walls\n", 2);
		return (FALSE);
	}
	return (check_sprites(game));
}
