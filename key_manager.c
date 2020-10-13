#include "cub3d.h"

int		key_press(int keycode, t_mlx *mlx)
{
	mlx->keyboard[keycode] = 1;
	return (0);
}
int		key_release(int keycode, t_mlx *mlx)
{
	mlx->keyboard[keycode] = 0;
	return (0);
}
int			ft_rotate(t_mlx *mlx)
{
	if (mlx->keyboard[KEY_W])
	{
		if (mlx->map.world_map[(int)(mlx->player.pos_x + mlx->player.dir_x * mlx->player.move_speed)][(int)mlx->player.pos_y] == 0)
			mlx->player.pos_x += mlx->player.dir_x * mlx->player.move_speed;
		if (mlx->map.world_map[(int)(mlx->player.pos_x)][(int)(mlx->player.pos_y + mlx->player.dir_y * mlx->player.move_speed)] == 0)
			mlx->player.pos_y += mlx->player.dir_y * mlx->player.move_speed;
	}
    if (mlx->keyboard[KEY_S])
    {
      if (mlx->map.world_map[(int)(mlx->player.pos_x - mlx->player.dir_x * mlx->player.move_speed)][(int)(mlx->player.pos_y)] == 0) 
	  	mlx->player.pos_x -= mlx->player.dir_x * mlx->player.move_speed;
      if (mlx->map.world_map[(int)(mlx->player.pos_x)][(int)(mlx->player.pos_y - mlx->player.dir_y * mlx->player.move_speed)] == 0) 
	  	mlx->player.pos_y -= mlx->player.dir_y * mlx->player.move_speed;
	}
	if (mlx->keyboard[KEY_A]) 
	{
		if (mlx->map.world_map[(int)(mlx->player.pos_x - mlx->player.plan_x * mlx->player.move_speed)][(int)mlx->player.pos_y] == 0)
			mlx->player.pos_x -= mlx->player.plan_x * mlx->player.move_speed;
		if (mlx->map.world_map[(int)mlx->player.pos_x][(int)(mlx->player.pos_y - mlx->player.plan_y * mlx->player.move_speed)] == 0)
			mlx->player.pos_y -= mlx->player.plan_y * mlx->player.move_speed;
	}
	if (mlx->keyboard[KEY_D])
	{
		if (mlx->map.world_map[(int)(mlx->player.pos_x + mlx->player.plan_x * mlx->player.move_speed)][(int)mlx->player.pos_y] == 0)
			mlx->player.pos_x += mlx->player.plan_x * mlx->player.move_speed;
		if (mlx->map.world_map[(int)mlx->player.pos_x][(int)(mlx->player.pos_y + mlx->player.plan_y * mlx->player.move_speed)] == 0)
			mlx->player.pos_y += mlx->player.plan_y * mlx->player.move_speed;
	}
	if (mlx->keyboard[KEY_RIGHT])
	{
		double old_dir_x;
		double old_plane_x;
		old_dir_x = mlx->player.dir_x;
		old_plane_x = mlx->player.plan_x;
		mlx->player.dir_x = mlx->player.dir_x * cos(-mlx->player.rotate_speed) - mlx->player.dir_y * sin(-mlx->player.rotate_speed);
		mlx->player.dir_y = old_dir_x * sin(-mlx->player.rotate_speed) + mlx->player.dir_y * cos(-mlx->player.rotate_speed);
		mlx->player.plan_x = mlx->player.plan_x * cos(-mlx->player.rotate_speed) - mlx->player.plan_y * sin(-mlx->player.rotate_speed);
		mlx->player.plan_y = old_plane_x * sin(-mlx->player.rotate_speed) + mlx->player.plan_y * cos(-mlx->player.rotate_speed);
	}
	if (mlx->keyboard[KEY_LEFT])
	{
		double old_dir_x;
		double old_plane_x;
		old_dir_x = mlx->player.dir_x;
		old_plane_x = mlx->player.plan_x;
		mlx->player.dir_x = mlx->player.dir_x * cos(mlx->player.rotate_speed) - mlx->player.dir_y * sin(mlx->player.rotate_speed);
		mlx->player.dir_y = old_dir_x * sin(mlx->player.rotate_speed) + mlx->player.dir_y * cos(mlx->player.rotate_speed);
		mlx->player.plan_x = mlx->player.plan_x * cos(mlx->player.rotate_speed) - mlx->player.plan_y * sin(mlx->player.rotate_speed);
		mlx->player.plan_y = old_plane_x * sin(mlx->player.rotate_speed) + mlx->player.plan_y * cos(mlx->player.rotate_speed);
	}
	ft_raycasting(mlx, &mlx->vec, &mlx->player);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
	return (0);
}