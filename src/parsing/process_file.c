/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:52:02 by jihyeole          #+#    #+#             */
/*   Updated: 2023/07/05 02:52:41 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	is_valid_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 3 || ft_strncmp(&filename[len - 3], ".rt", 3) != 0)
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
		exit(1);
	}
}

void	process_file(char *filename)
{
	int		fd;
	char	*line;

	is_valid_filename(filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nopen");
		exit(1);
	}
	// line = get_next_line(fd);
	// while (line)
	// {
	// 	line = get_next_line(fd);
	// }
	close(fd);
}