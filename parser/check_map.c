/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:38:16 by maearly           #+#    #+#             */
/*   Updated: 2021/04/24 15:33:41 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void 	flood_fill_one(t_head *head, int y_max, int y, int x)
{
	char	**map;

	map = head->map;
	if (y < 0 || y >= y_max || x < 0 || x >= ((int)ft_strlen(map[y]) - 1))
		return ;
	if (map[y][x] != '0')
		return ;
	if (map[y][x] == '$')
		return ;
	map[y][x] = '$';
	flood_fill_one(head, y_max, y + 1, x);
	flood_fill_one(head, y_max, y - 1, x);
	flood_fill_one(head, y_max, y, x + 1);
	flood_fill_one(head, y_max, y, x - 1);
}

int 	check_first_last_strings(t_head *head)
{
	char	**map;
	int		x;
	int		y;

	map = head->map;
	x = -1;
	while (map[0][++x])
	{
		if (map[0][x] != ' ' && map[0][x] != '1')
			return (0);
	}
	x = -1;
	y = head->map_buf.i - 1;
	while (map[y][++x])
	{
		if (map[y][x] != ' ' && map[y][x] != '1')
			return (0);
	}
	return (1);
}

int 	check_left_right_chars(char **map)
{
	int	left_char;
	int	right_char;
	int	i;

	if (!map)
		return (0);
	i = -1;
	while (map[++i])
	{
		left_char = 0;
		while (map[i][left_char] == ' ')
			left_char++;
		right_char = (int)ft_strlen(map[i]) - 1;
		while (map[i][right_char] == ' ')
			right_char--;
		if ((right_char - left_char) < 2 || map[i][left_char] != '1' ||
				map[i][right_char] != '1')
			return (0);
	}
	return (1);
}

int 	check_map_symbols(char **map, char c)
{
	int	i;
	int	k;

	if (!map)
		return (0);
	i = -1;
	while (map[++i])
	{
		k = 0;
		while (map[i][k])
		{
			if (map[i][k] == c || map[i][k] == ' ' || map[i][k] == '1' ||
				map[i][k] == '2')
				k++;
			else
			{
				i = -1;
				while (map[++i])
					printf("%s\n", map[i]);
				return (0);
			}
		}
	}
	return (1);
}

int 	check_map(t_head *head, int y_max)
{
	if (head->plr.pos_x == -1 || !head->map)
		return (0);
	if (!(check_map_symbols(head->map, '0')))
		return (0);
	flood_fill_one(head, y_max - 1, (int)head->plr.pos_y, (int)head->plr.pos_x);
	if (!check_first_last_strings(head))
		return (0);
	if (!check_left_right_chars(head->map)
		|| !check_map_symbols(head->map, '$'))
		return (0);
	if (!check_strlen(head) || !check_arround_symbols(head))
		return (0);
	if (!correct_plr_pos_y(head))
		return (0);
	return (1);
}
