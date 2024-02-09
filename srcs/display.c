/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 02:21:54 by ycostode          #+#    #+#             */
/*   Updated: 2023/11/30 11:51:35 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_img(t_game *game)
{
	int	i;

	mlx_destroy_image(game->vars.mlx, game->sprite.win.data);
	mlx_destroy_image(game->vars.mlx, game->sprite.lose.data);
	mlx_destroy_image(game->vars.mlx, game->sprite.wall.data);
	i = 0;
	while (i < 2)
		mlx_destroy_image(game->vars.mlx, game->sprite.exit[i++].data);
	i = 0;
	while (i < 2)
		mlx_destroy_image(game->vars.mlx, game->sprite.nest[i++].data);
	i = 0;
	while (i < 4)
		mlx_destroy_image(game->vars.mlx, game->sprite.chicken[i++].data);
	i = 0;
	while (i < 9)
		mlx_destroy_image(game->vars.mlx, game->sprite.tile[i++].data);
	i = 0;
	while (i < 16)
		mlx_destroy_image(game->vars.mlx, game->sprite.player[i++].data);
	i = 0;
	while (i < 10)
		mlx_destroy_image(game->vars.mlx, game->sprite.number[i++].data);
}

void	change_at(t_map *map, int x, int y, char c)
{
	map->map[x + y * map->width] = c;
}

char	get_at(t_map map, int x, int y)
{
	return (map.map[x + y * map.width]);
}

static void	print_elem(t_game game, int x, int y)
{
	if (x == 0 && y == 0)
		show(game, game.sprite.tile[2], x, y);
	else if (x == 0 && y == game.map.height - 1)
		show(game, game.sprite.tile[0], x, y);
	else if (x == game.map.width - 2 && y == 0)
		show(game, game.sprite.tile[8], x, y);
	else if (x == game.map.width - 2 && y == game.map.height - 1)
		show(game, game.sprite.tile[6], x, y);
	else if (y == 0)
		show(game, game.sprite.tile[5], x, y);
	else if (y == game.map.height - 1)
		show(game, game.sprite.tile[3], x, y);
	else if (x == 0)
		show(game, game.sprite.tile[1], x, y);
	else if (x == game.map.width - 2)
		show(game, game.sprite.tile[7], x, y);
	else if (get_at(game.map, x, y) == '1')
		show(game, game.sprite.wall, x, y);
	else if (get_at(game.map, x, y) == 'C')
		show(game, game.sprite.nest[0], x, y);
	else if (get_at(game.map, x, y) == 'E')
		show(game, game.sprite.exit[0], x, y);
	else
		show(game, game.sprite.tile[4], x, y);
}

void	print_map(t_game game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game.map.width)
	{
		y = 0;
		while (y < game.map.height)
			print_elem(game, x, y++);
		x++;
	}
}
