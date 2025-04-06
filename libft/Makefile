NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar rcs
SRC = ft_strlen.c ft_memcpy.c ft_strlcpy.c ft_itoa.c \
	ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strnstr.c \
	ft_calloc.c ft_strjoin.c ft_strtrim.c \
	ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c \
	get_next_line.c get_next_line_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo " ✔ 📃 $@ file created"

$(NAME): $(OBJ)	
	@$(AR) $(NAME) $?
	@echo " ✔ 📚 $(NAME) static library created"

clean:
	@$(RM) $(OBJ) $(BOBJ)
	@echo " ✔ 🧹 Object files cleaned"

fclean: clean
	@$(RM) $(NAME)
	@echo " ✔ 🧹 $(NAME) static library cleaned"
	
re: fclean all
	@echo " ✔ 🛠️  Project rebuilded"

.PHONY: all bonus clean fclean re
