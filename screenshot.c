/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 20:19:49 by maearly           #+#    #+#             */
/*   Updated: 2021/04/30 20:19:51 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	pixel_color(t_win *win, int x, int y)
{
	int		color;
	char	*dst;

	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

static void	a_write(int fd, int c, int s)
{
	write(fd, &c, s);
}

static void	bmp_header(int fd, int x, int y, int bpp)
{
	write(fd, "BM", 2);
	a_write(fd, ((x * y) * 4 + 58), 4);
	write(fd, "\0\0\0\0", 4);
	a_write(fd, 58, 4);
	a_write(fd, 40, 4);
	a_write(fd, x, 4);
	a_write(fd, y, 4);
	a_write(fd, 1, 2);
	a_write(fd, bpp, 2);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 28);
}

int	screenshot(t_head *head, t_win *win)
{
	int	x;
	int	y;
	int	fd;
	int	sx;

	x = (int)head->screen.x;
	y = (int)head->screen.y;
	sx = 0;
	fd = open("screenshot.bmp", O_CREAT | O_RDWR);
	if (fd < 0)
		return (ft_exit(head));
	bmp_header(fd, x, y, win->bits_per_pixel);
	while (y != 0)
	{
		while (sx != x)
		{
			a_write(fd, pixel_color(win, sx, y), 4);
			++sx;
		}
		sx = 0;
		--y;
	}
	close(fd);
	return (1);
}

void	make_screenshot(t_head *head)
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
	if (!screenshot(head, &head->win))
		ft_error(head, "Error\nScreenshot error!\n");
	mlx_destroy_image(head->win.mlx, head->win.img);
	ft_exit(head);
}
