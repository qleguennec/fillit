# Directories
BINDIR		?=	.
SRCDIR		?=	src
BUILDDIR	?=	build
LIBDIR		?=	$(BUILDDIR)
DEPSDIR		?=	lib
INCLUDE		+=	includes
INCLUDE		+=	$(addprefix $(DEPSDIR)/,$(addsuffix /includes,$(LIBSRC)))
NAME		=	fillit
TARGET		=	$(BINDIR)/$(NAME)

# Compiler options
CC			=	clang
LIBFLAGS	=	$(subst lib,-l,$(LIBSRC))
CFLAGS		=	$(addprefix -I,$(INCLUDE)) -Wall -Wextra -Werror -g

# Color output
BLACK		=	"\033[0;30m"
RED			=	"\033[0;31m"
GREEN		=	"\033[0;32m"
YELLOW		=	"\033[1;33m"
BLUE		=	"\033[0;34m"
MAGENTA		=	"\033[0;35m"
CYAN		=	"\033[0;36m"
WHITE		=	"\033[0;37m"
END			=	"\033[0m"

# Source files
SRC			+=	io.c
SRC			+=	list.c
SRC			+=	main.c
SRC			+=	math.c
SRC			+=	play.c
SRC			+=	validation.c

# Libraries
LIBSRC		=	libft

OBJECTS		=	$(addprefix $(BUILDDIR)/, $(SRC:%.c=%.o))
LIBS		=	$(addprefix $(LIBDIR)/, $(addsuffix .a,$(LIBSRC)))

all: deps $(TARGET)
$(NAME): $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@[ -d $(BUILDDIR) ] || mkdir $(BUILDDIR); true
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(GREEN)+++ obj:'\t'$(END)$(BUILDDIR)/$(YELLOW)'\t'$(@F)$(END)

$(LIBDIR)/%.a: $(DEPSDIR)/%
	@[ -d $(BUILDDIR)/$* ] || mkdir -p $(BUILDDIR)/$*; true
	@										\
		DEPSDIR=$(CURDIR)/$(DEPSDIR)		\
		BINDIR=$(CURDIR)/$(BUILDDIR)		\
		BUILDDIR=$(CURDIR)/$(BUILDDIR)/$*	\
		LIBDIR=$(CURDIR)/$(LIBDIR)			\
		make -s -C $< > /dev/null
	@echo $(GREEN)+++ static lib:'\t'$(END)$(LIBDIR)/'\t'$(CYAN)$(@F)$(END)

$(TARGET): $(OBJECTS) $(LIBS)
	@$(CC) $(CFLAGS) -L$(BUILDDIR) $(OBJECTS) $(LIBFLAGS) -o $@
	@echo $(GREEN)+++ target:'\t'$(END)$(BINDIR)/'\t'$(BLUE)$(NAME)$(END)

$(DEPSDIR)/%:
	@git clone http://github.com/qleguennec/$(@F).git $@
	@make -s -C $@ purge

.PHONY: clean fclean re deps clean-deps re-deps test rendu purge get-%

clean:
	@rm $(LIBS) 2> /dev/null &&	\
	echo $(RED)--- static lib:'\t'$(END)$(LIBDIR)/'\t'$(CYAN)$(LIBS:$(LIBDIR)/%.a=%.a); true
	@rm $(OBJECTS) 2> /dev/null	\
	&& echo $(RED)--- obj:'\t'$(END)$(BUILDDIR)/'\t'$(YELLOW)$(OBJECTS:$(BUILDDIR)/%=%)$(END); true

fclean: clean
	@[ -f $(TARGET) ] && rm $(TARGET) \
	&& echo $(RED)--- target:'\t'$(END)$(BINDIR)/'\t'$(BLUE)$(NAME)$(END); true

re: fclean all

deps: $(addprefix $(DEPSDIR)/, $(LIBSRC))

clean-deps:
	@rm -rf $(DEPSDIR)

re-deps: clean-deps deps

test:
	@test/test.sh $(ARGS)
	@test/test-functions-used.sh

rendu:
	@util/rendu.sh

purge:
	@util/purge.sh

get-%:
	@echo '$($*)'
