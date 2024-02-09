/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:15:17 by ycostode          #+#    #+#             */
/*   Updated: 2023/12/08 16:54:28 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	show_end(t_game *game)
{
	int	height;
	int	width;

	if (game->state == NEUTRAL)
		return (1);
	height = game->map.height * CELL_SIZE;
	width = (game->map.width - 1) * CELL_SIZE;
	if (game->state == WIN)
	{
		print_image(*game, game->sprite.win, width / 2 - CELL_15, height / 2
			- CELL_15);
		game->state = NEUTRAL;
	}
	if (game->state == LOSE)
	{
		print_image(*game, game->sprite.lose, width / 2 - CELL_15, height / 2
			- CELL_15);
		game->state = NEUTRAL;
	}
	return (1);
}

void	reset_tiles(t_game *game, int x, int y)
{
	char	c;
	int		i;
	int		j;

	i = game->player.x - x;
	j = game->player.y - y;
	c = get_at(game->map, i, j);
	if (c == 'i')
	{
		show(*game, game->sprite.nest[1], i, j);
		change_at(&(game->map), i, j, 'c');
	}
	else if (c != 'c')
		show(*game, game->sprite.tile[4], i, j);
}

void	open_exit(t_game *game)
{
	int		x;
	int		y;
	char	c;

	x = 0;
	while (x < game->map.width)
	{
		y = 0;
		while (y < game->map.height)
		{
			c = get_at(game->map, x, y);
			if (c == 'E')
			{
				show(*game, game->sprite.exit[1], x, y);
				change_at(&game->map, x, y, 'e');
			}
			y++;
		}
		x++;
	}
}

int	player_movement(t_game *game, char c, int x, int y)
{
	if (game->player.x == game->enemy.x && game->player.y == game->enemy.y)
	{
		game->state = LOSE;
		game->player.can_move = FALSE;
	}
	else if (c == 'C')
	{
		game->player.egg++;
		if (game->player.egg == game->map.egg)
			open_exit(game);
		change_at(&(game->map), game->player.x, game->player.y, 'i');
	}
	else if (c == 'e')
	{
		reset_tiles(game, x, y);
		game->state = WIN;
		game->player.can_move = FALSE;
	}
	else if (c == 'c')
		change_at(&(game->map), game->player.x, game->player.y, 'i');
	else
		change_at(&(game->map), game->player.x, game->player.y, 'P');
	return (0);
}

int	player_move(t_game *game, int x, int y)
{
	char	c;

	if (game->player.can_move == FALSE)
		return (1);
	c = get_at(game->map, game->player.x + x, game->player.y + y);
	player_facing(&(game->player), x, y);
	if (c == '1' || c == 'E')
		return (1);
	show_move(game);
	game->player.x += x;
	game->player.y += y;
	game->player.time = 0;
	if (player_movement(game, c, x, y) == 1)
		return (1);
	reset_tiles(game, x, y);
	return (1);
}
