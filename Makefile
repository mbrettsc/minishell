USERNAME = mbrettsc
NAME = minishell
CFLAGS = $(INCLUDE) -Wall -Werror -Wextra
LIBFT = libft
LIBFTM = libft/libft.a
INCLUDE = -IInclude/ -I/Users/$(USERNAME)/homebrew/Cellar/readline/8.2.1/include
CC = gcc

SRC = src/expander_utils.c src/lexer_utils.c src/run_builtin3.c src/run_builtin2.c \
      src/create_files.c src/expander_utils2.c src/main.c src/run_execve.c \
      src/create_files_utils.c src/expander_utils3.c src/run_execve1.c \
      src/dup2_fd.c src/expander_utils4.c src/parser.c src/signal.c \
      src/env.c src/ft_check.c src/parser_utils.c src/single_or_multi_command.c \
      src/exec.c src/ft_check_utils.c src/parser_utils_others.c src/welcome_to_parse.c \
      src/exec_free.c src/heredoc.c src/run_builtin.c \
      src/exec_free2.c src/heredoc_utils.c src/run_builtin1.c src/builtin.c \
	  src/expander.c src/lexer.c \

OBJ = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(BASE)))

BASE = $(basename $(notdir $(SRC)))

OBJDIR = builds

all: $(NAME)

$(OBJDIR):
	@mkdir $(OBJDIR)

$(NAME):  $(OBJDIR) $(OBJ)
	@make -C $(LIBFT)
	@echo "Building Minishell"
	@make bonus -C $(LIBFT)
	@echo "Compiling Files..."
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFTM) -lreadline -L/Users/$(USERNAME)/homebrew/Cellar/readline/8.2.1/lib -o $(NAME)

$(OBJDIR)/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -rf $(OBJDIR)
	@echo "Cleaning Objects..."
	@make -C $(LIBFT) clean

fclean: clean
	@$(RM) -f $(NAME)
	@echo "Cleaning Program..."
	@make -C $(LIBFT) fclean

re: fclean all

check:
	@echo "SRC: $(SRC)"
	@echo "OBJ: $(OBJ)"
	@make -C $(LIBFT) check

.PHONY: all clean fclean re
