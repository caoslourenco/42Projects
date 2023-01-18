/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clourenc  <clourenc@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:32:15 by clourenc          #+#    #+#             */
/*   Updated: 2023/01/13 14:23:59 by clourenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// usada para liberar a memória alocada para um array de strings. 
// Ela percorre o array usando um contador e libera a memória de cada elemento individualmente.
//  Em seguida, a memória alocada para o array é liberada. 
// Isso é importante para evitar vazamentos de memória no programa 
void	free_all(char **access)
{
    int	i; // contador

    i = -1; // inicializa o contador com -1
    while (access [++i]) // enquanto houver elementos no array
        free(access [i]); // libera a memória alocada para cada elemento
    free(access); // libera a memória alocada para o array
}
----------------------------------------------------------------------------------
//  usada para lidar com erros durante a execução do programa.
//  Ela escreve a mensagem de erro no stderr, libera a memória 
// alocada para o array de strings e finaliza o programa com o 
// código de saída especificado. Isso é útil para evitar a 
// necessidade de escrever o mesmo código para lidar com erros 
// em vários pontos do programa e garantir que a memória seja liberada corretamente.

void	error_handler(char **access, int exitcode)

{
    perror("Error: "); // escreve a mensagem de erro no stderr
    free_all(access); // libera a memória alocada para o array
    exit(exitcode); // finaliza o programa com o código de saída especificado
}
--------------------------------------------------------------------------------------
// essa função contar a quantidade de vezes que um determinado 
// caractere aparece em uma string. Ela usa um contador para
//  percorrer a string de trás para frente e um outro contador
//  para contar a quantidade de caracteres encontrados. 
// Ao final, a função retorna o número de caracteres encontrados.
int	count_char_in_string(char *str, int c)
{
    int	i; // contador
    int	j; // contador de caracteres encontrados

    j = 0; // inicializa o contador de caracteres encontrados com 0
    i = ft_strlen(str); // obtém o tamanho da string
    while (i > -1) // enquanto o contador for maior que -1
    {
        if (str[i] == (unsigned char)c) // se o caractere na posição i for igual ao caractere procurado
            j++; // incrementa o contador de caracteres encontrados
        i--; // decrementa o contador
    }
    return (j); // retorna o número de caracteres encontrados
}
-----------------------------------------------------------------------
// Função junta duas strings, geralmente usadas para juntar um
//  diretório e um arquivo, usando o caractere '/' como separador.
//  Ela aloca memória para a string resultante, copia os caracteres
//  das duas strings para a string resultante e adiciona o caractere 
// '/' entre as duas strings. Em seguida, adiciona o caractere '\0' 
// para indicar o fim da string e retorna a string resultante.

char	*path_join(const char *s1, const char *s2)
{
    int		i; // contador
    int		size; // tamanho da string resultante
    char	*out; // string resultante

    i = 0;
    size = ft_strlen(s1) + 1; // calcula o tamanho da string resultante 
    out = malloc(ft_strlen(s1) + ft_strlen(s2) + 2); // aloca memória para a string resultante
    while (s1[i]) // enquanto houver caracteres na primeira string
    {
        out[i] = s1[i]; // copia o caractere para a string resultante
        i++;
    }
    out[i] = '/'; // adiciona o caractere '/' entre as duas strings
    i = 0;
    while (s2[i]) // enquanto houver caracteres na segunda string
    {
        out[size] = s2[i]; // copia o caractere para a string resultante
        i++;
        size++;
    }
    out[size] = '\0'; // adiciona o caractere '\0' para indicar o fim da string
    return (out); // retorna a string resultante
}

---------------------------------------------------------------------------------
// Essa funkk serve pra dividir uma string em um array de strings 
// usando o caractere espaço como separador. Ela usa a função ft_split
//  para dividir a string original e depois percorre as strings do 
// array e procura por caractere ' e 1 para trocar pelo caractere 
// espaço. Dessa forma, é possível preservar os espaços dentro de 
// aspas simples.

char	**space_split(char *cmd)
{
    char	**splitted_cmd; // array de strings resultante
    int		i; // contador
    int		j; // contador

    i = 0;
    j = 0;
    splitted_cmd = ft_split(cmd, ' '); // divide a string original em um array de strings usando o caractere ' ' como separador
    while (splitted_cmd[j]) // enquanto houver elementos no array
    {	
        i = 0;
        while (splitted_cmd[j][i] && splitted_cmd[j][i] != '\'') // enquanto houver caracteres e não for encontrado um caractere '
            i++;
        if (splitted_cmd[j][i] && splitted_cmd[j][i + 1]) // se houver mais um caractere depois do '
            i++;
        while (splitted_cmd[j][i] && splitted_cmd[j][i] != '\'') // enquanto houver caracteres e não for encontrado outro '
        {
            if (splitted_cmd[j][i] == 1) // se o caractere for 1
                splitted_cmd[j][i] = ' '; // troca pelo caractere espaço
            i++;
        }
        j++;
    }
    return (splitted_cmd); // retorna o array de strings resultante
}

