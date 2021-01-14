/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 10:30:42 by clorin            #+#    #+#             */
/*   Updated: 2021/01/14 10:31:48 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int			nb_sprites(t_map *map)
{
	unsigned int	i;
	unsigned int	j;
	int				count;

	i = 0;
	count = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			if (map->tab[i][j] == '2')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static void			load_sprites(t_game *game)
{
	unsigned int	i;
	unsigned int	j;
	int				nb;

	i = 0;
	nb = 0;
	while (i < game->map.num_rows)
	{
		j = 0;
		while (j < game->map.num_cols)
		{
			if (game->map.tab[i][j] == '2' && nb < game->nb_sprite)
			{
				game->tab_sprite[nb].x = j;
				game->tab_sprite[nb].y = i;
				nb++;
			}
			j++;
		}
		i++;
	}
}

void				free_sprite(t_game *game)
{
	free(game->tab_sprite);
	game->tab_sprite = NULL;
}

int					check_sprites(t_game *game)
{
	game->nb_sprite = nb_sprites(&game->map);
	printf("nb sprite = %d\n", game->nb_sprite);
	if (game->nb_sprite > 0)
	{
		game->tab_sprite = (t_sprite*)malloc(sizeof(t_sprite) * game->nb_sprite);
		if (!game->tab_sprite)
		{
			ft_putstr_fd("Error\nMalloc fail for tab sprite.\n", 2);
			return (FALSE);
		}
	}
	load_sprites(game);
	return (TRUE);
}