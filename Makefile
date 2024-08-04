# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/21 02:50:41 by hlaadiou          #+#    #+#              #
#    Updated: 2023/08/21 14:44:34 by hlaadiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_M =	minishell
NAME_B =	minishell_bonus
SRCS_M = 	Mandatory/sources/builtins/cd_builtin.c \
			Mandatory/sources/builtins/echo_builtin.c \
			Mandatory/sources/builtins/env_builtin.c \
			Mandatory/sources/builtins/exit_builtin.c \
			Mandatory/sources/builtins/export_builtin.c \
			Mandatory/sources/builtins/export_builtin_utils.c \
			Mandatory/sources/builtins/pwd_builtin.c \
			Mandatory/sources/builtins/unset_builtin.c \
			Mandatory/sources/environment/environment.c \
			Mandatory/sources/environment/environment_utils.c \
			Mandatory/sources/executor/executor.c \
			Mandatory/sources/executor/executor_utils1.c \
			Mandatory/sources/executor/executor_utils2.c \
			Mandatory/sources/executor/executor_utils3.c \
			Mandatory/sources/executor/executor_utils4.c \
			Mandatory/sources/executor/executor_utils5.c \
			Mandatory/sources/executor/executor_utils6.c \
			Mandatory/sources/executor/executor_utils7.c \
			Mandatory/sources/executor/executor_utils8.c \
			Mandatory/sources/executor/executor_utils9.c \
			Mandatory/sources/executor/heredoc.c \
			Mandatory/sources/executor/open_heredocs.c \
			Mandatory/sources/garbage/free.c \
			Mandatory/sources/garbage/garbage.c \
			Mandatory/sources/libft/ft_atoi.c \
			Mandatory/sources/libft/ft_atoull.c \
			Mandatory/sources/libft/ft_isalnum.c \
			Mandatory/sources/libft/ft_isalpha.c \
			Mandatory/sources/libft/ft_isdigit.c \
			Mandatory/sources/libft/ft_itoa.c \
			Mandatory/sources/libft/ft_putstr_fd.c \
			Mandatory/sources/libft/ft_split.c \
			Mandatory/sources/libft/ft_strchr.c \
			Mandatory/sources/libft/ft_strcmp.c \
			Mandatory/sources/libft/ft_strdup.c \
			Mandatory/sources/libft/ft_strjoin.c \
			Mandatory/sources/libft/ft_strlcpy.c \
			Mandatory/sources/libft/ft_strlen.c \
			Mandatory/sources/libft/ft_strncmp.c \
			Mandatory/sources/libft/ft_strrchr.c \
			Mandatory/sources/libft/ft_strtrim.c \
			Mandatory/sources/libft/ft_substr.c \
			Mandatory/sources/macro_processor/dir.c \
			Mandatory/sources/macro_processor/env_insert_sort.c \
			Mandatory/sources/macro_processor/list_expander.c \
			Mandatory/sources/macro_processor/list_expander_utils1.c \
			Mandatory/sources/macro_processor/list_expander_utils2.c \
			Mandatory/sources/macro_processor/list_expander_utils3.c \
			Mandatory/sources/macro_processor/pattern_insert_sort.c \
			Mandatory/sources/macro_processor/redir_expander.c \
			Mandatory/sources/macro_processor/redir_expander_utils1.c \
			Mandatory/sources/macro_processor/redir_expander_utils2.c \
			Mandatory/sources/macro_processor/redir_expander_utils3.c \
			Mandatory/sources/macro_processor/redir_expander_utils4.c \
			Mandatory/sources/macro_processor/split_redir.c \
			Mandatory/sources/macro_processor/split_token.c \
			Mandatory/sources/macro_processor/wildcard.c \
			Mandatory/sources/main/minishell.c \
			Mandatory/sources/parser/rdp.c \
			Mandatory/sources/parser/rdp_utils1.c \
			Mandatory/sources/parser/rdp_utils2.c \
			Mandatory/sources/parser/rdp_utils3.c \
			Mandatory/sources/prompt/prompt.c \
			Mandatory/sources/signals/hdoc_signals.c \
			Mandatory/sources/signals/signals.c \
			Mandatory/sources/tokenizer/lexer.c \
			Mandatory/sources/tokenizer/lexer_utils1.c \
			Mandatory/sources/tokenizer/lexer_utils2.c \
			Mandatory/sources/tokenizer/lexer_utils3.c \
			Mandatory/sources/tokenizer/syntax.c \
			Mandatory/sources/tokenizer/syntax_utils1.c \
			Mandatory/sources/tokenizer/syntax_utils2.c

