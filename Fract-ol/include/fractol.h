/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:04:14 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/26 10:27:50 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# ifndef WIDTH
#  define WIDTH 900
# endif
# ifndef HEIGHT
#  define HEIGHT 600
# endif
# ifndef MAX_ITERATIONS
#  define MAX_ITERATIONS 100
# endif

enum
{
	KEY_A = 0,
	KEY_B = 11,
	KEY_C = 8,
	KEY_D = 2,
	KEY_E = 14,
	KEY_F = 3,
	KEY_G = 5,
	KEY_H = 4,
	KEY_I = 34,
	KEY_J = 38,
	KEY_K = 40,
	KEY_L = 37,
	KEY_M = 46,
	KEY_N = 45,
	KEY_O = 31,
	KEY_P = 35,
	KEY_Q = 12,
	KEY_R = 15,
	KEY_S = 1,
	KEY_T = 17,
	KEY_U = 32,
	KEY_V = 9,
	KEY_W = 13,
	KEY_X = 7,
	KEY_Y = 16,
	KEY_Z = 6,
	KEY_ESC = 53,
	KEY_PLUS = 24,
	KEY_MINUS = 27,
	KEY_UP = 126,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
	KEY_LEFT = 123,
	KEY_SPACE = 49,
	KEY_0 = 82,
	KEY_1 = 83,
	KEY_2 = 84,
	KEY_3 = 85,
	KEY_4 = 86,
	KEY_5 = 87,
	KEY_6 = 88,
	KEY_7 = 89,
	KEY_8 = 91,
	KEY_9 = 92,
	KEY_PLUS_PAD = 69,
	KEY_MINUS_PAD = 78
};

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_mlx
{
	void	*init;
	void	*win;
	void	*img;
	char	*addr;
	int		color;
	int		*colors;
	double	zoom;
	int		x;
	int		y;
	int		fractal;
	double	c_re;
	double	c_im;
	int		psyche;
}	t_mlx;

void	ft_set_colors(t_mlx *f, int color);
void	ft_color(t_mlx *f, int n, int x, int y);
void	julia(t_mlx *mlx);
void	mandelbrot(t_mlx *mlx);
int		call_fractal(t_mlx *mlx);
int		init_mlx(t_mlx *mlx);
int		ft_close(t_mlx *mlx);
int		key_pressed(int keycode, t_mlx *mlx);
int		ft_released(int keycode, t_mlx *mlx);
void	print_error(char *str);
void	ft_putstr(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_parsing(char **av, int ac, t_mlx *mlx);
int		mouse_wheel(int keycode, int x, int y, t_mlx *mlx);
void	draw_burning(t_mlx *mlx);
void	display_option(void);
float	ft_atof(char *arr, int *check);
int		init_fractal(char **av, int ac, t_mlx *mlx);
void	display_command(void);

#endif