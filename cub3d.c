#include "cub3d.h"

int	main(int ac, char **argv)
{
	t_mlx	mlx;
	if (ac == 2)
	{
		ft_init_vec(&mlx);
		mlx.mlx_ptr = mlx_init();
		mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
		mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
		mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l,
		&mlx.img.endian);
		if (ft_load_text(&mlx.text) < 0)
			return (-1);
		if (ft_read_map(&mlx, argv[1]) < 0)
			return (-1);
		ft_raycasting(&mlx, &mlx.vec, &mlx.player);
		mlx_hook(mlx.win, 2, 1L<<0, key_press, &mlx);
		mlx_hook(mlx.win,3, 1L<<1, key_release, &mlx);
		mlx_loop_hook(mlx.mlx_ptr, ft_rotate, &mlx);
		mlx_loop(mlx.mlx_ptr);
	}
	
	return (0);

}