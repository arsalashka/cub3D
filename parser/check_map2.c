/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:37:07 by maearly           #+#    #+#             */
/*   Updated: 2021/04/29 14:46:38 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_strlen(t_head *head)
{
	int	x;
	int	y;
	int	a;
	int	b;

	if (!head->map)
		return (0);
	y = 0;
	while (head->map[++y] && y < head->map_buf.i - 1)
	{
		x = -1;
		while (head->map[y][++x])
		{
			a = ((int)ft_strlen(head->map[y - 1]) - 1);
			b = ((int)ft_strlen(head->map[y + 1]) - 1);
			if (head->map[y][x] == '$' && (x > a || x > b))
				return (0);
		}
	}
	return (1);
}

int 	check_arround_symbols(t_head *head)
{
	int		x;
	int		y;
	char	**map;

	if (!head->map || head->plr.pos_x == -1)
		return (0);
	map = head->map;
	y = 0;
	while (map[++y] && y < head->map_buf.i - 1)
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '$' || map[y][x] == '2'
				|| (y == head->plr.pos_y && x == head->plr.pos_x))
			{
				if (map[y][x + 1] == ' ' || map[y][x - 1] == ' '
					|| map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
					return (0);
			}
		}
	}
	return (1);
}

int 	correct_plr_pos_y(t_head *head)
{
	if (head->map[(int)head->plr.pos_y - 1][(int)head->plr.pos_x] == '1')
		head->plr.pos_y = head->plr.pos_y + 0.5;
	else if (head->map[(int)head->plr.pos_y + 1][(int)head->plr.pos_x] == '1')
		head->plr.pos_y = head->plr.pos_y + 0.6;
	else
		head->plr.pos_y = head->plr.pos_y + 0.5;
	return (1);
}

int	spr_count_on_fov(t_head *head)
{
	int	i;
	int	k;
	int	spr_count;

	i = -1;
	spr_count = 0;
	while (head->map[++i])
	{
		k = -1;
		while (head->map[i][++k])
			if (head->map[i][k] == '2')
				spr_count++;
	}
	if (spr_count == 0)
		return (0);
	head->sprites = malloc(sizeof(t_sprite) * (spr_count));
	if (!head->sprites)
		return (0);
	return (spr_count);
}

int	set_sprites_pos(t_head *head)
{
	int	i;
	int	k;
	int	spr_count;

	spr_count = spr_count_on_fov(head);
	if (spr_count == 0)
		return (1);
	spr_count = 0;
	i = -1;
	while (head->map[++i])
	{
		k = -1;
		while (head->map[i][++k])
		{
			if (head->map[i][k] == '2')
			{
				head->sprites[spr_count].pos.x = k;
				head->sprites[spr_count].pos.y = i;
				spr_count++;
			}
		}
	}
	head->spr_count = spr_count;
	return (1);
}
