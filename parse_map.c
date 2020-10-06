#include "cub3d.h"
#include <stdio.h>

int         ft_read_resolution (t_mlx *mlx, char *str)
{
    int i;

    i = 0;
    if (str[i] != ' ' || !ft_isdigit(str[i + 1]))
        return (-1);
    i++;
    mlx->win_width = ft_atoi(str);
    while (str[i] >= '0' && str[i] <= '9')
        i++;
    if (str[i] != ' ' || !ft_isdigit(str[i + 1]))
        return (-1);
    mlx->win_height = ft_atoi(&str[i]);
    // mlx_get_screen_size(mlx->mlx_ptr, &mlx->screen_width, &mlx->screen_height);
    // if (mlx->win_width > mlx->screen_width)
    //     mlx->win_width = mlx->screen_width;
    // if (mlx->win_height > mlx->screen_height)
    //     mlx->win_height = mlx->screen_height;
    printf("WIDTH=%i HEIGHT=%i\n", mlx->win_width, mlx->win_height);
    return (0);
}
int         ft_read_conv(t_mlx *mlx, t_text *text, char *str)
{
    char *path;

    if (str[0] == 'R')
        ft_read_resolution(mlx, &str[1]);
    if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ' && str[3] == '.' && str[4] == '/')
    {
        path = ft_strdup(&str[3]);
        printf("%s\n", path);
        if (!(text->texture[0]->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &text->texture[0]->width, &text->texture[0]->height)))
        {
            free(path);
            return (-1);
        }
	    text->texture[0]->data = (int *)mlx_get_data_addr(text->texture[0]->img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
        free(path);
    }
    return (0);
}
int         ft_compt_args(char **tab, int size)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    if (i == size)
        return (1);
    return (0);
}
void        ft_free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

int         ft_str_is_digit(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_isdigit(str[i]))
            i++;
        else
            return (0);
    }
    return (1);
}

int         ft_hash(char *key)
{
    int i;
    int hash_value;
    i = 0;
    hash_value = 0;
    while (key[i])
    {
        hash_value = hash_value << 8;
        hash_value += key[i];
        i++;
    }
    return (hash_value % H_SIZE);
}

int         error(char *msg, int ret)
{
    write(2, msg, ft_strlen(msg));
    return (ret);
}

int        ft_parse_map(t_mlx *mlx, char **file, t_text *text)
{
    int i;
    int k;
    char **values;
    char set[] = "NOSOWEEA";
    char toto[H_SIZE];
    ft_bzero(toto, H_SIZE);
    i = 0;
    k = 0;
    int e = 0;
    while (i < 8)
    {
        values = ft_split(file[i], ' ');
        if (values[0][0] == 'R' && ft_compt_args(values, 3) && toto[ft_hash("R")] == 0)
        {
            toto[ft_hash(values[0])] = 1;
            if (!ft_str_is_digit(values[1]) || !ft_str_is_digit(values[2]))
                return (error("It must be a digit", -1));
            mlx->win_width = ft_atoi(values[1]);
            mlx->win_height = ft_atoi(values[2]);
        }
        if (ft_strnstr(set, values[0], 9) && ft_compt_args(values, 2))
        {
            if (toto[ft_hash(values[0])] == 0)
                toto[ft_hash(values[0])] = 1;
            else
            {
                ft_free_tab(values);
                return (error("Error\n Duplicate texture\n", -1));
            }
            if (!ft_strncmp(values[0], "S", 2))
            {
                 if (!(text->texture[4]->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, values[1], &text->texture[4]->width, &text->texture[4]->height)))
                {
                    ft_free_tab(values);
                    return (-1);
                }
	            text->texture[4]->data = (int *)mlx_get_data_addr(text->texture[4]->img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
            }
            else
            {
                if (!(text->texture[e]->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, values[1], &text->texture[e]->width, &text->texture[e]->height)))
                {
                    ft_free_tab(values);
                    return (-1);
                }
	            text->texture[e]->data = (int *)mlx_get_data_addr(text->texture[e]->img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
                e++;
            }
        }
        ft_free_tab(values);
        i++;
    }
    return (0);
}


int        ft_read_and_split_map(t_mlx *mlx, char *path)
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
