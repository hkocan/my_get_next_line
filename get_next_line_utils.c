/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:01:33 by hkocan            #+#    #+#             */
/*   Updated: 2023/11/27 15:50:05 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s2)
		return (NULL);
	while (*s)
		s2[i++] = *s++;
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*new_str;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_str)
		return (NULL);
	while (*s1)
		new_str[i++] = *s1++;
	while (*s2)
		new_str[i++] = *s2++;
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	i;
	size_t	j;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!s || len <= 0)
		return (NULL);
	if (len > s_len)
		len = s_len;
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	i = start;
	j = 0;
	while (i < s_len && j < len)
	{
		tmp[j] = s[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	*ft_free(char **stack, int new_line)
{
	char	*line;

	if (!*stack)
		return (NULL);
	if (new_line == 0)
	{
		if (*stack)
		{
			free(*stack);
			*stack = NULL;
		}
		return (NULL);
	}
	else if (new_line == 1)
	{
		line = ft_strdup(*stack);
		free(*stack);
		*stack = NULL;
		return (line);
	}
	return (NULL);
}
