# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 14:57:58 by pchadeni          #+#    #+#              #
#    Updated: 2019/01/16 17:54:38 by pchadeni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------Name of the project------#

NAME = libft_malloc_$HOSTTYPE.so

#------Assign HOSTTYPE------#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m) $(shell uname -s)
endif

#------All sources------#

MALLOC = main.c			\

FILES_TO_TEST = check_placement.c

TESTS = $(addprefix test_, $(FILES_TO_TEST))

#SRCS += $(addprefix $(SRCS_PATH)/, $(FILLER))
OBJ       += $(addprefix ./$(OBJ_PATH)/, $(MALLOC:.c=.o))
OBJP      += $(addprefix ./$(OBJ_PATH)/, $(SRCS_PATH))
TESTS_OBJ  = $(addprefix ./$(TESTS_PATH)/, $(TESTS:.c=.o))
OBJ_FILES_TO_TEST = $(addprefix ./$(OBJ_PATH)/, $(FILES_TO_TEST:.c=.o))

#------Includes------#

INCLUDES = ./includes/
INC += -I $(INCLUDES)
INC += -I $(LIB_PATH)/$(INCLUDES)
LIB = $(LIB_PATH)/libft.a
HEAD = $(INCLUDES)/filler.h

#------Path------#

SRCS_PATH = srcs
OBJ_PATH  = obj
LIB_PATH  = libft
TESTS_PATH = tests

#------Main rules------#

all: $(OBJ_PATH) makelib $(NAME)

$(NAME): $(OBJ)
	@printf "\33[2KObjects created $(BOLD_GREEN)✓$(EOC)\n"
	@printf "Start making $(NAME)... "
	@$(CC) $(C_FLAGS) $(FLAGS) $(INC) -shared -o $@ $^ $(LIB)
	@ln -s libft_malloc.so $(NAME)
	@printf "$(BOLD_GREEN)$(NAME)$(EOC) created $(BOLD_GREEN)✓$(EOC)\n"

$(OBJ_PATH):
	@printf "Start creating obj folder... "
	@mkdir -p $(OBJ_PATH)
	@printf "$(OBJ_PATH) created  "
	@mkdir -p $(OBJP)
	@printf "$(OBJP) created\n"

$(OBJ_PATH)/%.o: $(SRCS_PATH)/%.c $(HEAD)
	@$(CC) $(FLAGS) $(C_FLAGS) $(INC) -o $@ -c $<
	@printf " $(COL_GREEN)[OK]$(EOC)    $(COL_YELLOW)Compiling:$(EOC) $<\r"

makelib:
	@make -C $(LIB_PATH) NOERR=$(NOERR) DEV=$(DEV) SAN=$(SAN)

clean: cleanlib
	@rm -Rf $(OBJ_PATH)
	@rm -Rf $(TEST_OBJ)
	@echo "$(BOLD_GREEN)$(NAME)$(EOC) clean $(BOLD_GREEN)✓$(EOC)"

cleanlib:
	@make clean -C $(LIB_PATH)

fclean: fcleanlib clean
	@rm -Rf $(NAME)
	@echo "$(BOLD_GREEN)$(NAME)$(EOC) fclean $(BOLD_GREEN)✓$(EOC)"

fcleanlib:
	@make fclean -C $(LIB_PATH)

re: fclean all

#------Compilation's flags------#

CC = gcc

# flags
C_FLAGS = -Wall -Wextra

ifneq ($(NOERR),yes)
C_FLAGS += -Werror
endif

ifeq ($(DEV),yes)
FLAGS += -g
endif

ifeq ($(SAN),yes)
FLAGS += -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif

#------Define colors------#

BOLD_GREEN = \033[01;32m
COL_GREEN = \033[0;32m
COL_YELLOW = \033[0;33m
EOC = \033[0m

.PHONY: all re fclean clean
