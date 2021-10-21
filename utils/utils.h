/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <maearly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 19:58:18 by maearly           #+#    #+#             */
/*   Updated: 2021/04/29 19:19:00 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define BUFFER_SIZE 64

typedef struct s_node
{
	char			*line;
	struct s_node	*next;

}					t_node;

typedef struct s_list
{
	int		i;
	t_node	*first;
	t_node	*tail;

}			t_list;

typedef struct s_split_next
{
	size_t	start;
	size_t	length;
}				t_split_next;

void		*ft_calloc(size_t count, size_t size);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s1);
void		ft_bzero(void *s, size_t n);
size_t		ft_strlen(const char *s);
int			get_next_line(int fd, char **line);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strchr(const char *s, int c);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_atoi(const char *str);
int			list_manager(t_list *list, char *line);
int			create_rgb(int r, int g, int b);

#endif
