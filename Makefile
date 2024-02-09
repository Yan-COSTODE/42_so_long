CC=cc
NAME = so_long
INCPATH = includes/
SRCPATH = srcs/
SRCS = enemy.c parse_map.c rand.c so_long.c pathfinding.c pathfinding_utils.c wrap.c display.c animation.c utils.c tools.c
HEADER = so_long.h mlx.h mlx_int.h libft.h
SRCSINC = $(addprefix $(SRCPATH), $(SRCS))
HEADINC = $(addprefix $(INCPATH), $(HEADER))
OBJS = $(SRCSINC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g

all:$(NAME)

bonus:all

$(NAME): $(OBJS)
	@printf "\033[1;37m"
	make --no-print-directory -C mlx
	cp mlx/libmlx_Linux.a ./$(INCPATH)
	make bonus --no-print-directory -C libft
	cp libft/libft.a ./$(INCPATH)
	$(CC) $(OBJS) -L./$(INCPATH) -lft -lmlx_Linux -lXext -lX11 -lm -lz -o $(NAME)
	@printf "\033[1;32mCompilation Finished !\n\033[0m"

%.o : %.c $(HEADINC)
	@printf "\033[1;37m"
	$(CC) $(CFLAGS) -I./$(INCPATH)  $< -c -o $@

fclean: clean
	@printf "\033[1;37m"
	rm -f $(NAME)
	rm -f ./$(INCPATH)libft.a
	rm -f ./$(INCPATH)libmlx_Linux.a
	make fclean --no-print-directory -C libft
	@printf "\033[1;31mProgram Deleted !\n\033[0m"

clean:
	@printf "\033[1;37m"
	rm -f $(OBJS)
	make clean --no-print-directory -C libft
	make clean --no-print-directory -C mlx
	@printf "\033[1;31mObjects Deleted !\n\033[0m"

re: fclean all

.PHONY: all fclean clean re
