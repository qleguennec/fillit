# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/25 17:44:49 by qle-guen          #+#    #+#              #
#*   Updated: 2016/03/18 11:39:20 by qle-guen         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

# Directories
BINDIR		=	.
SRCDIR		=	src
BUILDDIR	=	build
LIBDIR		=	lib
INCLUDE		=	include
NAME		=	fillit
TARGET		=	$(BINDIR)/$(NAME)

# Compiler options
CC			=	clang
LIBFLAGS	=	-L$(BUILDDIR) $(subst lib,-l,$(LIBSRC))
CFLAGS		=	-I$(INCLUDE) -Wall -Wextra -Werror -g

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
SRC			+=	main.c
SRC			+=	io.c
SRC			+=	play.c
SRC			+=	math.c
SRC			+=	validation.c
SRC			+=	list.c

# Libraries
LIBSRC		+=	libft

OBJECTS		=	$(addprefix $(BUILDDIR)/, $(SRC:%.c=%.o))
LIBS		=	$(addprefix $(BUILDDIR)/, $(addsuffix .a,$(LIBSRC)))

all: $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(BUILDDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(GREEN)+++ obj: $(YELLOW)$(@F)$(END)

$(BUILDDIR)/%.a: $(LIBDIR)/% $(BUILDDIR)
	@make -s -C $<
	@cp $</$(@F) $@
	@echo $(GREEN)+++ lib: $(CYAN)$(@F)$(END)

$(TARGET): $(LIBS) $(OBJECTS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFLAGS)
	@echo $(GREEN)+++ bin: $(BLUE)$(NAME)$(END)

$(BUILDDIR):
	@mkdir build/

.PHONY: clean
clean:
	@rm -f $(LIBS)
	@echo $(RED)--- lib: $(CYAN)$(LIBS:$(BUILDDIR)/%=%)$(END)
	@rm -f $(OBJECTS)
	@echo $(RED)--- obj: $(YELLOW)$(OBJECTS:$(BUILDDIR)/%=%)$(END)
	@rm -rf build/

.PHONY:	fclean
fclean: clean
	@rm -f $(TARGET)
	@echo $(RED)--- bin: $(BLUE)$(NAME)$(END)

.PHONY: re
re: fclean all

.PHONY: pull-libft
pull-libft:
	@git clone http://github.com/qleguennec/libft.git lib/libft

.PHONY: test
test: $(TARGET)
	@test/test.sh $(ARGS)