SRCS_B = 	Bonus/sources/builtins/cd_builtin_bonus.c \
			Bonus/sources/builtins/echo_builtin_bonus.c \
			Bonus/sources/builtins/env_builtin_bonus.c \
			Bonus/sources/builtins/exit_builtin_bonus.c \
			Bonus/sources/builtins/export_builtin_bonus.c \
			Bonus/sources/builtins/export_builtin_utils_bonus.c \
			Bonus/sources/builtins/pwd_builtin_bonus.c \
			Bonus/sources/builtins/unset_builtin_bonus.c \
			Bonus/sources/environment/environment_bonus.c \
			Bonus/sources/environment/environment_utils_bonus.c \
			Bonus/sources/executor/executor_bonus.c \
			Bonus/sources/executor/executor_utils1_bonus.c \
			Bonus/sources/executor/executor_utils2_bonus.c \
			Bonus/sources/executor/executor_utils3_bonus.c \
			Bonus/sources/executor/executor_utils4_bonus.c \
			Bonus/sources/executor/executor_utils5_bonus.c \
			Bonus/sources/executor/executor_utils6_bonus.c \
			Bonus/sources/executor/executor_utils7_bonus.c \
			Bonus/sources/executor/executor_utils8_bonus.c \
			Bonus/sources/executor/executor_utils9_bonus.c \
			Bonus/sources/executor/heredoc_bonus.c \
			Bonus/sources/executor/open_heredocs_bonus.c \
			Bonus/sources/garbage/free_bonus.c \
			Bonus/sources/garbage/garbage_bonus.c \
			Bonus/sources/libft/ft_atoi_bonus.c \
			Bonus/sources/libft/ft_atoull_bonus.c \
			Bonus/sources/libft/ft_isalnum_bonus.c \
			Bonus/sources/libft/ft_isalpha_bonus.c \
			Bonus/sources/libft/ft_isdigit_bonus.c \
			Bonus/sources/libft/ft_itoa_bonus.c \
			Bonus/sources/libft/ft_putstr_fd_bonus.c \
			Bonus/sources/libft/ft_split_bonus.c \
			Bonus/sources/libft/ft_strchr_bonus.c \
			Bonus/sources/libft/ft_strcmp_bonus.c \
			Bonus/sources/libft/ft_strdup_bonus.c \
			Bonus/sources/libft/ft_strjoin_bonus.c \
			Bonus/sources/libft/ft_strlcpy_bonus.c \
			Bonus/sources/libft/ft_strlen_bonus.c \
			Bonus/sources/libft/ft_strncmp_bonus.c \
			Bonus/sources/libft/ft_strrchr_bonus.c \
			Bonus/sources/libft/ft_strtrim_bonus.c \
			Bonus/sources/libft/ft_substr_bonus.c \
			Bonus/sources/macro_processor/dir_bonus.c \
			Bonus/sources/macro_processor/env_insert_sort_bonus.c \
			Bonus/sources/macro_processor/list_expander_bonus.c \
			Bonus/sources/macro_processor/list_expander_utils1_bonus.c \
			Bonus/sources/macro_processor/list_expander_utils2_bonus.c \
			Bonus/sources/macro_processor/list_expander_utils3_bonus.c \
			Bonus/sources/macro_processor/pattern_insert_sort_bonus.c \
			Bonus/sources/macro_processor/redir_expander_bonus.c \
			Bonus/sources/macro_processor/redir_expander_utils1_bonus.c \
			Bonus/sources/macro_processor/redir_expander_utils2_bonus.c \
			Bonus/sources/macro_processor/redir_expander_utils3_bonus.c \
			Bonus/sources/macro_processor/redir_expander_utils4_bonus.c \
			Bonus/sources/macro_processor/split_redir_bonus.c \
			Bonus/sources/macro_processor/split_token_bonus.c \
			Bonus/sources/macro_processor/wildcard_bonus.c \
			Bonus/sources/main/minishell_bonus.c \
			Bonus/sources/parser/rdp_bonus.c \
			Bonus/sources/parser/rdp_utils1_bonus.c \
			Bonus/sources/parser/rdp_utils2_bonus.c \
			Bonus/sources/parser/rdp_utils3_bonus.c \
			Bonus/sources/prompt/prompt_bonus.c \
			Bonus/sources/signals/hdoc_signals_bonus.c \
			Bonus/sources/signals/signals_bonus.c \
			Bonus/sources/tokenizer/lexer_bonus.c \
			Bonus/sources/tokenizer/lexer_utils1_bonus.c \
			Bonus/sources/tokenizer/lexer_utils2_bonus.c \
			Bonus/sources/tokenizer/lexer_utils3_bonus.c \
			Bonus/sources/tokenizer/syntax_bonus.c \
			Bonus/sources/tokenizer/syntax_utils1_bonus.c \
			Bonus/sources/tokenizer/syntax_utils2_bonus.c

C_FLAGS =	-Wall -Wextra -Werror
CC		=	cc
HEADER_M= 	Mandatory/include/minishell.h
HEADER_B= 	Bonus/include/minishell_bonus.h
LIB     = 	-L $(HOME)/.brew/Cellar/readline/8.2.1/lib
INC     = 	-I $(HOME)/.brew/Cellar/readline/8.2.1/include
OBJ_M   = 	$(SRCS_M:.c=.o)
OBJ_B   = 	$(SRCS_B:.c=.o)

all: 		$(NAME_M)

bonus:		$(NAME_B)

$(NAME_M): 	$(OBJ_M)
			$(CC) $(C_FLAGS) $^ -o $@ -lreadline $(LIB) $(INC)

$(NAME_B): 	$(OBJ_B)
			$(CC) $(C_FLAGS) $^ -o $@ -lreadline $(LIB) $(INC)

%_bonus.o:	%_bonus.c $(HEADER_B)
			$(CC) $(C_FLAGS) $(INC) -c $< -o $@

%.o: 		%.c $(HEADER_M)
			$(CC) $(C_FLAGS) $(INC) -c $< -o $@

clean:
			rm -f $(OBJ_M) $(OBJ_B)

fclean: 	clean
			rm -f $(NAME_M) $(NAME_B)

re: 		fclean all

.PHONY: 	all clean fclean re bonus
