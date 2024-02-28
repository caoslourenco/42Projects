/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clourenc  <clourenc@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:29:01 by clourenc          #+#    #+#             */
/*   Updated: 2022/09/08 15:57:01 by clourenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hexlen(unsigned long int n)
{
	int	lenght;

	// Inicializa a variável "lenght" como 1
	lenght = 1;

	// Enquanto o número for maior ou igual a 16, incrementa o comprimento e divide o número por 16
	while (n >= 16)
	{
		lenght++;
		n = n / 16;
	}
	// Retorna o comprimento calculado
	return (lenght);
}

static char	conversion_ascii(unsigned long int receptor, char id)
{
	// Se o receptor for menor ou igual a 9, retorna o caractere correspondente ao receptor + 48 (caracteres numéricos)
	if (receptor <= 9)
		return (receptor + 48);
	// Se o id for 'l' retorna o caractere correspondente ao receptor + 87 (caracteres minúsculos)
	else if (id == 'l')
		return (receptor + 87);
	// Se o id for 'U' retorna o caractere correspondente ao receptor + 55 (caracteres maiúsculos)
	else if (id == 'U')
		return (receptor + 55);
	// Se o id for 'p' retorna o caractere correspondente ao receptor + 87 (caracteres minúsculos)
	else if (id == 'p')
		return (receptor + 87);
	// Caso contrário, retorna o receptor sem modificação
	return (receptor);
}

int	ft_convert_hex(unsigned long long number, char id)
{
	char				*str;
	int					lenght;
	unsigned long int	mod;

	// Calcula o comprimento da representação hexadecimal do número
	lenght = ft_hexlen (number);

	// Se o id for 'p' e o número for 0, retorna "(nil)"
	if (id == 'p')
	{
		if (number == 0)
			return (ft_printf("(nil)") - 2);
		ft_printf("0x");
	}

	// Aloca memória para a string de representação hexadecimal
	str = (char *) calloc(sizeof(char), (lenght + 1));

	// Se o número for 0, coloca o caractere '0' na string
	if (number == 0)
		str[--lenght] = '0';

	// Enquanto o número for diferente de 0, calcula o resto da divisão por 16 e adiciona o caractere correspondente na string
	while (number != 0)
	{
		mod = (number % 16);
		str[--lenght] = conversion_ascii(mod, id);
		number = number / 16;
	}
	lenght = ft_putstr(str);
	free(str);
	return (lenght);
}

int	handle_argument_format(const char *str, int count, va_list arg)
{
	int	lenght;

	lenght = 0;
	if (str[count] == 'c')
		lenght = ft_putchar(va_arg(arg, int));
	if (str[count] == 's')
		lenght = ft_putstr(va_arg(arg, char *));
	if (str[count] == 'p')
		lenght = ft_convert_hex(va_arg(arg, unsigned long long int), 'p') + 2;
	if (str[count] == 'd')
		lenght = ft_putnbr(va_arg(arg, int));
	if (str[count] == 'i')
		lenght = ft_putnbr(va_arg(arg, int));
	if (str[count] == 'u')
		lenght = ft_putnbr(va_arg(arg, unsigned int));
	if (str[count] == 'x')
		lenght = ft_convert_hex(va_arg(arg, unsigned int), 'l');
	if (str[count] == 'X')
		lenght = ft_convert_hex(va_arg(arg, unsigned int), 'U');
	if (str[count] == '%')
		lenght = ft_putchar('%');
	return (lenght);
}

int	ft_printf(const char *str, ...)
{
	int		count_size;
	int		total_lenght;
	va_list	args;

	total_lenght = 0;
	va_start(args, str);
	count_size = 0;
	while (str[count_size] != '\0')
	{
		if (str[count_size] == '%')
		{
			count_size++;
			total_lenght += handle_argument_format(str, count_size, args);
		}
		else
			total_lenght += ft_putchar(str[count_size]);
		count_size++;
	}
	return (total_lenght);
}
