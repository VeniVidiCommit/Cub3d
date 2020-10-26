#include "../include/cub3d.h"

int					key_press(int keycode, t_mlx *mlx)
{
	mlx->keyboard[keycode] = 1;
	return (0);
}
int					key_release(int keycode, t_mlx *mlx)
{
	mlx->keyboard[keycode] = 0;
	return (0);
}