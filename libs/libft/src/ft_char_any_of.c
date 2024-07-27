/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_any_of.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:59:01 by damateos          #+#    #+#             */
/*   Updated: 2024/07/27 14:59:30 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char_any_of(char target, int num_args, ...)
{
	va_list	args;
	char	current;
	int		i;

	va_start(args, num_args);
	i = 0;
	while (i < num_args)
	{
		current = va_arg(args, int);
		if (target == current)
		{
			va_end(args);
			return (1);
		}
		i++;
	}
	va_end(args);
	return (0);
}
