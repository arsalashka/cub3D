/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <maearly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 15:05:25 by maearly           #+#    #+#             */
/*   Updated: 2021/04/29 23:10:59 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_splited_line(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int 	check_map_path(char *path)
{
	path = path + ft_strlen(path) - 4;
	if (path[0] == '.' && path[1] == 'c' && path[2] == 'u' && path[3] == 'b')
		return (1);
	return (0);
}

int 	get_index(char const *str)
{
	if (str == NULL)
		return (0);
	if (*str == 'R')
		return (1);
	else if (*str == 'N' && str[1] == 'O')
		return (2);
	else if (*str == 'S' && str[1] == 'O')
		return (3);
	else if (*str == 'W' && str[1] == 'E')
		return (4);
	else if (*str == 'E' && str[1] == 'A')
		return (5);
	else if (*str == 'S')
		return (6);
	else if (*str == 'F' && str[1] == 'T')
		return (7);
	else if (*str == 'C' && str[1] == 'T')
		return (8);
	else if (*str == 'F')
		return (9);
	else if (*str == 'C')
		return (10);
	else if (*str == '1')
		return (11);
	return (0);
}

int	parse_string(t_head *head, char *line)
{
	char		**splited_line;
	int			index;

	if (!*line && !check_config(head))
		return (1);
	splited_line = ft_split(line, ' ');
	index = get_index(splited_line[0]);
	if (index == R)
		return (set_resolution(head, splited_line));
	else if (index >= NO && index <= CT)
		return (set_texture(head, index, splited_line));
	else if (index == F || index == C)
		return (set_floor_ceiling(head, index, splited_line));
	else if (check_config(head))
	{
		if (head->map_buf.i != 0 && line[0] == '\0')
			return (0);
		if (!(list_manager(&head->map_buf, line)))
			return (0);
		free_splited_line(splited_line);
		return (1);
	}
	return (0);
}

int 	read_map(t_head *head, char const *map_path)
{
	int		fd;
	char	*line;

	line = NULL;
	if (!check_map_path((char *)map_path))
		return (0);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((get_next_line(fd, &line) > 0))
	{
		if (!(parse_string(head, line)))
			return (0);
		free(line);
	}
	if (!(parse_string(head, line)))
		return (0);
	free(line);
	close(fd);
	if (!find_plr(head))
		return (0);
	if (!set_map(head))
		return (0);
	return (1);
}
