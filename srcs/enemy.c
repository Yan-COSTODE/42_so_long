/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:32:43 by ycostode          #+#    #+#             */
/*   Updated: 2023/12/08 16:54:05 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	enemy_pos(t_game *game)
{
	game->enemy.alive = TRUE;
	if (get_at(game->map, game->enemy.x + 1, game->enemy.y) == '0')
		game->enemy.x++;
	else if (get_at(game->map, game->enemy.x - 1, game->enemy.y) == '0')
		game->enemy.x--;
	else if (get_at(game->map, game->enemy.x, game->enemy.y + 1) == '0')
		game->enemy.y++;
	else if (get_at(game->map, game->enemy.x, game->enemy.y - 1) == '0')
		game->enemy.y--;
	else
		game->enemy.alive = FALSE;
}

void	spawn_enemy(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map.width)
	{
		y = 0;
		while (y < game->map.height)
		{
			if (get_at(game->map, x, y) == 'E')
			{
				game->enemy.x = x;
				game->enemy.y = y;
			}
			++y;
		}
		++x;
	}
	enemy_pos(game);
	game->enemy.iter = 0;
	if (game->enemy.alive == FALSE)
	{
		game->enemy.x = 0;
		game->enemy.y = 0;
	}
}

static void	move_enemy(t_game *game)
{
	int	rand;

	show(*game, game->sprite.tile[4], game->enemy.x, game->enemy.y);
	game->enemy.iter = 0;
	rand = random_number(game, 1, 4);
	if (rand == 1 && (get_at(game->map, game->enemy.x + 1, game->enemy.y) == '0'
			|| get_at(game->map, game->enemy.x + 1, game->enemy.y) == 'P'))
		game->enemy.x++;
	else if (rand == 2 && (get_at(game->map, game->enemy.x - 1,
				game->enemy.y) == '0' || get_at(game->map, game->enemy.x - 1,
				game->enemy.y) == 'P'))
		game->enemy.x--;
	else if (rand == 3 && (get_at(game->map, game->enemy.x, game->enemy.y
				+ 1) == '0' || get_at(game->map, game->enemy.x, game->enemy.y
				+ 1) == 'P'))
		game->enemy.y++;
	else if (rand == 4 && (get_at(game->map, game->enemy.x, game->enemy.y
				- 1) == '0' || get_at(game->map, game->enemy.x, game->enemy.y
				- 1) == 'P'))
		game->enemy.y--;
	show(*game, game->sprite.chicken[game->player.frames], game->enemy.x,
		game->enemy.y);
}

void	set_enemy(t_game *game)
{
	if (game->player.can_move == FALSE || game->enemy.alive == FALSE)
		return ;
	if (game->player.x == game->enemy.x && game->player.y == game->enemy.y)
	{
		game->state = LOSE;
		game->player.can_move = FALSE;
	}
	if (game->player.time == 0)
	{
		game->enemy.iter++;
		show(*game, game->sprite.chicken[game->player.frames], game->enemy.x,
			game->enemy.y);
	}
	if (game->enemy.iter == ENEMY_DELAY)
		move_enemy(game);
}
