NAME=msh
SRC= environment.c \
	 libft/ft_strlen.c \
	 libft/ft_strdup.c \
	 libft/ft_strcmp.c \
	 libft/ft_strncmp.c \
	 libft/ft_strjoin.c \
	 libft/ft_strtrim.c \
	 libft/ft_strchr.c \
	 libft/ft_strrchr.c \
	 libft/ft_strlcpy.c \
	 libft/ft_putstr_fd.c \
	 libft/ft_itoa.c \
	 libft/ft_atoi.c \
	 garbage/garbage.c \
	 tokenizer/lexer.c \
	 tokenizer/syntax.c \
	 parser/rdp.c \
	 builtins/env_builtin.c \
	 builtins/pwd_builtin.c \
	 builtins/cd_builtin.c \
	 free.c \
	 minishell.c \
	 prompt.c \

C_FLAGS= -Wall -Wextra -Werror -g #-fsanitize=address
header= minishell.h
obj= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(obj)
	gcc $(C_FLAGS) $^ -lreadline -o $@

%.o: %.c $(header)
	gcc $(C_FLAGS) -c $< -o $@

clean:
	rm -f $(obj)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
