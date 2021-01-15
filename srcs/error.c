/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:50:10 by clorin            #+#    #+#             */
/*   Updated: 2021/01/15 10:50:35 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int					msg_err(char *msg, char *line)
{
	printf("Error\n%s", msg);
	if (*line)
	{
		printf(" (%s)\n", line);
	}
	else
		printf("\n");
/*	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);*/
	return (FALSE);
}