# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/17 15:44:28 by abeauvoi          #+#    #+#              #
#    Updated: 2018/07/23 08:37:16 by abeauvoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

#
# Dirs
#

SRCS_DIR	= src
OBJS_DIR	= obj
LIB_DIR		= libft
INC_DIRS	= $(addsuffix includes, ./ $(LIB_DIR)/)
VPATH		= $(SRCS_DIR)

#
# Sources
#

SRCS		= main.c env.c list.c check_command.c core.c exec_builtin.c \
		  builtin.c signals.c expansions.c list2.c builtin_cd.c \
		  errno.c canonicalize.c canonicalize2.c
#
# Build
#

OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
CFLAGS		= -Wall -Werror -Wextra $(addprefix -I, $(INC_DIRS))
LFLAGS		= -L$(LIB_DIR) -lft
LIB		= libft.a
COMP		= $(CC) $(CFLAGS) -o $@ -c $<
LINK		= $(CC) $(CFLAGS) $(LFLAGS) -o $@ $(filter-out $(LIB_DIR)/$(LIB), $^)
NUMCORES 	= $(sysctl -n hw.ncpu)
_MAKEFLAGS	= -j$(echo $(NUMCORES)+1| bc) -l$(NUMCORES) -C $(LIB_DIR)

#
# Rules
#

all: $(LIB_DIR)/$(LIB) $(NAME)

debug: CFLAGS += -g3
debug: clean all

$(LIB_DIR)/$(LIB):
	@make $(_MAKEFLAGS)

$(NAME): $(LIB_DIR)/$(LIB) $(OBJS)
	@$(LINK)
	@echo "completed compilation \033[1;32m√"

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@$(COMP)

clean:
	@rm $(OBJS) 2> /dev/null || true
	@make $(_MAKEFLAGS) $@
	@rm -rf $(OBJS_DIR)
	@echo "cleaned .o files"

fclean: clean
	@rm $(NAME) 2> /dev/null || true
	@make $(_MAKEFLAGS) $@
	@echo "removed binary"

re: fclean all

.PHONY: all clean fclean re
