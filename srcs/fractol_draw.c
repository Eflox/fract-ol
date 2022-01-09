/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chde-mar </var/mail/chde-mar>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 02:45:40 by chde-mar          #+#    #+#             */
/*   Updated: 2021/08/06 02:45:42 by chde-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	put_pixel(t_fractol *fractol, int depth)
{
	int	pos;

	pos = (fractol->fractal.height + (fractol->fractal.width * WIN_WIDTH)) * 4;
	if (fractol->fractal.height < WIN_WIDTH \
			&& fractol->fractal.width < WIN_HEIGHT \
				&& depth == fractol->fractal.iteration)
	{
		fractol->image.data[pos] = 0x00;
		fractol->image.data[pos + 1] = 0x00;
		fractol->image.data[pos + 2] = 0x00;
	}
	else if (fractol->fractal.height < WIN_WIDTH \
				&& fractol->fractal.width < WIN_HEIGHT)
	{
		fractol->image.data[pos] = fractol->color.red + (depth * 2.42);
		fractol->image.data[pos + 1] = fractol->color.green + (depth * 2.42);
		fractol->image.data[pos + 2] = fractol->color.blue + (depth * 2.42);
	}
}

static void	*draw_fractal(void *tab)
{
	t_fractol	*fractol;
	int			depth;
	double		tmp_width;

	fractol = (t_fractol *)tab;
	tmp_width = fractol->fractal.width;
	while (fractol->fractal.height < WIN_WIDTH)
	{
		fractol->fractal.width = tmp_width;
		while (fractol->fractal.width < fractol->fractal.limit)
		{
			if (fractol->fractal.type == 1)
				depth = mandelbrot(fractol);
			if (fractol->fractal.type == 2)
				depth = julia(fractol);
			put_pixel(fractol, depth);
			fractol->fractal.width += 1;
		}
		fractol->fractal.height += 1;
	}
	return (tab);
}

void	fractol_pthread(t_fractol *fractol)
{
	t_fractol	tab[THREADS];
	pthread_t	t[THREADS];
	int			i;

	i = 0;
	while (i < THREADS)
	{
		ft_memcpy((void *)&tab[i], (void *)fractol, sizeof(t_fractol));
		tab[i].fractal.width = ((double)(1.00 / THREADS) *WIN_WIDTH) * i;
		tab[i].fractal.limit = ((double)(1.00 / THREADS) *WIN_WIDTH) * (i + 1);
		i += 1;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_create(&t[i], NULL, draw_fractal, &tab[i]);
		i += 1;
	}
	while (i--)
		pthread_join(t[i], NULL);
	mlx_put_image_to_window(fractol->mlx.init, fractol->mlx.win, \
								fractol->mlx.img, 0, 0);
}

int	fractol_manipulate(int x, int y, t_fractol *fractol)
{
	if (fractol->mouse.state == 1 && (x > 0 && y > 0) \
			&& (x < WIN_WIDTH && y < WIN_HEIGHT))
	{
		fractol->mouse.pos_x = x;
		fractol->mouse.pos_y = y;
		fractol_update(fractol);
	}
	return (0);
}
