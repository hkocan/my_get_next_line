/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:01:58 by hkocan            #+#    #+#             */
/*   Updated: 2023/11/27 15:39:56 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static char	*ft_addbuf(char *stack, char *buf)
{
	char	*tmp;

	tmp = 0;
	if (!stack && buf)
	{
		tmp = ft_strdup(buf);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	tmp = ft_strjoin(stack, buf);
	ft_free(&stack, 0);
	return (tmp);
}

static int	ft_checknl(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_get_line(char *stack)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!stack)
		return (0);
	while (stack[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (0);
	while (j < i + 1)
	{
		line[j] = stack[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*ft_new_line(char *stack)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (!stack)
		return (NULL);
	while (stack[i] != '\n')
		i++;
	if (stack[i + 1] == '\0')
		return (ft_free(&stack, 0));
	tmp = ft_substr(stack, i + 1, ft_strlen(stack));
	if (!tmp)
	{
		ft_free(&stack, 0);
		return (NULL);
	}
	ft_free(&stack, 0);
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	long		rd_bytes;
	char		*line;
	static char	*stack = NULL;

	line = 0;
	rd_bytes = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free(&stack, 0));
	while (rd_bytes > 0)
	{
		rd_bytes = read(fd, buf, BUFFER_SIZE);
		if ((rd_bytes <= 0 && !stack) || rd_bytes == -1)
			return (ft_free(&stack, 0));
		buf[rd_bytes] = '\0';
		stack = ft_addbuf(stack, buf);
		if (ft_checknl(stack))
		{
			line = ft_get_line(stack);
			if (!line)
				return (ft_free(&stack, 0));
			return (stack = ft_new_line(stack), line);
		}
	}
	return (ft_free(&stack, 1));
}
