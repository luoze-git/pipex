NAME		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
INCDIR		= .
INCFLAGS	= -I$(INCDIR)

LIBFT_DIR	= libft
LIBFT_A		= $(LIBFT_DIR)/libft.a
LIBFT_INC	= -I$(LIBFT_DIR)
LIBFT_LINK	= -L$(LIBFT_DIR) -lft

SRCS		= main.c \
			  parser_1_classifier.c \
			  parser_2_cmds.c \
			  parser_3_open.c \
			  pipes.c \
			  pipline.c \
			  pwait.c \
			  error.c \
			  close.c \
			  cleanup.c \
			  utils.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LINK) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCFLAGS) $(LIBFT_INC) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
