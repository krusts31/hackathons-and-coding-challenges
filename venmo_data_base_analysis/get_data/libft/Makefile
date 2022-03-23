# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    mf_p1                                              :+:    :+:             #
#                                                      +:+                     #
#    By: mraasvel <mraasvel@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/14 12:06:33 by mraasvel      #+#    #+#                  #
#    Updated: 2020/11/14 12:06:47 by mraasvel      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ft_split_set.c\
ft_strstr.c\
ft_unumlen_base.c\
ft_dbl_tenthpow.c\
lft_gnl.c\
ft_putll.c\
ft_numlen_double.c\
ft_putnofc.c\
ft_putllu.c\
ft_free.c\
put_area_in_bin.c\
ft_putllu_base.c\
ft_isspace.c\
ft_putstr_p.c\
ft_putstr.c\
ft_free_split.c\
ft_numlen_base.c\
ft_join_n_strings.c\
ft_strcmp.c\
ft_split_token.c\
ft_llutoa.c\
ft_pow.c\
ft_strdup.c\
ft_bzero.c\
ft_split.c\
ft_isalnum.c\
ft_putchar_fd.c\
ft_memcmp.c\
ft_calloc.c\
ft_strmapi.c\
ft_isalpha.c\
ft_memcpy.c\
ft_isdigit.c\
ft_memchr.c\
ft_lstmap.c\
ft_atoi.c\
ft_lstclear.c\
ft_lstiter.c\
ft_tolower.c\
ft_lstdelone.c\
ft_lstadd_front.c\
ft_memccpy.c\
ft_memset.c\
ft_lstsize.c\
ft_isprint.c\
ft_substr.c\
ft_putnbr_fd.c\
ft_itoa.c\
ft_isascii.c\
ft_strtrim.c\
ft_putstr_fd.c\
ft_strlcat.c\
ft_lstnew.c\
ft_putendl_fd.c\
ft_strncmp.c\
ft_strnstr.c\
ft_strlcpy.c\
ft_memmove.c\
ft_strrchr.c\
ft_lstadd_back.c\
ft_strjoin.c\
ft_toupper.c\
ft_strchr.c\
ft_strlen.c\
ft_lstlast.c\

OBJ = $(SRC:.c=.o)

# Compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^
%.o: %.c
	$(CC) -o $@ -c $(CFLAGS) $<

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
