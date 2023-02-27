#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

int				ft_atol(const char *nptr, long *v);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
char			*ft_itoa(int n);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strchr(const char *str, int c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strjoin(char const *s1, char const *s2);
unsigned int	ft_strlcpy(char *dst, const char *src, unsigned int size);
int				ft_strlen(const char *s);
char			*ft_substr(char *s, int n);
char			*ft_strdup(char *str);

#endif