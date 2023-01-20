/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayou <tayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:09:50 by tayou             #+#    #+#             */
/*   Updated: 2023/01/18 02:41:26 by tayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_string(char *str, int *print_count)
{
	int	str_len;

	str_len = my_strlen(str);
	write(1, str, str_len);
	(*print_count) += str_len;
}
	
void	print_character(char c, int *print_count)
{
	write(1, &c, 1);
	(*print_count)++;
}

int	get_hexa_digit(long long number)
{
	int	digit;

	digit = 0;
	while (number != 0)
	{
		number /= 16;
		digit++;
	}
	return (digit);
}

 void	fill_hexa_address(long long number, char *hexa_address, int hexa_digit)
{
	int		i;
	char	*hexa;

	hexa = "0123456789abcdef";
	i = hexa_digit - 1;
	while (number != 0)
	{
		hexa_address[i] = hexa[number % 16];
		number /= 16;
		i--;
	}
	hexa_address[hexa_digit] = '\0';
}

void	print_address(void *address, int *print_count)
{
	long long	number;
	int			hexa_digit;
	char		*hexa_address;

	write(1, "0x", 2);
	(*print_count) += 2;
	if (address == NULL)
	{
		write(1, "0", 1);
		(*print_count)++;
		return ;
	}
	number = (long long) address;
	hexa_digit = get_hexa_digit(number);
	hexa_address = (char *) malloc(sizeof(char) * (hexa_digit) + 1);
	if (hexa_address == 0)
		return ;
	fill_hexa_address(number, hexa_address, hexa_digit);
	write(1, hexa_address, hexa_digit);
	(*print_count) += hexa_digit;
	free(hexa_address);
}

static int	get_digit(long long number)
{
	int	digit;

	digit = 0;
	if (number < 0)
	{
		number *= (-1);
		digit++;
	}
	if (number == 0)
		return (1);
	while (number != 0)
	{
		number /= 10;
		digit++;
	}
	return (digit);
}

static char	*fill_number_array(char *number_array, long long number, int digit)
{
	int	i;

	if (number < 0)
	{
		number *= (-1);
		number_array[0] = '-';
	}
	if (number == 0)
		number_array[0] = '0';
	i = digit - 1;
	while (number != 0)
	{
		number_array[i] = number % 10 + '0';
		number /= 10;
		i--;
	}
	number_array[digit] = '\0';
	return (number_array);
}

void	print_decimal_number(int n, int *print_count)
{
	char		*number_array;
	long long	number;
	int			digit;

	number = (long long) n;	
	digit = get_digit(number);
	number_array = (char *) malloc(sizeof(char) * digit + 1);
	if (number_array == 0)
		return ;
	number_array = fill_number_array(number_array, number, digit);
	write(1, number_array, digit);
	(*print_count) += digit;
	free(number_array);
}

static int	get_digit(unsigned int number)
{
	int	digit;

	digit = 0;
	if (number == 0)
		return (1);
	while (number != 0)
	{
		number /= 10;
		digit++;
	}
	return (digit);
}

static char	*fill_number_array(char *array, unsigned int number, int digit)
{
	int	i;

	if (number == 0)
		array[0] = '0';
	i = digit - 1;
	while (number != 0)
	{
		array[i] = number % 10 + '0';
		number /= 10;
		i--;
	}
	array[digit] = '\0';
	return (array);
}

void	print_unsigned_number(unsigned int number, int *print_count)
{
	char	*array;
	int		digit;

	digit = get_digit(number);
	array = (char *) malloc(sizeof(char) * digit + 1);
	if (array == 0)
		return (0);
	array = fill_number_array(array, number, digit);
	write(1, array, digit);
	(*print_count) += digit;
	free(array);
}

void	check_type(va_list ap, char character, int *print_count)
{
	if (character == 'c')
		print_character(va_arg(ap, int), print_count);
	else if (character == 's')
		print_string(va_arg(ap, char *), print_count);
	else if (character == 'p')
		print_address(va_arg(ap, void *), print_count);
	else if (character == 'd' || character == 'i')
		print_decimal_number(va_arg(ap, int), print_count);
	else if (character == 'u')
		print_unsigned_number(va_arg(ap, unsigned int), print_count);
}

int	ft_printf(const char *str, ...)
{
	int		print_count;
	va_list	ap;
	int		i;

	va_start(ap, str);
	print_count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '%')
		{
			write(1, &str[i], 1);
			print_count++;
			i++;
		}
		else if (str[i] == '%')
		{
			check_type(ap, str[i + 1], &print_count);
			i += 2;
		}
	}	
	return (print_count);
}
