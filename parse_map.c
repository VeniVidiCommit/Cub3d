#include "cub3d.h"
#include <stdio.h>

int         ft_malloc_map(t_mlx *mlx, char **file)
{
    mlx->map.col = 0;
    mlx->map.line = 0;
    int i = 0;
    while (file[i])
    {
        if (ft_strlen(file[i]) > (size_t)mlx->map.col)
            mlx->map.col = ft_strlen(file[i]);
        mlx->map.line++;
        i++;
    }
    i = 0;
    if (!(mlx->map.world_map = malloc(sizeof(int *) * mlx->map.line)))
        return (error("Malloc fail\n", -1));
    while(i < mlx->map.line)
    {
        if (!(mlx->map.world_map[i] = malloc(sizeof(int) * mlx->map.col)))
            return (error("Malloc fail\n", -1));
        i++;
    }
    return (0);
}

int         ft_count(t_mlx *mlx, char **file)
{
    int i = 0;
    int j = 0;
    int start = 0;
    char set[] = "NWES";
    if (ft_malloc_map(mlx, file) < 0)
        return(-1);
    while(file[start])
    {
        j = 0;
        while (j < mlx->map.col)
        {
            if (file[start][j] == '0')
                mlx->map.world_map[i][j] = 0;
            else if (file[start][j] == '2')
            {
                mlx->map.world_map[i][j] = 2;
                // mlx->sprite.x = i;
                // mlx->sprite.y = j;
                mlx->count_sprite = mlx->count_sprite + 1;
            }
            else if (ft_strchr(set, file[start][j])) 
            {
                mlx->map.world_map[i][j] = 0;
                mlx->player.pos_x = i;
                mlx->player.pos_y = j;
                if (file[start][j] == 'N')
                {
                    mlx->player.dir_x = -1;
                    mlx->player.dir_y = 0;
                    mlx->player.plan_x = 0;
                    mlx->player.plan_y = 0.66;
                }
                if (file[start][j] == 'S')
                {
                    mlx->player.dir_x = 1;
                    mlx->player.dir_y = 0;
                    mlx->player.plan_x = 0;
                    mlx->player.plan_y = -0.66;
                }
                if (file[start][j] == 'E')
                {
                    mlx->player.dir_x = 0;
                    mlx->player.dir_y = 1;
                    mlx->player.plan_x = 0.66;
                    mlx->player.plan_y = 0;
                }
                if (file[start][j] == 'W')
                {
                    mlx->player.dir_x = 0;
                    mlx->player.dir_y = -1;
                    mlx->player.plan_x = -0.66;
                    mlx->player.plan_y = 0;
                }
            }
            else
                mlx->map.world_map[i][j] = 1;
            if (mlx->map.world_map[i][j] == 0 && (i == mlx->map.line - 1 || i == 0 || j ==  mlx->map.col - 1 || j == 0))
                return (error("Map is not close !\n", -1));
            j++;
        }
        i++;
        start++;
    }
    //malloc nb of sprite
    mlx->sprite = malloc(sizeof(t_sprite) * mlx->count_sprite);
    i = 0;
    j = 0;
    int nb = 0;
    while (file[i])
    {
        j = 0;
        while (file[i][j])
        {
            if (file[i][j] == '2')
            {
                mlx->sprite[nb].x = i;
                mlx->sprite[nb].y = j;
                nb++;
            }
            j++;
        }
        i++;
    }
    return (0);
}

int         ft_get_resolution(char **values, char *hash, t_mlx *mlx)
{
    if (!ft_compt_args(values, 3))
        return (error_free("Resolution is follow by less or more than 2 values\n", -1, values));
    if (hash[ft_hash("R")] == 0)
    {
        hash[ft_hash(values[0])] = 1;
        if (!ft_str_is_digit(values[1]) || !ft_str_is_digit(values[2]))
            return (error_free("Resolution values must be a digit\n", -1, values));
        mlx->win_width = ft_atoi(values[1]);
        mlx->win_height = ft_atoi(values[2]);
    }
    else
        return (error_free("Resolution is define more than one time\n", -1, values));
    return (0);
}
int         ft_load_sprite(t_mlx *mlx, char **values, t_text *text)
{
    if (!(text->texture[4]->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, values[1], &text->texture[4]->width, &text->texture[4]->height)))
        return (error_free("Invalide sprite texture, impossible to read\n", -1, values));
	text->texture[4]->data = (int *)mlx_get_data_addr(text->texture[4]->img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
    return (0);
}

