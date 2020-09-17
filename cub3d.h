/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 16:13:40 by viroques          #+#    #+#             */
/*   Updated: 2020/09/17 16:19:16 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "./minilibx/mlx.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

typedef struct  s_img
{
    void        *img_ptr;
    int         *data;
    //useless variable
    int         size_l;
    int         bpp;
    int         endian;
}               t_img;

typedef struct  s_mlx
{
    void        *mlx_ptr;
    void        *win;
    t_img       img;
}               t_mlx;

#endif