/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayou <tayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:27:20 by tayou             #+#    #+#             */
/*   Updated: 2023/01/16 00:45:05 by tayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int	main(void)
{
	char	*name;
	void	*address;
	int		number;
	int		return_printf;
	int		return_ft_printf;

	name = "Tom";
	address = name;
	number = -2147483648;
	return_printf = printf("name: %s, address: %p, number: %i\n", name, address, number);
	return_ft_printf = ft_printf("name: %s, address: %p, number: %i\n", name, address, number);

	printf("return_printf: %d\n", return_printf);
	printf("return_ft_printf: %d\n", return_ft_printf);

	return (0);
}
