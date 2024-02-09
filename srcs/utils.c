/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:06:21 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/02 15:41:03 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_comp(int *i, int tab[3])
{
	*i = -1;
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
}

void	parse_error(t_map *map, const t_string msg)
{
	map->parsed = FALSE;
	if (map->map)
	{
		free(map->map);
		map->map = NULL;
	}
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

static void	init_img_bisbis(t_game *game)
{
	game->sprite.win = load_xpm(game->vars.mlx, "textures/Win.xpm");
	game->sprite.lose = load_xpm(game->vars.mlx, "textures/Lose.xpm");
	game->sprite.number[0] = load_xpm(game->vars.mlx, "textures/0.xpm");
	game->sprite.number[1] = load_xpm(game->vars.mlx, "textures/1.xpm");
	game->sprite.number[2] = load_xpm(game->vars.mlx, "textures/2.xpm");
	game->sprite.number[3] = load_xpm(game->vars.mlx, "textures/3.xpm");
	game->sprite.number[4] = load_xpm(game->vars.mlx, "textures/4.xpm");
	game->sprite.number[5] = load_xpm(game->vars.mlx, "textures/5.xpm");
	game->sprite.number[6] = load_xpm(game->vars.mlx, "textures/6.xpm");
	game->sprite.number[7] = load_xpm(game->vars.mlx, "textures/7.xpm");
	game->sprite.number[8] = load_xpm(game->vars.mlx, "textures/8.xpm");
	game->sprite.number[9] = load_xpm(game->vars.mlx, "textures/9.xpm");
}

static void	init_img_bis(t_game *game)
{
	game->sprite.player[0] = load_xpm(game->vars.mlx, "textures/PlayerD0.xpm");
	game->sprite.player[1] = load_xpm(game->vars.mlx, "textures/PlayerD1.xpm");
	game->sprite.player[2] = load_xpm(game->vars.mlx, "textures/PlayerD2.xpm");
	game->sprite.player[3] = load_xpm(game->vars.mlx, "textures/PlayerD3.xpm");
	game->sprite.player[4] = load_xpm(game->vars.mlx, "textures/PlayerU0.xpm");
	game->sprite.player[5] = load_xpm(game->vars.mlx, "textures/PlayerU1.xpm");
	game->sprite.player[6] = load_xpm(game->vars.mlx, "textures/PlayerU2.xpm");
	game->sprite.player[7] = load_xpm(game->vars.mlx, "textures/PlayerU3.xpm");
	game->sprite.player[8] = load_xpm(game->vars.mlx, "textures/PlayerL0.xpm");
	game->sprite.player[9] = load_xpm(game->vars.mlx, "textures/PlayerL1.xpm");
	game->sprite.player[10] = load_xpm(game->vars.mlx, "textures/PlayerL2.xpm");
	game->sprite.player[11] = load_xpm(game->vars.mlx, "textures/PlayerL3.xpm");
	game->sprite.player[12] = load_xpm(game->vars.mlx, "textures/PlayerR0.xpm");
	game->sprite.player[13] = load_xpm(game->vars.mlx, "textures/PlayerR1.xpm");
	game->sprite.player[14] = load_xpm(game->vars.mlx, "textures/PlayerR2.xpm");
	game->sprite.player[15] = load_xpm(game->vars.mlx, "textures/PlayerR3.xpm");
	init_img_bisbis(game);
}

void	init_img(t_game *game)
{
	game->sprite.wall = load_xpm(game->vars.mlx, "textures/Wall.xpm");
	game->sprite.exit[0] = load_xpm(game->vars.mlx, "textures/ExitC.xpm");
	game->sprite.exit[1] = load_xpm(game->vars.mlx, "textures/ExitF.xpm");
	game->sprite.nest[0] = load_xpm(game->vars.mlx, "textures/NestF.xpm");
	game->sprite.nest[1] = load_xpm(game->vars.mlx, "textures/NestE.xpm");
	game->sprite.chicken[0] = load_xpm(game->vars.mlx, "textures/Chicken0.xpm");
	game->sprite.chicken[1] = load_xpm(game->vars.mlx, "textures/Chicken1.xpm");
	game->sprite.chicken[2] = load_xpm(game->vars.mlx, "textures/Chicken2.xpm");
	game->sprite.chicken[3] = load_xpm(game->vars.mlx, "textures/Chicken3.xpm");
	game->sprite.tile[0] = load_xpm(game->vars.mlx, "textures/TileLB.xpm");
	game->sprite.tile[1] = load_xpm(game->vars.mlx, "textures/TileLM.xpm");
	game->sprite.tile[2] = load_xpm(game->vars.mlx, "textures/TileLU.xpm");
	game->sprite.tile[3] = load_xpm(game->vars.mlx, "textures/TileMB.xpm");
	game->sprite.tile[4] = load_xpm(game->vars.mlx, "textures/Tile.xpm");
	game->sprite.tile[5] = load_xpm(game->vars.mlx, "textures/TileMU.xpm");
	game->sprite.tile[6] = load_xpm(game->vars.mlx, "textures/TileRB.xpm");
	game->sprite.tile[7] = load_xpm(game->vars.mlx, "textures/TileRM.xpm");
	game->sprite.tile[8] = load_xpm(game->vars.mlx, "textures/TileRU.xpm");
	init_img_bis(game);
}
