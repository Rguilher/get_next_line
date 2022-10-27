/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguilher <rguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 01:41:27 by rguilher          #+#    #+#             */
/*   Updated: 2022/10/26 23:36:30 by rguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
			* sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}

static char	*get_line(int fd, char *storage, char *buffer)
{
	int		n_bytes;
	char	*temp;

	n_bytes = 1;
	while (1)
	{
		n_bytes = read(fd, buffer, BUFFER_SIZE);
		if (n_bytes == -1)
			return (NULL);
		else if (n_bytes == 0)
			break ;
		buffer[n_bytes] = '\0';
		if (!storage)
			storage = ft_strdup("");
		temp = storage;
		storage = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(storage, '\n'))
			break ;
	}
	return (storage);
}

static char	*separete_line(char *line)
{
	int		i;
	char	*rest_to_storage;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	rest_to_storage = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*rest_to_storage == '\0')
	{
		free(rest_to_storage);
		rest_to_storage = NULL;
	}
	line[i + 1] = '\0';
	return (rest_to_storage);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*storage[FD_BUFFER];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = get_line(fd, storage[fd], buffer);
	free(buffer);
	if (!line)
		return (line);
	storage[fd] = separete_line(line);
	return (line);
}
