# /* ************************************************************************** */
# /*                                                                            */
# /*                                                        :::      ::::::::   */
# /*   makefile                                           :+:      :+:    :+:   */
# /*                                                    +:+ +:+         +:+     */
# /*   By: bpatel <marvin@42.fr>                      +#+  +:+       +#+        */
# /*                                                +#+#+#+#+#+   +#+           */
# /*   Created: 2017/03/09 14:36:11 by bpatel            #+#    #+#             */
# /*   Updated: 2017/03/09 14:36:13 by bpatel           ###   ########.fr       */
# /*                                                                            */
# /* ************************************************************************** */


FILENAMES	= main.c helper_funcs.c link_list_funcs.c query.c list_to_file.c \
				file_to_list.c delete_row.c delete_category.c \
				add_row.c add_category.c

//ASAN		= -fsanitize=address
NAME		= db
CC			= gcc
CFLAGS		+= -Wall -Werror -Wextra
INC			+= -I./includes

SRCS		= $(addprefix srcs/, $(FILENAMES))
OBJS		= $(addprefix build/, $(FILENAMES:.c=.o))

LIBFT		= ./libft/libft.a
LIBFTINC	= -I./libft/includes
LIBFTLINK	= -L./libft -lft

.PHONY: all clean fclean re

all: libft $(NAME) clean

build:
	mkdir $@

build/%.o: srcs/%.c | build
	$(CC) $(CFLAGS) $(ASAN) $(INC) $(LIBFTINC) $(LIBMLXINC) -o $@ -c $<

libft: $(LIBFT)

$(LIBFT):
	make -C ./libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(ASAN) $(AFLAGS) $(INC) $(LIBFTLINK) -o $@ $^

clean_libft:
	@make -C libft clean

clean: clean_libft
	rm -rf build/

fclean: clean
	rm -f $(NAME)

re: fclean all
