/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:23:33 by clorin            #+#    #+#             */
/*   Updated: 2020/12/24 15:23:35 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int		valid_color(int color)
{
	return (color >= 0 && color <= 255);
}

static int		is_texture(char **tab_line)
{
	if (ft_strequ(*tab_line, "NO") || ft_strequ(*tab_line, "SO")
		|| ft_strequ(*tab_line, "WE") || ft_strequ(*tab_line, "EA")
		|| ft_strequ(*tab_line, "S"))
		return (TRUE);
	else
		return (FALSE);
}

int				parse_color(char *str)
{
	char		**rgb;
	int			color_tab[3];
	int			color;
	int			i;

	i = 0;
	if (!str || str[0] == '\0')
		return (-1);
	rgb = ft_split(str, ',');
	while (i < 3)
	{
		if (rgb[i] && is_number(rgb[i]) && valid_color(ft_atoi(rgb[i])))
			color_tab[i] = ft_atoi(rgb[i]);
		else
		{
			ft_putstr_fd("Error\nInvalid floor/ceiling line\n", 2);
			return (-1);
		}
		i++;
	}
	color = create_trgb(0x0, color_tab[0], color_tab[1], color_tab[2]);
	free_tab(rgb);
	free(rgb);
	return (color);
}
static int		record_list_map(t_game *game, t_list **list, char *line)
{
	game->in_map = TRUE;
	if (line[0] != '\0')
	{
		ft_lstadd_back(list, ft_lstnew(ft_strdup(line)));
		return (TRUE);
	}
	else
	{
		ft_putstr_fd("Error\nEmpty line in map.\n", 2);
		return (FALSE);
	}
}

int				parse_line(char *line, t_game *game, t_list **list)
{
	char		**tab_line;
	int			ret;

	ret = TRUE;
	tab_line = ft_split(line, ' ');
	if (*tab_line && *tab_line[0] == 'R')
		ret = setup_resol(game, tab_line);
	else if (*tab_line && is_texture(tab_line))
		ret = parse_texture(game, tab_line);
	else if (*tab_line && (ft_strequ(*tab_line, "F") || ft_strequ(*tab_line, "C")))
		ret = setup_color(game, tab_line);
	else if (*tab_line && *tab_line[0] == '1')
		ret = record_list_map(game, list, line);
	else if (!*tab_line && game->in_map)
	{
		ft_putstr_fd("Error\nEmpty line in map.\n", 2);
		return (FALSE);
	}
	if (*tab_line)
	{
		free_tab(tab_line);
		free(tab_line);
	}
	return (ret);
}
