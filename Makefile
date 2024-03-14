NAME = minishell
INCLUDE = ./include
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror -lreadline -I./include
#CFLAGS = -lreadline -I./include
SRC_DIR = ./src
OBJ_DIR = ./obj

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = 	$(SRC_DIR)/minishell.c\
		$(SRC_DIR)/utils.c\
		$(SRC_DIR)/utils2.c\
		$(SRC_DIR)/signal.c\
		$(SRC_DIR)/parser/tokenizer.c\
		$(SRC_DIR)/parser/parser.c\
		$(SRC_DIR)/parser/utils_tokenizer.c\
		$(SRC_DIR)/parser/utils_tokenizer2.c\
		$(SRC_DIR)/parser/utils_parser.c\
		$(SRC_DIR)/parser/parser_list_utils.c\
		$(SRC_DIR)/exe/exe.c\
		$(SRC_DIR)/exe/exe_forking.c\
		$(SRC_DIR)/exe/exe_utils.c\
		$(SRC_DIR)/exe/exe_utils2.c\
		$(SRC_DIR)/exe/redirections.c\
		$(SRC_DIR)/exe/redirections_utils.c\
		$(SRC_DIR)/exe/check_redirection.c\
		$(SRC_DIR)/env/env.c\
		$(SRC_DIR)/env/env_setup.c\
		$(SRC_DIR)/builtins/ft_exit.c\
		$(SRC_DIR)/builtins/ft_echo.c\
		$(SRC_DIR)/builtins/ft_pwd.c\
		$(SRC_DIR)/builtins/ft_env.c\
		$(SRC_DIR)/builtins/ft_cd.c\
		$(SRC_DIR)/builtins/ft_export.c\
		$(SRC_DIR)/builtins/import_builtins.c\
		$(SRC_DIR)/builtins/ft_export_utils.c\
		$(SRC_DIR)/builtins/ft_unset.c

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
RM = rm -rf
NORMI = norminette
NORM_FOLDER = ./src ./include

UPurple = \033[4;35m
BIRed =\033[1;91m
On_IGreen =\033[0;102m
CYAN = \033[0;36m
GREEN = \033[0;32m
RED = \033[0;31m
PURPLE = \033[1;200m
BLUE = \033[0;36m
ORANGE = \033[0;33m
BOLD = \033[1m
RESET = \033[0m
COLOR_SEPARATOR = \033[1;92m

SEPARATOR = "\033[1m ******************************* \033[0m"

all: obj_dir $(NAME)

$(NAME): $(OBJ)
	@echo $(SEPARATOR)
	@make -s -C $(LIBFT_DIR)
	@echo "$(BOLD)$(CYAN)  Compiled libft$(RESET)"
	@$(CC) $(OBJ) $(CFLAGS) $(LIBFT) -o $(NAME)
	@echo "$(BOLD)$(GREEN)  Compiled $(NAME) successfully$(RESET)"
	@echo "$(BOLD)$(GREEN)  READY TO START!$(RESET)"
	@echo $(SEPARATOR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BOLD) $(GREEN)  Compiled $(CYAN) $<$(RESET)"

obj_dir:
	@mkdir -p $(OBJ_DIR)
	@echo "$(CYAN)  obj folder $(PURPLE)$(OBJ_DIR) $(GREEN)created$(RESET)"
	@echo "$(CYAN)  Compiling files $(PURPLE)$(SRC_DIR) $(GREEN)...$(RESET)"

clean:
	@echo $(SEPARATOR)
	@$(RM) $(OBJ_DIR)
	@echo "$(BOLD)$(UPurple)  $(NAME) OBJ deleted$(RESET)"
	@make -s -C $(LIBFT_DIR) clean
	@echo "$(BOLD)$(UPurple)  libft OBJ deleted$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(BOLD)$(UPurple)  $(NAME) deleted$(RESET)"
	@make -s -C $(LIBFT_DIR) fclean
	@echo "$(BOLD)$(UPurple)  libft deleted$(RESET)"
	@echo $(SEPARATOR)

re: fclean all

norm:
	@echo "$(RED)"$(SEPARATOR)
	@echo -n "$(ORANGE)"
	@$(NORMI) $(LIBFT_DIR)
	@echo "$(RED)"$(SEPARATOR)
	@echo -n "$(CYAN)"
	@-$(NORMI) $(NORM_FOLDER) 2>/dev/null
	@echo "$(RED)"$(SEPARATOR)

.PHONY: all clean fclean re norm obj_dir
