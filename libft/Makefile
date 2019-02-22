# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 14:57:58 by pchadeni          #+#    #+#              #
#    Updated: 2018/06/26 14:47:07 by pchadeni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------Name of the project------#

NAME = libft.a

#------Compilation's flags------#

AR = ar rc
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

NUMBER_FILES = $(words $(FTPRINTF) + $(LIB_FILES))
INDEX = 1

#------All sources------#

FTPRINTF = ft_printf.c	\
	   attrib_flags.c	\
	   check_char.c		\
	   check_flags.c	\
	   conv_cs.c		\
	   conv_digit.c		\
	   conv_majcs.c		\
	   conv_uni.c		\
	   exit_printf.c	\
	   flags_digit.c	\
	   flags_str.c		\
	   ft_itoa_base.c	\
	   ft_utoa_base.c	\
	   ft_strzerojoin.c \
	   parser.c			\
	   struct.c

############ Do not edit ############

#------Library------#

INCLUDES = ./includes/
INC += -I$(INCLUDES)
INC += -I $(LIB_PATH)
HEAD = $(INCLUDES)/libft.h	\
	   $(INCLUDES)/ft_printf.h

#### FILES FROM LIB ####
LIB_FILES = ft_atoi.c	\
		ft_bzero.c		\
		ft_case.c 		\
		ft_checkopt.c	\
		ft_foreachint.c	\
		ft_getopt.c		\
		ft_ischar.c		\
		ft_isx.c		\
		ft_itoa.c		\
		ft_lastchar.c	\
		ft_lstalloc.c	\
		ft_lstindel.c	\
		ft_lstmanip.c	\
		ft_maths.c		\
		ft_memalloc.c	\
		ft_memmanip.c	\
		ft_nbchar.c		\
		ft_nbwords.c	\
		ft_point.c		\
		ft_put.c		\
		ft_put_fd.c		\
		ft_putcolor.c	\
		ft_putsgap.c	\
		ft_putformat.c	\
		ft_strcat.c		\
		ft_strchr.c		\
		ft_strclr.c		\
		ft_strcmp.c		\
		ft_strcpy.c		\
		ft_strdel.c		\
		ft_strdup.c		\
		ft_strgap.c		\
		ft_striter.c	\
		ft_strjoin.c	\
		ft_strlen.c		\
		ft_strmap.c		\
		ft_strnew.c		\
		ft_splitwsp.c	\
		ft_strsplit.c	\
		ft_strstr.c		\
		ft_strsub.c		\
		ft_strtrim.c	\
		ft_tab.c		\
		ft_vector.c		\
		get_next_line.c

#------Path------#

SRCS_PATH = srcs
OBJ_PATH  = obj
LIB_PATH  = libft
FTPRINTF_PATH = ft_printf
SRCS_LIB    += $(addprefix      $(LIB_PATH)/, $(LIB_FILES))
SRCS_PRINTF += $(addprefix $(FTPRINTF_PATH)/, $(FTPRINTF))

SRCS += $(addprefix $(SRCS_PATH)/, $(SRCS_LIB))
SRCS += $(addprefix $(SRCS_PATH)/, $(SRCS_PRINTF))

OBJP += $(addprefix ./$(OBJ_PATH)/, $(LIB_PATH))
OBJP += $(addprefix ./$(OBJ_PATH)/, $(FTPRINTF_PATH))

OBJ += $(addprefix ./$(OBJ_PATH)/, $(SRCS_LIB:.c=.o))
OBJ += $(addprefix ./$(OBJ_PATH)/, $(SRCS_PRINTF:.c=.o))

#------Main rules------#

all: $(OBJ_PATH) $(NAME)

$(NAME): $(OBJ)
	@$(eval PROGRESS:=$(shell echo $$(($(PROGRESS)+1))))
	@printf "\r⸨`printf '▓%.s' {0..$(PROGRESS)}`⸩"
	@printf " Objects created $(BOLD_GREEN)✓$(EOC)\n"
	@printf "Start making $(NAME)...\n"
	@$(AR) $(NAME) $^
	@ranlib $(NAME)
	@printf "$(BOLD_GREEN)⤖     $(NAME)$(EOC) created $(BOLD_GREEN)✓$(EOC)\n"

$(OBJ_PATH):
	@echo "Generating $(NAME)"
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJP)

$(OBJ_PATH)/%.o: $(SRCS_PATH)/%.c $(HEAD)
	@$(eval PROGRESS=$(shell echo $$(($(INDEX)*30/$(NUMBER_FILES)))))
	@$(eval NOT_DONE=$(shell echo $$((30-$(INDEX)*30/$(NUMBER_FILES) - 1))))
	@$(CC) $(FLAGS) $(C_FLAGS) $(INC) -MMD -o $@ -c $<
	@$(eval INDEX:=$(shell echo $$(($(INDEX)+1))))
	@$(eval PERCENT=$(shell echo $$((($(INDEX))*100/$(NUMBER_FILES)))))
	@printf "\r⸨`printf '▓%.s' {0..$(PROGRESS)}``printf '░%.s' {0..$(NOT_DONE)}`⸩"
	@printf " | %3d%% - [$(INDEX)/$(NUMBER_FILES)]" $(PERCENT)

clean:
	@if [ -d $(OBJ_PATH) ]; \
	then \
		rm -Rf $(OBJ_PATH); \
		echo "$(BOLD_GREEN)clean ✓$(EOC)"; \
	fi;

fclean: clean
	@if [ -e $(NAME) ]; \
	then \
		rm -Rf $(NAME); \
		echo "$(BOLD_GREEN)fclean ✓$(EOC)"; \
	fi;

re: fclean all

#------Define colors------#

BOLD_GREEN = \033[01;32m
COL_GREEN = \033[0;32m
COL_YELLOW = \033[0;33m
EOC = \033[0m
