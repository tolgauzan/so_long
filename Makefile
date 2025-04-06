NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = ./src
OBJ_DIR = ./obj
LIBFT_DIR = ./libft
MLX_DIR = ./minilibx
LIBFT = $(LIBFT_DIR)/libft.a
LIBMLX = $(MLX_DIR)/libmlx.a
INCLUDES = -I$(MLX_DIR) -I$(LIBFT_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext
NORM = norminette

SRC = $(SRC_DIR)/main.c \
	$(SRC_DIR)/free.c \
	$(SRC_DIR)/initialize.c\
	$(SRC_DIR)/create_map.c \
	$(SRC_DIR)/check_map.c \
	$(SRC_DIR)/check_map_file.c \
	$(SRC_DIR)/check_valid_path.c \
	$(SRC_DIR)/render.c \
	$(SRC_DIR)/event_listener.c \
	$(SRC_DIR)/event_utils.c \

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo " ✔ 🏁 $(NAME) executable created"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo " ✔ 📃 $@ object file created"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(LIBMLX):
	@make -C $(MLX_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@rm -rf $(OBJ_DIR)
	@echo " ✔ 🧹 Object files cleaned"

fclean:
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)
	@echo " ✔ 🧹 Object files cleaned"
	@echo " ✔ 🧹 $(NAME) cleaned"

re: fclean all
	@echo " ✔ 🛠️ Project rebuilt"

norm:
	$(NORM) $(LIBFT_DIR)/*.c $(LIBFT_DIR)/*.h $(SRC_DIR)/*.c $(SRC_DIR)/*.h

.PHONY: all clean fclean re norm