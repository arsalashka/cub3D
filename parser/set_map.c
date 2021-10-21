/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <maearly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 18:38:25 by maearly           #+#    #+#             */
/*   Updated: 2021/05/01 16:15:13 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int 	set_resolution(t_head *head, char **str)
{
	int	x;
	int	y;

	if (!*str[1] && !*str[2])
		return (0);
	if (head->screen.x != 0 || head->screen.y != 0)
		return (0);
	x = ft_atoi(str[1]);
	y = ft_atoi(str[2]);
	if (x < 1 || y < 1)
		return (0);
	head->screen.x = x;
	head->screen.y = y;
	check_resolution(head);
	free_splited_line(str);
	return (1);
}

int 	set_texture(t_head *head, int index, char **str)
{
	t_tex	*tex;
	char	*path;

	path = str[1];
	index = index - 2;
	tex = calloc(1, sizeof(t_tex));
	if (tex == NULL || head->tex[index] || !path)
	{
		if (tex)
			free(tex);
		return (0);
	}
	tex->path = path;
	tex->tex = mlx_xpm_file_to_image(head->win.mlx, path, &tex->width,
			&tex->height);
	if (tex->tex != NULL)
		tex->ptr = mlx_get_data_addr(tex->tex, &tex->bpp, &tex->sl, &tex->en);
	else
	{
		free(tex);
		return (0);
	}
	head->tex[index] = tex;
	free_splited_line(str);
	return (1);
}

void	check_floor_ceiling(t_head *head, int index, char **str)
{
	if (index == F && head->skyline.f_color != -1)
	{
		free_splited_line(str);
		ft_error(head, "Error\nMap error!\n");
	}
	if (index == C && head->skyline.c_color != -1)
	{
		free_splited_line(str);
		ft_error(head, "Error\nMap error!\n");
	}
}

int	set_floor_ceiling(t_head *head, int index, char **str_color)
{
	char	**tmp;
	int		i;
	int		clr[3];

	check_floor_ceiling(head, index, str_color);
	tmp = ft_split(str_color[1], ',');
	free_splited_line(str_color);
	i = 0;
	while (tmp[i])
		i++;
	if (i != 3)
		return (0);
	i = -1;
	while (++i < 3)
		clr[i] = ft_atoi(tmp[i]);
	free_splited_line(tmp);
	i = -1;
	while (++i < 3)
		if (clr[i] < 0 || clr[i] > 255)
			return (0);
	if (index == F)
		head->skyline.f_color = create_rgb(clr[0], clr[1], clr[2]);
	else if (index == C)
		head->skyline.c_color = create_rgb(clr[0], clr[1], clr[2]);
	return (1);
}

int 	set_map(t_head *head)
{
	char	**map;
	int		i;
	t_list	tmp;

	i = 0;
	map = malloc(sizeof(char *) * (head->map_buf.i + 1));
	if (!map)
		return (0);
	tmp = head->map_buf;
	while (head->map_buf.first)
	{
		map[i] = head->map_buf.first->line;
		head->map_buf.first = head->map_buf.first->next;
		i++;
	}
	map[i] = NULL;
	head->map = map;
	ft_free_list(&tmp);
	if (!(check_map(head, head->map_buf.i)))
		return (0);
	if (!set_sprites_pos(head))
		return (0);
	return (1);
}
