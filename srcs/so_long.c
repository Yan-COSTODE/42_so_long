/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:32:34 by ycostode          #+#    #+#             */
/*   Updated: 2023/12/04 16:58:20 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdio.h>

int	win_close(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
	return (1);
}

static int	handle_input(int code, t_game *game)
{
	(void)game;
	if (code == K_ESCAPE)
		return (win_close(&(game->vars)));
	if (code == K_UP || code == K_W)
		return (player_move(game, 0, -1));
	if (code == K_DOWN || code == K_S)
		return (player_move(game, 0, 1));
	if (code == K_LEFT || code == K_A)
		return (player_move(game, -1, 0));
	if (code == K_RIGHT || code == K_D)
		return (player_move(game, 1, 0));
	return (1);
}

static void	free_game(t_game *game)
{
	free_img(game);
	free(game->map.map);
	mlx_destroy_window(game->vars.mlx, game->vars.win);
	mlx_destroy_display(game->vars.mlx);
	free(game->vars.mlx);
}

static int	init_game(t_game *game, t_string file)
{
	parse_map(&(game->map), file);
	if (game->map.parsed == FALSE)
		return (0);
	game->state = NEUTRAL;
	game->vars.mlx = mlx_init();
	game->vars.win = mlx_new_window(game->vars.mlx, (game->map.width - 1) * 64,
			game->map.height * 64, "So Long");
	game->seed = 0;
	init_img(game);
	init_player(game);
	parse_path(game);
	if (game->map.parsed == FALSE)
	{
		free_game(game);
		return (0);
	}
	print_map(*game);
	show_move(game);
	spawn_enemy(game);
	mlx_hook(game->vars.win, E_DESTROY_NOTIFY, M_NONE, win_close,
		&(game->vars));
	mlx_hook(game->vars.win, E_KEY_PRESSED, M_KEY_PRESSED, handle_input, game);
	mlx_loop_hook(game->vars.mlx, set_player, game);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		write(2, "Error\nWrong number of parameters\n", 33);
		return (EXIT_FAILURE);
	}
	if (init_game(&game, argv[1]) == 0)
		return (EXIT_FAILURE);
	mlx_loop(game.vars.mlx);
	free_game(&game);
	return (EXIT_SUCCESS);
}
