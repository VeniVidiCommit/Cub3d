#include "cub3d.h"
#include <stdio.h>

uint32_t	reverse(uint32_t n)
{
	uint32_t	res;

	res = 0;
	res |= n & 0xFF;
	res <<= 8;
	n >>= 8;
	res |= n & 0xFF;
	res <<= 8;
	n >>= 8;
	res |= n & 0xFF;
	res <<= 8;
	n >>= 8;
	res |= n & 0xFF;
	return (res);
}

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
	if (ac == 3 && ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) == 0)
	{
		ft_init_vec(&mlx);
		mlx.mlx_ptr = mlx_init();
		mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
		mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l,
		&mlx.img.endian);
		if (ft_load_text(&mlx.text) < 0)
			return (-1);
		if (ft_read_map(&mlx, argv[1]) < 0)
			return (-1);
		ft_raycasting(&mlx, &mlx.vec, &mlx.player);

		// t_bmp_image bmp_image;
		// bzero(&bmp_image, sizeof(t_bmp_image));;

		t_bmp_header theader;
		bzero(&theader, sizeof(t_bmp_header));

		theader.type = 0x4d42;
		theader.offset = 0x36;
		theader.dib_header_size = 0x28;
		theader.width_px = WIN_WIDTH;
		theader.height_px = WIN_HEIGHT;
		theader.num_planes = 0x01;
		theader.bits_per_pixel = 0x20;
		char header[54];
		bzero(header, 54);
		ft_memmove(header, &(theader.type), 2);
		ft_memmove(header+2, &(theader.size), 4);
		ft_memmove(header+6, &(theader.reserved1), 2);
		ft_memmove(header+8, &(theader.reserved2), 2);
		ft_memmove(header+10, &(theader.offset), 4);
		ft_memmove(header+14, &(theader.dib_header_size), 4);
		ft_memmove(header+18, &(theader.width_px), 4);
		ft_memmove(header+22, &(theader.height_px), 4);
		ft_memmove(header+26, &(theader.num_planes), 2);
		ft_memmove(header+28, &(theader.bits_per_pixel), 2);
		ft_memmove(header+30, &(theader.compression), 4);
		ft_memmove(header+34, &(theader.image_size_bytes), 4);
		ft_memmove(header+38, &(theader.x_resolution_ppm), 4);
		ft_memmove(header+42, &(theader.y_resolution_ppm), 4);
		ft_memmove(header+46, &(theader.num_colors), 4);
		ft_memmove(header+50, &(theader.important_colors), 4);
		int fd;
		fd = open("screenshot.bmp", O_WRONLY | O_APPEND | O_CREAT, 0644);
		write(fd, header, sizeof(t_bmp_header));
		// write(fd, &bmp_image.data, WIN_WIDTH * WIN_HEIGHT);
		// // char c = 0;
		// for (int i = 0; i < 132; i++)
		// {
			// write(fd, &c, 1);
		// }
	}
	return (0);

}