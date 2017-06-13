# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bduron <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/07 13:02:54 by bduron            #+#    #+#              #
#    Updated: 2017/06/13 14:14:01 by bduron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT_LS= ft_ls

CC= gcc
CFLAGS= -Wall -Wextra -Werror -g -fsanitize=address
LIBFT= -Llibft -lft 

RM= rm -rf

INC_DIR= includes/

SRC= \
ls.c \
ls_parsing.c \
ls_cmp.c \
ls_main.c \
ls_display.c \
ls_display_list.c \
ls_libft.c \
debbug.c
 

OBJ= $(SRC:.c=.o)

VPATH= srcs/

########################
#    Makefile rules    # 
########################

all: libft $(FT_LS)

libft:
	@make -C libft

# Executables 

$(FT_LS): $(OBJ)
	@$(CC) -o $@ $(CFLAGS) $^ -I $(INC_DIR) $(LIBFT) 
	@echo "Compiling [$@]"

# Object files 

$(OBJ): $(SRC)
	@$(CC) -c $^ $(CFLAGS) -I $(INC_DIR) 
	@echo "Compiling [$^]"

# Cleaning rules 

clean:
	@rm -f $(OBJ)
	@echo "Cleaning [$(OBJ)]"	

fclean: clean
	@rm -rf $(FT_LS)
	@make fclean -C libft
	@echo "Cleaning [libft ft_ls]"	

re: fclean all

.PHONY: clean fclean re libft 
