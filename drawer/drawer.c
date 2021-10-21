/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 17:07:05 by maearly           #+#    #+#             */
/*   Updated: 2021/04/29 14:21:04 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int 	new_win_init(t_head *head)
{
	head->win.win = mlx_new_window(head->win.mlx, head->screen.x,
			head->screen.y, "cub3D");
	if (!head->win.mlx || !head->win.win)
		return (0);
	return (1);
}

void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_tex_color(t_tex *tex, double x, double y)
{
	if (x >= 0 && x < tex->width && y >= 0 && y < tex->height)
		return (*(int *)(tex->ptr + (4 * tex->width * (int)y) + (4 * (int)x)));
	return (0x0);
}

void 	draw_map(t_head *head)
{
	t_raycast	cast;
	int			x;
	int			i;
	double		z_buff[2880];

	ft_bzero(z_buff, sizeof(double));
	i = -1;
	while (++i < head->spr_count)
		head->sprites[i].flag = 0;
	x = 0;
	while (x < head->screen.x)
	{
		prep_calc(head, &cast, x);
		step_n_side_dist(head, &cast);
		dda_algorithm(head, &cast);
		perp_dist(head, &cast);
		cast.line_height = (int)(head->screen.y / cast.perp_wall_dist);
		draw_start_end(head, &cast);
		wall_x_calc(head, &cast);
		tex_x(head, &cast);
		draw_ceiling_floor(head, &cast, x);
		draw_line(head, &cast, x, z_buff);
		x++;
	}
	sprite_calc(head, z_buff);
}

int 	hook(t_head *head)
{
	set_position(head);
	mlx_clear_window(head->win.mlx, head->win.win);
	head->win.img = mlx_new_image(head->win.mlx, head->screen.x,
			head->screen.y);
	head->win.addr = mlx_get_data_addr(head->win.img,
			&head->win.bits_per_pixel, &head->win.line_length,
			&head->win.endian);
	draw_map(head);
	mlx_put_image_to_window(head->win.mlx, head->win.win, head->win.img, 0, 0);
	mlx_destroy_image(head->win.mlx, head->win.img);
	return (1);
}
