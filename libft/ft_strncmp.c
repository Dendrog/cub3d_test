/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:18:04 by jakim             #+#    #+#             */
/*   Updated: 2024/03/12 17:38:09 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n)
	{
		if (*s1 == 0 && *s2 != 0)
			return (0 - (int)(unsigned char)(*s2));
		if (*s1 != 0 && *s2 == 0)
			return ((int)(unsigned char)*s1);
		if (*s1 == 0 && *s2 == 0)
			return (0);
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((int)((unsigned char)*s1 - (unsigned char)*s2));
		s1++;
		s2++;
		n--;
	}
	return (0);
}
