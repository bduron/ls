# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bduron <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/07 13:02:54 by bduron            #+#    #+#              #
#    Updated: 2017/03/09 17:23:17 by bduron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT_LS= ft_ls

CC= gcc
CFLAGS= -Wall -Wextra -Werror #-g #-fsanitize=address
LIBFT= -Llibft -lft 

RM= rm -rf

INC_DIR= includes/

SRC= \
ls.c

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
