/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 13:45:14 by clorin            #+#    #+#             */
/*   Updated: 2021/01/12 16:37:36 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		contine(t_game *game)
{
	printf("screen size : width = %d\theight = %d\n", game->win.width, game->win.height);
	printf("position x =%f\ty=%f rot = %f\n", game->player.coord.x, game->player.coord.y, game->player.rot_angle);
	printf("TILE_SIZE = %d\n", game->win.t_size);
	mlx_hook(game->win.win_ptr, 2, 1L << 0, deal_key, game);
	mlx_hook(game->win.win_ptr, 3, 1L << 1, release_key, game);
	render(game);
	mlx_loop(game->win.mlx_ptr);
}

static int		load_file(t_game *game, char *file_name)
{
	int			fd;
	char		*line;
	int			ret;
	t_list		*list;
	int			nb_oct;

	ret = TRUE;
	list = NULL;
	nb_oct = 1;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nCouldn't open file (FD)\n", 2);
		return (FALSE);
	}
	while (ret && nb_oct > 0)
	{
		nb_oct = get_next_line(fd, &line);
		ret = ret && parse_line(line, game, &list);
		free(line);
	}
	close(fd);
	ret = ret && map_setup(game, list);
	return (ret && check_map(game));
}

static void		init(char *file_name, int save)
{
	t_game		game;

	init_win(&game.win);
	init_player(&game.player);
	init_map(&game.map, file_name);
	game.save = save;
	game.is_map = FALSE;
	if (load_file(&game, file_name))
		contine(&game);
	else
		game_close(&game);
}

static int		is_valid_file(char *file_name)
{
	int		i;

	i = 0;
	while (file_name[i] != '\0')
		i++;
	i -= 4;
	if (i > 0)
		return (ft_strequ(&file_name[i], ".cub"));
	else
		return (FALSE);
}

int				main(int argc, char **argv)
{
	if (argc == 3 && is_valid_file(argv[1]) && ft_strequ(argv[2], "--save"))
	{
		init(argv[1], TRUE);
	}
	else if (argc == 2 && is_valid_file(argv[1]))
	{
		init(argv[1], FALSE);
	}
	else
	{
		ft_putstr_fd("Error\nInvalid arguments\n", 2);
	}
	return (0);
}
