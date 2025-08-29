/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:43:01 by wxi               #+#    #+#             */
/*   Updated: 2025/08/29 15:58:44 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_bzero(void *s, size_t n)
{
	size_t				i;
	unsigned char		*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

// int	main(void)
// {
// 	unsigned char	ptr[5];
// 	int				i;
// 	int				n;

// 	i = 0;
// 	n = 10;
// 	bzero(ptr, n);
// 	while(i < n)
// 	{
// 		printf("%d", ptr[i]);
// 		i++;
// 	}
// 	return (0);
// }
