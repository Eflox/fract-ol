/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chde-mar </var/mail/chde-mar>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 02:30:24 by chde-mar          #+#    #+#             */
/*   Updated: 2021/08/06 16:55:31 by chde-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <math.h>
# include <time.h>
# include "mlx.h"
# include "libft.h"

# define WIN_WIDTH			(1280)
# define WIN_HEIGHT			(720)
# define THREADS			(8)
# define SCALE_LIMIT		(500000000)
# define SCALE_PRECISION	(1.042)
# define KEY_ANSI_W			(0X0D)
# define KEY_ANSI_A			(0X00)
# define KEY_ANSI_S			(0X01)
# define KEY_ANSI_D			(0X02)
# define KEY_UPARROW		(0X0D)
# define KEY_LEFTARROW		(0X7B)
# define KEY_RIGHTARROW		(0X7C)
# define KEY_DOWNARROW		(0X7D)
# define KEY_ANSI_R			(0X0F)
# define KEY_SPACE			(0X31)
# define KEY_ANSI_J			(0X26)
# define KEY_ANSI_K			(0X28)
# define KEY_ANSI_MINUS		(0X1B)
# define KEY_ANSI_EQUAL		(0X18)
# define KEY_ESCAPE			(0X35)
# define MOUSE_UP_SCRLL		(0x04)
# define MOUSE_DOWN_SCRLL	(0x05)
# define MOUSE_LEFT_CLK		(0x01)

typedef struct s_mlx
{
	void	*init;
	void	*win;
	void	*img;
}				t_mlx;

typedef struct s_image
{
	char	*data;
	int		size;
	int		endian;
	int		bpp;
}				t_image;

typedef struct s_color
{
	int		red;
	int		green;
	int		blue;
}				t_color;

typedef struct s_type
{
	int		type;
	int		depth;
	int		iteration;
	double	width;
	double	height;
	double	scale;
	double	limit;
	double	xr;
	double	yi;
}				t_type;

typedef struct s_mouse
{
	int		state;
	int		pos_x;
	int		pos_y;
}				t_mouse;

typedef struct s_fractol
{
	t_mlx	mlx;
	t_image	image;
	t_color	color;
	t_type	fractal;
	t_mouse	mouse;
}				t_fractol;

void			fractol_init(t_fractol *fractol);
void			fractol_update(t_fractol *fractol);
int				fractol_keys(int keycode, t_fractol *fractol);
int				fractol_mouse(int mousecode, int x, int y, t_fractol *fractol);
void			fractol_pthread(t_fractol *fractol);
int				fractol_manipulate(int x, int y, t_fractol *fractol);
int				mandelbrot(t_fractol *fractol);
int				julia(t_fractol *fractol);

#endif
