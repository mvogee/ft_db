/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:32:11 by bpatel            #+#    #+#             */
/*   Updated: 2016/11/29 13:43:33 by bpatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/libft.h"
#include <unistd.h>
#include <stdio.h>

/*
**							Warning 
**			Function does not work correctly with initial delim data
**			ex char *string = (,,data3,data4,data5)
**	count the number of words in the string. Allocate space for the num of words
**	count the num of letters in each word -> allocate space
*/

static int	ft_countw(char const *string, char c)
{
	size_t	num_words;
	int		pointer;

	pointer = 1;
	num_words = 1;
	while (*string)
	{
		if ((*string == c))
			num_words++;
		string++;
	}
	return (num_words);
}

char		**ft_strdelim(const char *s, char c)
{
	size_t	word;
	size_t	num_words;
	char	**words;
	char	*iter;

	if (!s)
		return (0);
	num_words = ft_countw(s, c);
	words = (char **)ft_memalloc(sizeof(char*) * (num_words + 1));
	if (!words)
		return (NULL);
	word = 0;
	while (word < num_words)
	{
		if (s[0] == c)
			s++;
		iter = ft_strchr(s, c);
		if (iter)
			words[word] = (s[1] == c) ? ft_strdup(" ") : ft_strsub(s, 0, iter - s);
		else
			words[word] = ft_strdup(s);
		s = iter;
		++word;
	}
	return (words);
}
