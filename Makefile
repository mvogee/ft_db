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
				add_row.c add_category.c modify_data.c new_table.c

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

all: libft $(NAME)

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

fclean_libft:
	@make -C libft fclean

clean: clean_libft
	rm -rf build/

fclean: fclean_libft clean
	rm -f $(NAME)

fclean_db: clean
	rm -f $(NAME)

re_db: fclean_db all

re: fclean all
