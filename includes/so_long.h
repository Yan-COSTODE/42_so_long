/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:16:38 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/02 15:28:19 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "enum.h"
# include "libft.h"
# include "mlx.h"
# include "stdbool.h"
# include <stdlib.h>

# define NUM_SIZE 32
# define CELL_SIZE 64
# define CELL_15 96
# define READ_SIZE 1024
# define ANIM_DELAY 16384
# define ENEMY_DELAY 4
# define NEUTRAL 0
# define WIN 1
# define LOSE 2

typedef unsigned char	*t_ustring;
typedef char			*t_string;
typedef struct s_map
{
	bool				parsed;
	int					width;
	int					height;
	t_string			map;
	int					egg;
}						t_map;
typedef struct s_params
{
	char				find;
	char				start;
	char				obstacle;
	t_map				map;
}						t_params;
typedef struct s_vector
{
	int					x;
	int					y;
}						t_vector;
typedef struct s_vars
{
	void				*mlx;
	void				*win;
}						t_vars;
typedef struct s_img
{
	void				*data;
	t_string			addr;
	int					bits;
	int					len;
	int					endian;
}						t_img;
typedef struct s_spritesheet
{
	t_img				wall;
	t_img				win;
	t_img				lose;
	t_img				exit[2];
	t_img				nest[2];
	t_img				tile[9];
	t_img				chicken[4];
	t_img				player[16];
	t_img				number[10];
}						t_spritesheet;
typedef struct s_player
{
	bool				facing[4];
	bool				can_move;
	int					egg;
	int					x;
	int					y;
	int					frames;
	int					time;
	int					moves;
}						t_player;
typedef struct s_enemy
{
	int					x;
	int					y;
	bool				alive;
	int					iter;
}						t_enemy;
typedef struct s_game
{
	t_map				map;
	t_vars				vars;
	t_spritesheet		sprite;
	t_player			player;
	t_enemy				enemy;
	char				state;
	unsigned int		seed;
}						t_game;

int						random_number(t_game *game, int min, int max);
void					spawn_enemy(t_game *game);
void					set_enemy(t_game *game);
void					print_image(t_game game, t_img img, int x, int y);
void					init_moves(int moves[8]);
int						is_inside(t_map map, int x, int y);
void					parse_path(t_game *game);
t_map					mapdup(t_map map);
int						show_end(t_game *game);
int						win_close(t_vars *vars);
int						player_move(t_game *game, int x, int y);
int						player_movement(t_game *game, char c, int x, int y);
void					open_exit(t_game *game);
void					reset_tiles(t_game *game, int x, int y);
void					init_comp(int *i, int tab[3]);
void					parse_error(t_map *map, const t_string msg);
void					show_move(t_game *game);
void					player_facing(t_player *player, int x, int y);
void					init_player(t_game *game);
int						set_player(t_game *game);
void					reset_facing(t_player *player);
void					change_at(t_map *map, int x, int y, char c);
char					get_at(t_map map, int x, int y);
void					show(t_game game, t_img img, int x, int y);
t_img					load_xpm(void *mlx, t_string path);
void					parse_map(t_map *map, const t_string file);
void					free_img(t_game *game);
void					init_img(t_game *game);
void					print_map(t_game game);

#endif
