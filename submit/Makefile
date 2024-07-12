
NAME          = pipex
SRCDIR        = .
SRCS          = \
	./px_print_error.c \
	./px_perrinfo.c \
	./px_perror_cmd_not_found.c \
	./px_errexit_child.c \
	./px_wait_termed.c \
	./px_destroy_pcmd.c \
	./px_new_pcmd.c \
	./px_generate_heredoc_unlinked_fd.c \
	./px_gen_pcmd_for_heredoc.c \
	./px_free_pcmd_array.c \
	./px_gen_pcmd_for_file.c \
	./px_errinfo.c \
	./px_execve.c \
	./px_resolve_command_path.c \
	./free_termed_null.c \
	./px_close_pipe.c \
	./px_fork_for_pipe.c \
	./main.c \
	./px_fork_all_pcmd.c \
	./px_main.c \
	./px_error.c \
	./px_is_permission_error.c \
	./px_is_not_exists.c
OBJS          = $(SRCS:%.c=%.o)
DEPENDS       = $(OBJS:.o=.d)
CFLAGS        += -Wall -Wextra -Werror -MMD -MP $(addprefix -I,$(LIBS))
LDFLAGS       += $(addprefix -L,$(LIBS))
LDLIBS        += -lft
LIBFT         = libft
LIBS          = $(LIBFT)

all: $(LIBFT)/$(LIBFT).a $(NAME) bonus

clean:
	make -f .bonus.mk clean
	make -C libft clean
	rm -f $(OBJS) $(DEPENDS)
	rm -rf $(MLX_DIR)

fclean: clean
	make -f .bonus.mk fclean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

show:
	@printf "NAME  		: $(NAME)\n"
	@printf "CC		    : $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "LDLIBS		: $(LDLIBS)\n"
	@printf "SRCS		:\n	$(SRCS)\n"
	@printf "OBJS		:\n	$(OBJS)\n"

debug: CFLAGS  += -g -O0 -fsanitize=leak
debug: LDFLAGS += -g -O0 -fsanitize=leak
debug: re

.PHONY: all

$(NAME): $(LIBFT)/$(LIBFT).a $(OBJS)
	make -C $(LIBFT)
	$(LINK.o) $(OBJS) $(LOADLIBES) $(LDLIBS) -o $@

.PHONY: bonus
bonus:
	make -f .bonus.mk bonus

$(LIBFT)/$(LIBFT).a: $(LIBFT)
	make -C $(LIBFT)

$(LIBFT):
	git clone git@github.com:PalmNeko/Libft.git $(LIBFT)

-include $(DEPENDS)
