/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 23:20:19 by maearly           #+#    #+#             */
/*   Updated: 2021/05/01 15:59:40 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int 	check_config(t_head *head)
{
	int	i;

	i = -1;
	if (head->screen.x < 1 || head->screen.y < 1)
		return (0);
	while (++i < 5)
	{
		if (head->tex[i] == NULL)
			return (0);
	}
	if (head->skyline.c_color == -1 || head->skyline.f_color == -1)
		return (0);
	return (1);
}

void	check_resolution(t_head *head)
{
	int	width;
	int	height;

	mlx_get_screen_size(&width, &height);
	if (width < head->screen.x)
		head->screen.x = width;
	if (height < head->screen.y)
		head->screen.y = height;
}

int	check_args(t_head *head, int argc, char **argv)
{
	if (argc == 2)
		return (1);
	if (argc > 3)
		return (0);
	if (argc == 3 && !ft_strcmp(argv[2], "--save"))
	{
		head->bmp = 1;
		return (1);
	}
	return (0);
}
