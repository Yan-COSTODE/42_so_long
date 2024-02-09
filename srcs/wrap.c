/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 03:03:41 by ycostode          #+#    #+#             */
/*   Updated: 2023/12/01 15:31:54 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_img	load_xpm(void *mlx, t_string file)
{
	int		w;
	int		h;
	t_img	img;

	img.data = mlx_xpm_file_to_image(mlx, file, &w, &h);
	img.addr = mlx_get_data_addr(img.data, &img.bits, &img.len, &img.endian);
	return (img);
}

void	print_image(t_game game, t_img img, int x, int y)
{
	mlx_put_image_to_window(game.vars.mlx, game.vars.win, img.data, x, y);
}

void	show(t_game game, t_img img, int x, int y)
{
	print_image(game, img, x * CELL_SIZE, y * CELL_SIZE);
}
