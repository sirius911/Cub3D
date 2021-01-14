/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 10:11:57 by clorin            #+#    #+#             */
/*   Updated: 2021/01/14 10:12:27 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		free_list(void *data)
{
	free(data);
	data = NULL;
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

int				free_map_setup(t_list *list, int result)
{
	ft_lstclear(&list, &free_list);
	free(list);
	return (result);
}
