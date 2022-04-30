/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:05:05 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/30 19:05:07 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

static void	free_read_vars(t_read_info *info)
{
	free(info->mem_space);
	info->buff = NULL;
	info->mem_space = NULL;
}

char	*read_line(int fd)
{
	static t_read_info	info;

	info.line = NULL;
	if (!info.buff)
	{
		info.mem_space = ft_xalloc(BUFFSIZE);
		info.buff = info.mem_space;
		info.nb_bytes_read = read(fd, info.buff, BUFFSIZE);
	}
	else
		info.nb_bytes_read = ft_strlen(info.buff);
	if (info.nb_bytes_read > 0)
	{
		info.line_len = strlen_c(info.buff, '\n');
		if (info.line_len <= 0)
			info.line_len = ft_strlen(info.buff);
		info.line = ft_xalloc(info.line_len * sizeof(char));
		info.line = ft_strncpy(info.line, info.buff, info.line_len);
		info.buff += info.line_len;
		if (info.line_len == info.nb_bytes_read)
			free_read_vars(&info);
		return (info.line);
	}
	free_read_vars(&info);
	return (NULL);
}
