/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clourenc  <clourenc@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:29:01 by clourenc          #+#    #+#             */
/*   Updated: 2022/09/07 20:56:51 by clourenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	// Escreve um caractere dado para a saída padrão
	write(1, &c, 1);
	// Retorna 1, indicando que um caractere foi escrito
	return (1);
}

static void	handle_int(int i)
{
	char	c;
	// Inicializa 'c' como '0'
	c = '0';
	// Adiciona o valor de i a 'c' para que 'c' contenha o caractere correspondente ao dígito
	c = c + i;
	// Escreve o caractere para a saída padrão
	write(1, &c, 1);
}

int	ft_putnbr(long int n)
{
	long int	i;
	int			length;
	// Inicializa 'i' como 1 e 'length' como 1
	i = 1;
	length = 1;
	// Verifica se o número é igual a -2147483648, que é o número mínimo representável por um inteiro,
	// e se for, usa ft_printf para imprimir "-2147483648"
	if (n == -2147483648)
		return (ft_printf("-2147483648"));
	// Se o número for negativo, escreve o sinal negativo e transforma o número em positivo
	if (n < 0)
	{
		ft_putchar('-');
		n = n * -1;
		length = length + 1;
	}
	// Encontra a potência de dez mais próxima do número
	while (i <= n / 10)
	{
		i = i * 10;
		length++;
	}
	// Escreve cada dígito do número
	while (i >= 1)
	{
		handle_int(n / i);
		n = n - (n / i) * i;
		i = i / 10;
	}
	// Retorna o número de caracteres escritos
	return (length);
}

int	ft_putstr(char *s)
{	
	int	count_size;
	// Se a string for nula, imprime "(null)" e retorna 6
	if (!s)
	{
		ft_putstr("(null)");
		return (6);
	}
	count_size = 0;
	// Escreve cada caractere da string
	while (s[count_size] != '\0')
	{
		write (1, &s[count_size], 1);
		count_size++;
	}
	// Retorna o número de caracteres escritos
	return (count_size);
}
