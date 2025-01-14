/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 00:12:11 by anammal           #+#    #+#             */
/*   Updated: 2022/10/09 13:04:24 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/**
 * @brief Determines whether a given character is an alphabetic letter or not
 * @param c the ASCII code of character to be examined
 * @return 1 if true, and 0 otherwise
*/
int		ft_isalpha(int c);
/**
 * @brief Determines whether a given character is a digit or not
 * @param c the ASCII code of character to be examined
 * @return 1 if true, and 0 otherwise
*/
int		ft_isdigit(int c);
/**
 * @brief Determines whether a given character is an alphanumeric one or not
 * @param c the ASCII code of character to be examined
 * @return 1 if true, and 0 otherwise
*/
int		ft_isalnum(int c);
/**
 * @brief Determines whether a given integer represents an ASCII character or not
 * @param c the integer to be examined
 * @return 1 if true, and 0 otherwise
*/
int		ft_isascii(int c);
/**
 * @brief Determines whether a given character is a printable ASCII character or not
 * @param c the ASCII code of character to be examined
 * @return 1 if true, and 0 otherwise
*/
int		ft_isprint(int c);
/**
 * @brief Converts a given lowercase letter to its corresponding uppercase letter
 * @param c the ASCII code representing the lowercase letter to convert
 * @return the corresponding uppercase letter,
 * or the original input if it is not a lowercase letter
*/
int		ft_toupper(int c);
/**
 * @brief Converts a given uppercase letter to its corresponding lowercase letter
 * @param c the ASCII code representing the uppercase letter to convert
 * @return the corresponding lowercase letter,
 * or the original input if it is not an uppercase letter
*/
int		ft_tolower(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
void	ft_bzero(void *s, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	*ft_memset(void *b, int c, int len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
// bonus part.
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
