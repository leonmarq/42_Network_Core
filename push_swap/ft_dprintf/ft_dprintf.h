/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 13:40:14 by lmarquar          #+#    #+#             */
/*   Updated: 2026/03/22 16:03:45 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H
# include "libft/libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

# define PF_SET_ALL   "cspdiuxX%"
# define PF_SET_NO_CP "sdiuxX"
# define PF_SET_NB    "diuxX%"

typedef struct b_list
{
	char			*sraw;
	char			*s;
	char			type;
	int				minus;
	int				nul;
	int				formatted_len;
	int				precision;
	struct b_list	*next;
}		t_plist;

char	*tobighex(unsigned long decnum);
char	*tosmallhex(unsigned long decnum);
int		ft_dprintf(const char *format, ...);
t_plist	*emptylist(void);
int		filllist(t_plist *list, const char *format, va_list args);
char	*ft_strdup(const char *s);
int		strtonb(const char *s, int *i);
int		findchr(const char *s, int i, char *set);
int		findchrchr(char c, char *set);
char	*createstr(va_list args, char c);
char	*nbtostr(long long n);
void	*ft_calloc(size_t nmemb, size_t size);
int		completelist(t_plist *list);
int		dividecount(long long nb);

#endif
