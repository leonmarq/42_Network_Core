/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 13:40:14 by lmarquar          #+#    #+#             */
/*   Updated: 2026/03/17 09:31:24 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct b_list
{
	char			*set;
	char			*setnocp;
	char			*setnb;
	char			*sraw;
	char			*s;
	char			type;
	int				minus;
	int				nul;
	int				nbr;
	int				precision;
	struct b_list	*next;
}		x_list;

int		ft_printf(const char *format, ...);
x_list	*emptylist(void);
int		filllist(x_list *list, const char *format, va_list args);
char	*ft_strdup(const char *s);
int		strtonb(const char *s, int *i);
int		findchr(const char *s, int i, char *set);
int		findchrchr(char c, char *set);
char	*createstr(va_list args, char c);
char	*nbtostr(long long n);
void	*ft_calloc(size_t nmemb, size_t size);
int		completelist(x_list *list);
int		dividecount(long long nb);

#endif
