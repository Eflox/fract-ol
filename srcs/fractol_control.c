/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chde-mar </var/mail/chde-mar>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 01:47:05 by chde-mar          #+#    #+#             */
/*   Updated: 2021/08/06 01:54:36 by chde-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	zoom_in(int x, int y, t_fractol *fractol)
{
	if (fractol->fractal.scale >= SCALE_LIMIT)
	{
		fractol->fractal.scale = SCALE_LIMIT;
		return ;
	}
	if (fractol->mouse.state == 1)
	{
		fractol->mouse.pos_x = x;
		fractol->mouse.pos_y = y;
	}
	fractol->fractal.xr = (x / fractol->fractal.scale + fractol->fractal.xr) - \
			((fractol->fractal.scale * SCALE_PRECISION) / 2);
	fractol->fractal.xr += ((fractol->fractal.scale * SCALE_PRECISION) / 2) - \
		(x / (fractol->fractal.scale * SCALE_PRECISION));
	fractol->fractal.yi = (y / fractol->fractal.scale + fractol->fractal.yi) - \
		((fractol->fractal.scale * SCALE_PRECISION) / 2);
	fractol->fractal.yi += ((fractol->fractal.scale * SCALE_PRECISION) / 2) - \
		(y / (fractol->fractal.scale * SCALE_PRECISION));
	fractol->fractal.scale *= SCALE_PRECISION;
	if (fractol->fractal.type != 3 && fractol->fractal.type != 5)
		fractol->fractal.iteration += 1;
}

static void	zoom_out(t_fractol *fractol)
{
	fractol->fractal.xr = (fractol->mouse.pos_x / fractol->fractal.scale + \
		fractol->fractal.xr) - ((fractol->fractal.scale / SCALE_PRECISION) / 2);
	fractol->fractal.xr += ((fractol->fractal.scale / SCALE_PRECISION) / 2) - \
		(fractol->mouse.pos_x / (fractol->fractal.scale / SCALE_PRECISION));
	fractol->fractal.yi = (fractol->mouse.pos_y / fractol->fractal.scale + \
		fractol->fractal.yi) - ((fractol->fractal.scale / SCALE_PRECISION) / 2);
	fractol->fractal.yi += ((fractol->fractal.scale / SCALE_PRECISION) / 2) - \
		(fractol->mouse.pos_y / (fractol->fractal.scale / SCALE_PRECISION));
	fractol->fractal.scale /= SCALE_PRECISION;
	if (fractol->fractal.type != 3 && fractol->fractal.type != 5)
		fractol->fractal.iteration -= 1;
}

static void	random_colors(t_fractol *fractol)
{
	int	red;
	int	green;
	int	blue;

	red = rand() % (0x4F + 0x01);
	green = rand() % (0x4F + 0x01);
	blue = rand() % (0x4F + 0x01);
	fractol->color.red = red;
	fractol->color.green = green;
	fractol->color.blue = blue;
}

int	fractol_mouse(int mousecode, int x, int y, t_fractol *fractol)
{
	if (x > 0 && y > 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		if (mousecode == MOUSE_UP_SCRLL)
			zoom_in(x, y, fractol);
		else if (mousecode == MOUSE_DOWN_SCRLL)
			zoom_out(fractol);
		else if (mousecode == MOUSE_LEFT_CLK)
		{
			if (fractol->mouse.state == 1)
				fractol->mouse.state = 0;
			else
				fractol->mouse.state = 1;
		}
		fractol_update(fractol);
	}
	return (0);
}

int	fractol_keys(int keycode, t_fractol *fractol)
{
	if (keycode == KEY_ESCAPE)
		exit(0);
	else if (keycode == KEY_ANSI_W || keycode == KEY_UPARROW)
		fractol->fractal.yi -= 1 / fractol->fractal.scale;
	else if (keycode == KEY_ANSI_A || keycode == KEY_LEFTARROW)
		fractol->fractal.xr -= 1 / fractol->fractal.scale;
	else if (keycode == KEY_ANSI_S || keycode == KEY_DOWNARROW)
		fractol->fractal.yi += 1 / fractol->fractal.scale;
	else if (keycode == KEY_ANSI_D || keycode == KEY_RIGHTARROW)
		fractol->fractal.xr += 1 / fractol->fractal.scale;
	else if (keycode == KEY_ANSI_EQUAL)
		zoom_in((WIN_WIDTH / 2), (WIN_HEIGHT / 2), fractol);
	else if (keycode == KEY_ANSI_MINUS)
		zoom_out(fractol);
	else if (keycode == KEY_ANSI_R)
		fractol_init(fractol);
	else if (keycode == KEY_SPACE)
		random_colors(fractol);
	else if (keycode == KEY_ANSI_J)
		fractol->fractal.iteration += 1;
	else if (keycode == KEY_ANSI_K)
		fractol->fractal.iteration -= 1;
	fractol_update(fractol);
	return (0);
}
