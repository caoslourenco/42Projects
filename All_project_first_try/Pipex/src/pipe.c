/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clourenc  <clourenc@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:32:15 by clourenc          #+#    #+#             */
/*   Updated: 2023/01/13 16:45:19 by clourenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// Essa função é usada pra configurar e executar um processo filho.
//  Ele abre o arquivo especificado em argv[1] com permissão de 
// leitura, redireciona a saída padrão para o pipe e a entrada padrão
//  para o arquivo de entrada, fecha a extremidade de leitura do pipe
//  e chama a função create_child para criar e executar o comando 
// especificado em argv[2]. Se o arquivo não pôde ser aberto, escreve
//  uma mensagem de erro no stderr, fecha o descritor de arquivo e 
// finaliza o programa com código de saída 127.
void	execute_child(char **argv, char **envp, int *fd)
{
    int	child_infile; // descritor de arquivo para o arquivo de entrada

    child_infile = open(argv[1], O_RDONLY, 0777); // abre o arquivo especificado em argv[1] com permissão de leitura
    if (child_infile == -1) // se o arquivo não pôde ser aberto
    {
        perror("Error: "); // escreve a mensagem de erro no stderr
        close(child_infile); // fecha o descritor de arquivo
        exit(127); // finaliza o programa com código de saída 127
    }
    dup2(fd[1], STDOUT_FILENO); // redireciona a saída padrão para o pipe
    dup2(child_infile, STDIN_FILENO); // redireciona a entrada padrão para o arquivo de entrada
    close(fd[0]); // fecha a extremidade de leitura do pipe
    create_child(argv[2], envp); // cria o processo filho e executa o comando especificado em argv[2]
}
-------------------------------------------------------------------------------------
// é semelhante a execute_child, é usada para configurar e executar um segundo processo filho. Ele abre o arquivo 
// especificado em argv[4] com permissão de escrita, cria o arquivo se ele não existir e apaga o conteúdo anterior, 
// redireciona a entrada padrão para o pipe e a saída padrão para o arquivo de saída, fecha a extremidade de escrita do
// pipe e chama a função create_child para criar e executar o comando especificado em argv[3]. Se o arquivo não pôde
//  ser aberto, escreve uma mensagem de erro no stderr, fechao descritor de arquivo e finaliza o programa com código de
//  saída 127.

void	execute_child2(char **argv, char **envp, int *fd)
{
    int	output_file; // descritor de arquivo para o arquivo de saída

    output_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777); // abre o arquivo especificado em argv[4] com permissão de escrita, cria o arquivo se ele não existir e apaga o conteúdo anterior
    if (output_file == -1) // se o arquivo não pôde ser aberto
    {
        perror("Error: "); // escreve a mensagem de erro no stderr
        close(output_file); // fecha o descritor de arquivo
        exit(127); // finaliza o programa com código de saída 127
    }
    dup2(fd[0], STDIN_FILENO); // redireciona a entrada padrão para o pipe
    dup2(output_file, STDOUT_FILENO); // redireciona a saída padrão para o arquivo de saída
    close(fd[1]); // fecha a extremidade de escrita do pipe
    create_child(argv[3], envp); // cria o processo filho e executa o comando especificado em argv[3]
}
----------------------------------------------------------------------
// Esse função serve para gerenciar os processos filhos. Ele fecha 
// as extremidades do pipe, espera os dois processos filhos 
// terminarem e se o segundo processo filho terminou normalmente 
// (WIFEXITED retorna true), obtém o código de saída do processo 
// filho através da função WEXITSTATUS e finaliza o programa com 
// esse código de saída. é usada pra garantir que os processos 
// filhos sejam finalizados antes que o processo pai termine,
//  e para obter o status de saída dos processos filhos e
//  usá-lo para determinar o comportamento do processo pai.
// void	parent_child_process(int *fd, int pid1, int pid2)
{
    int	wait_status; // armazena o status de saída do processo filho
    int	status_code; // armazena o código de saída do processo filho

    close(fd[0]); // fecha a extremidade de leitura do pipe
    close(fd[1]); // fecha a extremidade de escrita do pipe
    waitpid(pid1, NULL, 0); // espera o primeiro processo filho terminar
    waitpid(pid2, &wait_status, 0); // espera o segundo processo filho terminar
    if (WIFEXITED(wait_status)) // se o processo filho terminou normalmente
    {
        status_code = WEXITSTATUS(wait_status); // obtém o código de saída do processo filho
        exit(status_code); // finaliza o programa com o código de saída do processo filho
    }
}

-------------------------------------------------------------------------------------------

int	main(int argc, char **argv, char **envp)
{
    int		fd[2]; // array de inteiros fd para criar um pipe
    int		pid; // variável para armazenar o pid do processo filho 1
    int		pid2; // variável para armazenar o pid do processo filho 2

    if (argc != 5) // verifica se o número de argumentos é válido
    {
        write(2, "Error: Invalid number of arguments.\n", 37); // escreve mensagem de erro no stderr
        write(1, "Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 43); // escreve exemplo de uso no stdout
        exit(1); // finaliza o programa com código de saída 1
    }
    else // se o número de argumentos é válido
    {
        if (pipe(fd) < 0) // cria o pipe
            perror("Error: "); // em caso de erro, escreve a mensagem de erro
        pid = fork(); // cria o primeiro processo filho
        if (pid == 0) // se for o processo filho 1
            execute_child(argv, envp, fd); // executa a função execute_child
        pid2 = fork(); // cria o segundo processo filho
        if (pid2 == 0) // se for o processo filho 2
            execute_child2(argv, envp, fd); // executa a função execute_child2
        parent_child_process(fd, pid, pid2); // executa a função parent_child_process
    }
    return (0); // retorna 0 para indicar que o programa finalizou sem erros
}
