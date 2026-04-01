/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamercha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 23:30:29 by gamercha          #+#    #+#             */
/*   Updated: 2026/01/28 23:30:32 by gamercha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = read_and_storage(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = update_stash(stash, line);
	return (line);
}

char	*read_and_stash(int fd, char *stash)
{
	int		bytes;
	char	*buff;

	buff = malloc(BUFFER_SIZE + 1);
	if (buff == NULL)
		return (free(stash), stash = NULL, NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buff), free(stash), NULL);
		if (bytes == 0)
			break ;
		buff[bytes] = '\0';
		stash = stash_join(stash, buff);
		if (!stash)
			return (free(buff), NULL);
		if (find_n(stash) == 1)
			break ;
	}
	free(buff);
	return (stash);
}

char	*stash_join(char *stash, char *buff)
{
	char	*tmp;

	if (!stash)
		return (ft_strdup(buff));
	tmp = ft_strjoin(stash, buff);
	if (!tmp)
		return (free(stash), NULL);
	free(stash);
	return (tmp);
}

char	*read_and_storage(char *stash)
{
	int		i;
	char	*b_line;
	int		cont;

	cont = 0;
	i = 0;
	if (!stash || stash[0] == '\0')
		return (NULL);
	while (stash[cont] && stash[cont] != DELIMITER)
		cont++;
	if (stash[cont] == DELIMITER)
		cont++;
	b_line = malloc(cont + 1);
	if (b_line == NULL)
		return (NULL);
	while (i < cont)
	{
		b_line[i] = stash[i];
		i++;
	}
	b_line[i] = '\0';
	return (b_line);
}

char	*update_stash(char *stash, char *line)
{
	int		len;
	int		stash_len;
	char	*new_stash;

	if (!line || !stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash_len = ft_strlen(stash);
	len = ft_strlen(line);
	if (len >= stash_len)
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_substr(stash, len, stash_len - len);
	free(stash);
	return (new_stash);
}
// # include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		printf("Error!!");
// 		return (1);
// 	}
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }
