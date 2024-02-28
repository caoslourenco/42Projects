/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clourenc  <clourenc@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:23:24 by clourenc          #+#    #+#             */
/*   Updated: 2022/09/08 16:09:34 by clourenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(const char *str, ...); 
// ///Essa é a função principal ft_printf, 
// que é uma implementação da função printf do C.
//  Ela recebe uma string formatada e argumentos 
//  adicionais, e escreve a saída formatada para a saída padrão.//

int		handle_argument_format(const char *str, int count, va_list arg);
// Essa função handle_argument_format é responsável por processar os argumentos
//  de acordo com o formato especificado na string de formato. 
// Ela recebe a string de formato, uma contagem de caracteres e um argumento va_list.

int		ft_convert_hex(unsigned long long number, char id);
// é usada para converter um número dado para sua representação hexadecimal. Ela recebe 
// o número a ser convertido e uma identificação (id) para indicar se o número deve 
// ser convertido para hexadecimal minúsculo ou maiúsculo

int		ft_strlen(const char *str);
// Essa função ft_strlen retorna o comprimento de uma string dada.

int		ft_putchar(char c);
// Essa função ft_putchar escreve um caractere dado para a saída padrão e retorna 1, indicando que um caractere foi escrito

int		ft_putnbr(long int n);
// Essa função ft_putnbr escreve um número inteiro dado para a saída padrão e retorna o número de caracteres escritos

int		ft_putstr(char *s);
// Essa função ft_putstr escreve uma string dada para a saída padrão e retorna o número de caracteres escritos

#endif
