/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:36:26 by ycostode          #+#    #+#             */
/*   Updated: 2023/12/04 15:23:28 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	show_move(t_game *game)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_itoa(++game->player.moves);
	while (s[i])
	{
		mlx_put_image_to_window(game->vars.mlx, game->vars.win,
			game->sprite.number[s[i] - '0'].data, CELL_SIZE - 8 + i * NUM_SIZE,
			8);
		i++;
	}
	free(s);
}

void	player_facing(t_player *player, int x, int y)
{
	reset_facing(player);
	if (x == 0 && y == 1)
		player->facing[0] = TRUE;
	if (x == 0 && y == -1)
		player->facing[1] = TRUE;
	if (x == -1 && y == 0)
		player->facing[2] = TRUE;
	if (x == 1 && y == 0)
		player->facing[3] = TRUE;
}

void	reset_facing(t_player *player)
{
	player->facing[0] = FALSE;
	player->facing[1] = FALSE;
	player->facing[2] = FALSE;
	player->facing[3] = FALSE;
}

int	set_player(t_game *game)
{
	if (game->player.can_move == FALSE)
		return (show_end(game));
	set_enemy(game);
	if (game->player.facing[0] && game->player.time == 0)
		show(*game, game->sprite.player[game->player.frames], game->player.x,
			game->player.y);
	else if (game->player.facing[1] && game->player.time == 0)
		show(*game, game->sprite.player[4 + game->player.frames],
			game->player.x, game->player.y);
	else if (game->player.facing[2] && game->player.time == 0)
		show(*game, game->sprite.player[8 + game->player.frames],
			game->player.x, game->player.y);
	else if (game->player.facing[3] && game->player.time == 0)
		show(*game, game->sprite.player[12 + game->player.frames],
			game->player.x, game->player.y);
	game->player.time++;
	if (game->player.time == ANIM_DELAY)
	{
		game->player.frames++;
		if (game->player.frames == 4)
			game->player.frames = 0;
		game->player.time = 0;
	}
	return (1);
}

void	init_player(t_game *game)
{
	int	x;
	int	y;

	game->player.egg = 0;
	reset_facing(&(game->player));
	game->player.facing[0] = TRUE;
	game->player.can_move = TRUE;
	game->player.frames = 0;
	game->player.moves = -1;
	game->player.time = 0;
	x = 0;
	while (x < game->map.width)
	{
		y = 0;
		while (y < game->map.height)
		{
			if (get_at(game->map, x, y) == 'P')
			{
				game->player.x = x;
				game->player.y = y;
			}
			y++;
		}
		x++;
	}
}
