/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clourenc  <clourenc@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:32:15 by clourenc          #+#    #+#             */
/*   Updated: 2023/01/14 05:40:55 by clourenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// A função get_first_command é usada para dividir uma string de 
// comando em um array de strings. Ele verifica se o número de aspas 
// é par, percorre a string até encontrar uma aspa e, em seguida, a
//  próxima aspa, substituindo os espaços entre elas por um caractere
//  especial. Se o número de aspas não é par, escreve uma mensagem de 
// erro no stderr. Em seguida, chama a função space_split para dividir
//  o comando em um array de strings usando o caractere especial como
//  delimitador e retorna o array de strings.


char	**get_first_command(char *cmd)
{
	char	**splitted_cmd; // array de strings com o comando dividido
	int		i;

	i = 0;
	if (count_char_in_string(cmd, '\'') % 2 == 0) // verifica se o número de aspas é par
	{
		while (cmd[i] && cmd[i] != '\'') // percorre a string até encontrar uma aspa
			i++;
		if (cmd[i] && cmd [i + 1]) // se a aspa não é a última caractere
			i++;
		while (cmd[i] && cmd[i] != '\'') // percorre a string até encontrar a próxima aspa
		{
			if (cmd[i] == ' ') // se o caractere é um espaço
				cmd[i] = 1; // substitui o espaço por um caractere especial
			i++;
		}
	}
	else
		write(2, "Error: ", 7); // escreve uma mensagem de erro no stderr
	splitted_cmd = space_split(cmd); // divide o comando em um array de strings usando o caractere especial como delimitador
	return (splitted_cmd); // retorna o array de strings
}

--------------------------------------------------------------------------------------------------------
// Essa função é usada para encontrar o caminho 
// completo de um comando específico. Ele procura a variável de 
// ambiente PATH no array envp, divide os diretórios do PATH em um 
// array de strings usando ':' como delimitador, percorre o array de 
// diretórios e verifica se o arquivo existe e tem permissão de 
// execução, se existir, retorna o caminho completo do comando, caso
//  contrário chama a função error_handler para finalizar o programa 
// com código de saída 127.

char	*find_command_in_path(char **cmd, char **envp)
{
	char	**path_directories; // array de strings com os diretórios do PATH
	char	*path; // caminho completo do comando
	int		i;

	i = 0;
	if (!cmd[0]) // se o comando não foi fornecido
		error_handler(cmd, 127); // chama a função error_handler para finalizar o programa com código de saída 127
	while (ft_strnstr(envp[i], "PATH", 4) == 0) // procura a variável de ambiente PATH
		i++;
	path_directories = ft_split(envp[i] + 5, ':'); // divide os diretórios do PATH em um array de strings usando ':' como delimitador
	i = 0;
	while (path_directories[i]) // percorre o array de diretórios
	{
		path = path_join(path_directories[i], cmd[0]); // junta o diretório com o nome do comando
		if (access(path, F_OK | X_OK) == 0) // verifica se o arquivo existe e tem permissão de execução
		{
			free_all(path_directories); // libera a memória alocada para o array de diretórios
			return (path); // retorna o caminho completo do comando
		}
		free(path); // libera a memória alocada para o caminho completo
		i++;
	}
	free_all(path_directories); // libera a memória alocada para o array de diretórios
	error_handler(cmd, 127); // chama a função error_handler para finalizar o programa com código de saída 127
	return (0);
}

--------------------------------------------------------------------------------------------------
// cria um processo filho e executar um comando específico.
//  Ela divide o comando em um array de strings com a função get_first_command,
//  encontra o caminho completo do comando com a função find_command_in_path,
//  se o caminho não foi encontrado chama a função error_handler para finalizar
//  o programa com código de saída 127. Em seguida, a função usa a chamada de 
// sistema execve para executar o comando passando o caminho completo,
//  o array de strings com o comando dividido e o array envp com as variáveis
//  de ambiente. Se a execução falhar, a função chama a função error_handler
//  para finalizar o programa com código de saída 0.


void	create_child(char *argv, char **envp)
{
	char	*path; // caminho completo do comando
	char	**cmd; // array de strings com o comando dividido

	cmd = get_first_command(argv); // divide o comando em um array de strings
	path = find_command_in_path(cmd, envp); // encontra o caminho completo do comando
	if (!path) // se o caminho não foi encontrado
		error_handler(cmd, 127); // chama a função error_handler para finalizar o programa com código de saída 127
	if (execve(path, cmd, envp) == -1) // executa o comando
	{
		free(path); // libera a memória alocada para o caminho completo
		error_handler(cmd, 0); // chama a função error_handler para finalizar o programa com código de saída 0
	}
}

