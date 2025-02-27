/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:37:05 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/28 17:34:02 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int generate_error(t_data *data, char *error)
{
    exitS = 2;
    data->err = 1;
    ft_putstr_fd(error, 2);
    return (0);
}

void    heredoc_action(t_data *data, int status, int fd[0])
{
    if (status == 0)
    {
        exitS = 0;
        data->cmds->in_file = fd[0];
        data->tokens = data->tokens->next->next;
    }
    else
    {
        ///// CLOSE ALL FDS &  FREE ALL DATA 
        exitS = 130;
        close(fd[0]);
        close(fd[1]);
        free_tokens_list(data);
        free_env_list(data);
        //// Get new prompt //
        main (1, NULL, data->envp_);
    }
}

void    heredoc_sig_handler(int sig)
{
    (void)sig;
    exit(130);
}

void    read_input(t_data *data, int fd[2])
{
    char *buffer;

    close(fd[0]);
    signal(SIGINT, heredoc_sig_handler);
    while (1)
    {
        buffer = readline("heredoc> ");
        if (!buffer)
            exit(130);
        if (ft_strcmp(buffer, data->tokens->next->lex) == 0)
        {
            free(buffer);
            break;
        }
        ft_putstr_fd(buffer, fd[1]);
        free(buffer);
    }
    close(fd[1]);
    exit (0);
}

int heredoc_handler(t_data *data)
{
    int     fd[2];
    pid_t   pid;
    int     status;
    
    if (pipe(fd) == -1)
        return (generate_error(data, "Minishell: unsuccessful pipe creation\n"));
    signal(SIGINT, SIG_IGN);
    pid = fork();
    if (pid == -1)
        return (generate_error(data, "Minishell: unsuccessful fork\n"));
    if (pid == 0)
        read_input(data, fd);
    waitpid(pid, &status, 0);
    ///----- handle the heredoc exit status //
    heredoc_action(data, status, fd);
    return (1);
}