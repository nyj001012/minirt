/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:38:31 by yena              #+#    #+#             */
/*   Updated: 2023/07/19 16:09:22 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static size_t	word_cnt(const char *s, char c)
{
	size_t	cnt;

	if (s == 0)
		return (0);
	cnt = 0;
	while (*s != 0 && *s != '\n')
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == 0 || *(s + 1) == '\n'))
			cnt++;
		s++;
	}
	return (cnt);
}

static size_t	word_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (*(s + len) != c && *(s + len) != 0 && *(s + len) != '\n')
		len++;
	return (len);
}

char	**free_front(char **arr, size_t idx)
{
	size_t	i;

	i = 0;
	while (idx > i)
	{
		free(*(arr + i));
		i++;
	}
	free(arr);
	return (NULL);
}

char	**split_line(char const *s, char c)
{
	char	**str_arr;
	size_t	idx;
	size_t	w_num;
	size_t	w_len;

	w_num = word_cnt(s, c);
	str_arr = (char **)malloc(sizeof(char *) * (w_num + 1));
	if (str_arr == NULL)
		return (NULL);
	idx = 0;
	while (w_num > 0)
	{
		while (*s == c)
			s++;
		w_len = word_len(s, c);
		*(str_arr + idx) = ft_substr(s, 0, w_len);
		if (*(str_arr + idx) == NULL)
			return (free_front(str_arr, idx));
		s += w_len;
		idx++;
		w_num--;
	}
	*(str_arr + idx) = 0;
	return (str_arr);
}
