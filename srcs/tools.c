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

void			right_trim(char *str)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && ft_isspace(str[i]))
	{
		i--;
	}
	str[i + 1] = '\0';
}
