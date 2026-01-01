/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:25:28 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/01 17:10:14 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdint.h> // For SIZE_MAX
# include <stdlib.h> // For size_t, malloc, free
# include <unistd.h> // For write

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_join_vars
{
	int				i;
	int				j;
	int				len_hd;
	int				len_tl;
}					t_join_vars;

void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s);

int					ft_atoi(const char *str);
char				*ft_itoa(int n);

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);

int					ft_toupper(int c);
int					ft_tolower(int c);

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);

void				*ft_memmove(void *dst, const void *src, size_t len);

char				**ft_split(char const *s, char c);

void				ft_free_split(char **split);

char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

size_t				ft_strlen(const char *s);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);

t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
// get_next_line.c
void				*reset_return_null(char **pending_content);
char				*reading_loop_body_of_get_next_line(char **pending,
						char *hd_stat, int fd);
char				*get_next_line(int fd);

// get_next_line_utils.c
char				*gnl_has_newline(char *buf_terminated);
void				ft_init_t_join_vars(t_join_vars *t, char *hd, char *tl,
						char sep);
char				*gnl_join(char *hd, char *tl, char sep);
void				ft_update_static_array(char *stat, char *s);
int					ft_strlen_sep(char *s, char sep);
#endif