/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 00:07:01 by nathan            #+#    #+#             */
/*   Updated: 2023/04/04 00:07:02 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_new_left_str(char *kalan)
{
	int		i;
	int		j;
	char	*str2;

	i = 0;
	while (kalan[i] && kalan[i] != '\n')
		i++;
	if (!kalan[i])
	{
		free(kalan);
		return (NULL);
	}
	str2 = (char *)malloc(sizeof(char) * (ft_strlen(kalan) - i + 1));
	if (!str2)
		return (NULL);
	i++;
	j = 0;
	while (kalan[i])
		str2[j++] = kalan[i++];
	str2[j] = '\0';
	free(kalan);
	return (str2);
}

char	*ft_get_line(char *kalan)
{
	int		i;
	char	*str1;

	i = 0;
	if (!kalan[i])
		return (NULL);
	while (kalan[i] && kalan[i] != '\n')
		i++;
	str1 = (char *)malloc(sizeof(char) * (i + 2));
	if (!str1)
		return (NULL);
	i = 0;
	while (kalan[i] && kalan[i] != '\n')
	{
		str1[i] = kalan[i];
		i++;
	}
	if (kalan[i] == '\n')
	{
		str1[i] = kalan[i];
		i++;
	}
	str1[i] = '\0';
	return (str1);
}

char	*ft_read_to_left_str(int fd, char *left_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(left_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		left_str = ft_strjoin(left_str,buff);
	}
	free(buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*kalan;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	kalan = ft_read_to_left_str(fd, kalan);
	if (!kalan)
		return (NULL);
	line = ft_get_line(kalan);
	kalan = ft_new_left_str(kalan);
	return (line);
}
