/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chde-mar </var/mail/chde-mar>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 02:46:17 by chde-mar          #+#    #+#             */
/*   Updated: 2021/08/06 02:46:19 by chde-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	fractol_usage(char *argv0)
{
	ft_putstr("Usage: ");
	ft_putstr(ft_program_name(argv0));
	ft_putstr(" [ mandelbrot | julia ]\n");
	return (0);
}

static int	fractol_selection(char *argument, t_fractol *fractol)
{
	fractol->fractal.type = 0;
	if (ft_strequ(ft_str_to_lowcase(argument), "mandelbrot"))
		fractol->fractal.type = 1;
	else if (ft_strequ(ft_str_to_lowcase(argument), "julia"))
		fractol->fractal.type = 2;
	else
	{
		ft_putstr(argument);
		ft_putendl(" not an available fractal.");
	}
	return (fractol->fractal.type);
}

void	fractol_init(t_fractol *fractol)
{
	fractol->fractal.xr = -2.60;
	fractol->fractal.yi = -1.20;
	fractol->fractal.scale = 300.00;
	fractol->fractal.iteration = 42;
	fractol->color.red = 0x42;
	fractol->color.green = 0x32;
	fractol->color.blue = 0x22;
	fractol->mouse.pos_x = WIN_WIDTH / 2;
	fractol->mouse.pos_y = WIN_HEIGHT / 2;
	if (fractol->fractal.type == 2 || fractol->fractal.type == 4 \
			|| fractol->fractal.type == 3)
	{
		fractol->fractal.xr = -2.10;
		fractol->mouse.state = 1;
		if (fractol->fractal.type == 2 || fractol->fractal.type == 4)
			fractol->fractal.iteration = 100;
		if (fractol->fractal.type == 3)
			fractol->fractal.iteration = 10;
	}
	if (fractol->fractal.type == 5)
	{
		fractol->fractal.xr = -2.20;
		fractol->fractal.yi = -1.60;
		fractol->fractal.iteration = 14;
	}
}

void	fractol_update(t_fractol *fractol)
{
	if (fractol->fractal.iteration <= 0)
		fractol->fractal.iteration = 0;
	fractol_pthread(fractol);
	mlx_string_put(fractol->mlx.init, fractol->mlx.win, 10, 5, 0xFFFFFF, \
		ft_strjoin("Iterations = ", ft_itoa(fractol->fractal.iteration)));
	mlx_string_put(fractol->mlx.init, fractol->mlx.win, 200, 5, 0xFFFFFF, \
		ft_strjoin("Zoom = ", ft_itoa((int)fractol->fractal.scale)));
	mlx_string_put(fractol->mlx.init, fractol->mlx.win, 10, WIN_HEIGHT - 30, \
		0xFFFFFF, "KEYS = [ W|A|S|D|-|=|j|k|SPACE|MOUSEWHEEL-+]");
}

int	main(int argc, char *argv[])
{
	t_fractol	*fractol;

	if (argc != 2)
		return (fractol_usage(argv[0]));
	fractol = (t_fractol *)malloc(sizeof(t_fractol));
	if (fractol == NULL)
		ft_puterror("Memory Allocation Failed.", 1);
	if (!fractol_selection(argv[1], fractol))
		ft_puterror("Usage: fractol [ mandelbrot | julia ]", 2);
	fractol->mlx.init = mlx_init();
	fractol->mlx.win = mlx_new_window(fractol->mlx.init, WIN_WIDTH, \
		WIN_HEIGHT, "CHDE-MAR Fractol");
	fractol->mlx.img = mlx_new_image(fractol->mlx.init, WIN_WIDTH, \
		WIN_HEIGHT);
	fractol->image.data = mlx_get_data_addr(fractol->mlx.img, \
		&fractol->image.bpp, &fractol->image.size, &fractol->image.endian);
	fractol_init(fractol);
	fractol_update(fractol);
	mlx_hook(fractol->mlx.win, 2, 3, fractol_keys, fractol);
	mlx_hook(fractol->mlx.win, 4, 3, fractol_mouse, fractol);
	mlx_hook(fractol->mlx.win, 6, 3, fractol_manipulate, fractol);
	mlx_loop(fractol->mlx.init);
	return (0);
}
