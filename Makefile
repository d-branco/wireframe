# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 08:19:06 by abessa-m          #+#    #+#              #
#    Updated: 2025/02/11 14:14:23 by abessa-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= fdf
NAME-BONUS	:= fdf
LIBFT		:= libft/libft.a mlx_linux/libmlx_Linux.a
#################################################################### Compiler  #
CC			:= cc
CFLAGS		:= -g -lm -Wall -Wextra -Werror
MLXFLAGS	:= \
	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
########################################################## Intermidiate steps  #
RM			:= rm -f
AR			:= ar rcs
######################################################### Objects and Headers  #
HEADERS		= fdf.h
SRCS		= \
	fdf.c fdf-init.c fdf-close.c \
	fdf-map.c fdf-line.c fdf-draw.c 
OBJS		= $(SRCS:.c=.o)
SRCS-BONUS		= 
OBJS-BONUS		= $(SRCS-BONUS:.c=.o)
##################################################################### Targets  #
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME) \
	&& echo "$(GRAY)Compiled:$(COR) $(OBJS)"

%.o: %.c
	@$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@ \

$(LIBFT):
	@make --no-print-directory -C ./libft/ \
	&& make --no-print-directory -C mlx_linux/ 

bonus: $(OBJS-BONUS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS-BONUS) $(LIBFT) -o $(NAME-BONUS) \
	&& echo "$(GRAY)Compiled:$(COR) $(OBJS-BONUS)"

clean:
	@$(RM) *.o *.gch ; \
	make --no-print-directory -C libft/ clean \
	&& make --no-print-directory -C mlx_linux/ clean 

fclean: clean
	@make --no-print-directory -C libft/ fclean \
	&& $(RM) $(NAME) $(NAME-BONUS)

re: fclean all
	@echo "$(GRAY)redone$(COR)"

.PHONY: all clean fclean re
####################################################################### Colors #
COR = \033[0m# COlor Remove
PURPLE = \033[1;35m# purple
GRAY = \033[1;90m# gray
YELLOW = \033[1;93m# yellow
