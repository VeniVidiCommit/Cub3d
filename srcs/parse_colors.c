#include "../include/cub3d.h"

static  int     get_res_value(char **tab, char c, t_mlx *mlx)
{
    int y;
    int tmp;
    int mult;
    int res;

    res = 0;
    mult = 3;
    y = -1;
     while (++y < 3)
    {
        if (!ft_str_is_digit(tab[y]))
            return (error("RGB colors must be only digits\n", -1));
        tmp = ft_atoi(tab[y]);
        if (tmp > 255 | tmp < 0)
            return (error("Invalide range of color must be between 0 and 255\n", -1));
        tmp = tmp << (--mult * 8);
        res += tmp;
    }
    if (c == 'F')
        mlx->f_color = res;
    else
        mlx->c_color = res;
    return (0);
}

int             ft_get_color_fc(t_mlx *mlx, char **values, char *hash)
{
    char **tab;

    if (hash[ft_hash(values[0])] == 0)
        hash[ft_hash(values[0])] = 1;
    else
        return (error("Duplicate F or C colors\n", -1));
    if (!ft_compt_args(values, 2))
        return (error("Expected F or C followed by rgb format\n", -1));
    if(!(tab = ft_split(values[1], ',')))
        return (error("Malloc fail in ft_get_color_fc\n", -1));
    if (!ft_compt_args(tab, 3))
        return (error_free("F/C colors must be RGB format\n", -1, tab));
    if (get_res_value(tab, values[0][0], mlx) < 0)
        return (error_free("", -1, tab));
    ft_free_tab(tab);
    return (0);
}