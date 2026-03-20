/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kghesqui <kghesqui@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:14:23 by kghesqui          #+#    #+#             */
/*   Updated: 2026/02/02 15:14:23 by kghesqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_check(char *tmp, char *buffer)
{
	char	*keep_tmp;
	int		len;

	len = 0;
	keep_tmp = NULL;
	if (tmp)
	{
		keep_tmp = ft_strdup(tmp);
		if (!keep_tmp)
			return (free(tmp), NULL);
		free(tmp);
		len = ft_strlen(keep_tmp) + ft_strlen(buffer);
		tmp = (char *)malloc(len + 1);
		if (tmp == NULL)
			return (free(keep_tmp), NULL);
		ft_memcpy(tmp, keep_tmp, ft_strlen(keep_tmp));
		ft_memcpy(tmp + ft_strlen(keep_tmp), buffer, ft_strlen(buffer));
		tmp[len] = '\0';
		free(keep_tmp);
	}
	else if (!tmp)
		tmp = ft_strdup(buffer);
	return (tmp);
}

void	ft_extract(char **ptr)
{
	char	*keep_tmp;

	keep_tmp = ft_strdup(ft_strchr(*ptr, '\n') + 1);
	free(*ptr);
	*ptr = keep_tmp;
}

char	*ft_free(char **ptr_tmp, char **ptr_buffer, ssize_t b)
{
	char	*line;

	line = NULL;
	(void)ptr_buffer;
	if (*ptr_tmp && **ptr_tmp && b == 0)
	{
		line = ft_strdup(*ptr_tmp);
		free(*ptr_tmp);
		*ptr_tmp = NULL;
		return (line);
	}
	if (*ptr_tmp && ft_strchr(*ptr_tmp, '\n'))
	{
		line = ft_substr(*ptr_tmp, 0, (ft_strlen(*ptr_tmp)
					- ft_strlen(ft_strchr(*ptr_tmp, '\n'))) + 1);
		ft_extract(ptr_tmp);
		return (line);
	}
	free(*ptr_tmp);
	*ptr_tmp = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*buffer;
	ssize_t		read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0)
	{
		if (tmp && ft_strchr(tmp, '\n'))
			return (ft_free(&tmp, NULL, 1));
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (free(tmp), tmp = NULL, NULL);
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(buffer), free(tmp), tmp = NULL, NULL);
		buffer[read_bytes] = '\0';
		tmp = ft_check(tmp, buffer);
		free(buffer);
		if (!tmp || read_bytes == 0)
			break ;
	}
	return (ft_free(&tmp, NULL, 0));
}
/*int	main(void)
{
	int	fd = 0;
	char *string = NULL;


	fd = open("test_normal.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Erreur d'ouverture du fichier\n");
		return (1);
	}
	string = get_next_line(fd);
	while (string != NULL)
	{
		printf("%s", string);
		string = get_next_line(fd);
	}
	return (0);
}*/
