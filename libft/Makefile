# ---- project
NAME    := libft.a

# ---- tools & flags
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -fPIE
AR      := ar
ARFLAGS := rcs
RM      := rm -f

# ---- headers
HDRS    := libft.h
INCLUDES:= -I .

# ---- sources
MSRCS := \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_free_split.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	get_next_line.c \
	get_next_line_utils.c

BSRCS := \
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstsize.c

# ---- derived object lists
MOBJS  := $(MSRCS:.c=.o)
BOBJS := $(BSRCS:.c=.o)
.DEFAULT_GOAL := all
# ---- rules (highlights mandatory ones: all NAME clean fclean re)
.PHONY: all bonus clean fclean re 
# rule 1: all . build the MANDATORY library
all: $(NAME)

$(NAME): $(MOBJS)
	$(AR) $(ARFLAGS) $(NAME) $(MOBJS)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# rule 2: bonus . build the bonus functions into the library
bonus: $(BOBJS) $(NAME)
	$(AR) $(ARFLAGS) $(NAME) $(BOBJS)

# rule 3: clean . clean all object files
clean:
	$(RM) $(MOBJS) $(BOBJS)

# rule 4: fclean . clean all object files and the library
fclean: clean
	$(RM) $(NAME)

# rule 5: re . rebuild the MANDATORY library
re: fclean all