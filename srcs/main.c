/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 13:45:14 by clorin            #+#    #+#             */
/*   Updated: 2020/12/23 13:47:56 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void		ft_print_list(t_list *list)
// {
// 	while (list)
// 	{
// 		ft_putendl(list->content);
// 		list = list->next;
// 	}
// }

static void		contine(t_game *game)
{
	ft_putendl("tableaux : ");
	for (unsigned int y = 0; y < game->map.num_rows; y++)
	{
		ft_putstr("<");
		for (unsigned int x = 0; x < game->map.num_cols; x++)
		{
			ft_putchar('.');
			ft_putchar(game->map.tab[y][x]);
			ft_putchar('.');
		}
		ft_putendl(">");
	}
	printf("screen size : width = %d\theight = %d\n", game->window.screen_width, game->window.screen_height);
	printf("position x =%f\ty=%f rot = %f\n", game->player.coord.x, game->player.coord.y, game->player.rot_angle);
	mlx_hook(game->window.win_ptr, 2, 1L<<0, deal_key, game);
	mlx_hook(game->window.win_ptr, 3, 1L<<1, release_key, game);
	render(game);
	mlx_loop(game->window.mlx_ptr);
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
	ret = ret && map_setup(game, list);
	ft_lstclear(&list, &free_list);
	close(fd);
	return (ret && check_map(game));
}

static void		init(char *file_name, int save)
{
	t_game		game;
	t_window	window;
	t_player	player;
	t_map		map;
	t_image		image;

	window.mlx_ptr = NULL;
	window.win_ptr = NULL;
	init_window(&window);
	init_player(&player);
	init_map(&map, file_name);
	init_image(&image);
	window.image = image;
	game.player = player;
	game.map = map;
	game.window = window;
	game.save = save;
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
