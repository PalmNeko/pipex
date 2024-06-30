
NAME          = bonus
SRCDIR        = .
EXCLUDE_PATH  = "*/libft/*.c" "*/cident/*" "*/test/*"
SRCS          = $(shell find $(SRCDIR) -name "*.c" $(addprefix -not -path, $(EXCLUDE_PATH)) -type f)
OBJS          = $(SRCS:%.c=%.o)
DEPENDS       = $(OBJS:.o=.d)
CFLAGS        += -Wall -Wextra -Werror -MMD -MP -O3 $(addprefix -I,$(LIBS))
LDFLAGS       += $(addprefix -L,$(LIBS))
LDLIBS        += -lft

all: $(NAME)

clean:
	rm -f $(OBJS) $(DEPENDS)
	rm -rf $(MLX_DIR)

fclean: clean
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

$(NAME): $(LIBFT) $(OBJS)
	$(LINK.o) $(OBJS) $(LOADLIBES) $(LDLIBS) -o $@

bonus:
	make -C .bonus.mk

$(LIBFT):
	bash -c "$(curl https://raw.githubusercontent.com/PalmNeko/Libft/main/install.sh)"

LIBFT         = libft
LIBS          = $(LIBFT)

-include $(DEPENDS)
