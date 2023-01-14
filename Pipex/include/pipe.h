/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clourenc  <clourenc@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:31:57 by clourenc          #+#    #+#             */
/*   Updated: 2023/01/13 15:16:26 by clourenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// libraries
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../libft/libft.h"

// Childprocess
void	create_child(char *argv, char **envp); 
// Essa função é chamada para executar o comando específico.
char	**get_first_command(char *cmd);
char	*find_command_in_path(char **cmd, char **envp);

// othersPathstring
char	*path_join(const char *s1, const char *s2);
char	**space_split(char *cmd);
int		count_char_in_string(char *str, int c);
void	error_handler(char **access, int exitcode);
void	free_all(char **access);


#endif