int     ft_check_text(char **values, char *hash)
{
     if (hash[ft_hash(values[0])] == 0)
                hash[ft_hash(values[0])] = 1;
    else
        return (error_free("Duplicate texture\n", -1, values));
    if (!ft_compt_args(values, 2))
        return (error_free("Texture must be followed by only one path\n", -1, values));
    return (0);
}

int     ft_get_color_fc(t_mlx *mlx, char **values, char *hash)
{
    char **tab;
    int y = -1;
    int res = 0;
    int mult = 3;
    int tmp;

    if (hash[ft_hash(values[0])] == 0)
        hash[ft_hash(values[0])] = 1;
    else
        return (error_free("Duplicate F or C colors\n", -1, values));
    if (!ft_compt_args(values, 2))
        return (error_free("F/C colors must be like 220,100,20\n", -1, values));
    if(!(tab = ft_split(values[1], ',')))
        return (error_free("Malloc fail in ft_get_color_fc\n", -1, values));
    while (++y < 3)
    {
        tmp = ft_atoi(tab[y]);
        tmp = tmp << (--mult * 8);
        res += tmp;
    }
    if (values[0][0] == 'F')
        mlx->f_color = res;
    else
        mlx->c_color = res;
    ft_free_tab(tab);
    return (0);
}

int        ft_parse_map(t_mlx *mlx, char **file, t_text *text)
{
    int i;
    int k;
    char **values;
    char set[] = "NOSOWEEA";
    char hash[H_SIZE];
    int e;

    ft_bzero(hash, H_SIZE);
    i = 0;
    k = 0;
    e = 0;
    while (file[i])
    {
        values = ft_split(file[i], ' ');
        if (values[0][0] == 'R')
        {
            if (ft_get_resolution(values, hash, mlx) < 0)
                return (-1);
        }
        else if (ft_strnstr(set, values[0], 9))
        {
            if (ft_check_text(values, hash) < 0)
                return (-1);
            if (!ft_strncmp(values[0], "S", 2))
            {
                if (ft_load_sprite(mlx, values, text) < 0)
                    return (-1);
            }
            else
            {
                if (!(text->texture[e]->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, values[1], &text->texture[e]->width, &text->texture[e]->height)))
                    return (error_free("Failed to load texture\n", -1, values));
	            text->texture[e]->data = (int *)mlx_get_data_addr(text->texture[e]->img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
                e++;
            }
        }
        else if (values[0][0] == 'F' || values[0][0] == 'C')
            ft_get_color_fc(mlx, values, hash);
        else if ((values[0][0] == ' ' || ft_isdigit(values[0][0])) && i == 8)
        {
            ft_free_tab(values);
            break;
        }
        else
            return (error("Invalide characters in map\n", -1));
        ft_free_tab(values);
        i++;
    }
    return (ft_count(mlx, &file[i]));
}


int        ft_read_map(t_mlx *mlx, char *path)
{
    char buff[4096];
    char *stock;
    char *tmp;
    int fd;
    int ret;

    if (!(stock = malloc(sizeof(char))))
        return (-1);
    stock[0] = '\0';
    fd = open(path, O_RDONLY);
    while ((ret = read(fd, buff, 4096)))
    {
        buff[ret] = '\0';
        tmp = stock;
        if (!(stock = ft_strjoin(tmp, buff)))
        {
            free(tmp);
            return (-1);
        }
        free(tmp);
    }
    if (!(mlx->file = ft_split(buff, '\n')))
        return (-1);
    close(fd);
    if (ft_parse_map(mlx, mlx->file, &mlx->text) < 0)
        return (-1);
    return (0);
}
