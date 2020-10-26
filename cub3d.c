#include "include/cub3d.h"

int	main(int ac, char **argv)
{
	t_mlx	mlx;

	if (ac == 2)
	{
		if (ft_init(&mlx) < 0)
			return (-1);
		if (parsing_map(&mlx, argv[1]) < 0)
			return (-1);
		mlx.win = mlx_new_window(mlx.mlx_ptr, mlx.win_width, mlx.win_height, "Cub3D");
		mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, mlx.win_width, mlx.win_height);
		mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l,
		&mlx.img.endian);
		ft_raycasting(&mlx, &mlx.vec, &mlx.player);
		mlx_hook(mlx.win, 2, 1L<<0, key_press, &mlx);
		mlx_hook(mlx.win, 3, 1L<<1, key_release, &mlx);
		mlx_hook(mlx.win, 17, 1L << 17, exit_game, &mlx);
		mlx_loop_hook(mlx.mlx_ptr, ft_keyboard_manager, &mlx);
		mlx_loop(mlx.mlx_ptr);
	}
	else if (ac == 3 && ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) == 0)
		screenshot(&mlx, argv[1]);
	else 
		return (error("Bad arguments\n", -1));
}