# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/25 17:44:49 by qle-guen          #+#    #+#              #
#*   Updated: 2016/01/29 12:32:03 by qle-guen         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

# Directories
BINDIR	=	.
SRCDIR	=	src
OBJDIR	=	obj
LIBDIR	=	lib
INCLUDE	=	include
NAME	=	fillit
TARGET	=	$(BINDIR)/$(NAME)

# Compiler options
CC		=	clang
CFLAGS	=	-I$(INCLUDE) -Wall -Wextra -Werror -g


# Source files
SRC += main.c
SRC += io.c
SRC += play.c
SRC += math.c

OBJECTS=$(addprefix $(OBJDIR)/, $(subst .c,.o,$(SRC)))

all: $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJECTS) -L$(LIBDIR) -lft

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(TARGET)

.PHONY: re
re: fclean all

.PHONY: test
test:
	@make -C test/ f
