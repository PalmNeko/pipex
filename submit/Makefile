
NAME          = pipex
SRCDIR        = .
EXCLUDE_PATH  = */libft/*.c */cident/* */test/* *bonus*.c
EX_PARAGRAPH  = $(foreach path,$(EXCLUDE_PATH),-not -path '$(path)')
SRCS          = $(shell find $(SRCDIR) -name "*.c" $(EX_PARAGRAPH) -type f)
OBJS          = $(SRCS:%.c=%.o)
DEPENDS       = $(OBJS:.o=.d)
CFLAGS        += -Wall -Wextra -Werror -MMD -MP $(addprefix -I,$(LIBS))
LDFLAGS       += $(addprefix -L,$(LIBS))
LDLIBS        += -lft
LIBFT         = libft
LIBS          = $(LIBFT)

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
	git clone git@github.com:PalmNeko/Libft.git $@
	cd $@ && make

-include $(DEPENDS)
