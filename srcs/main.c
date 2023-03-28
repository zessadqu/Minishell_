/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:07 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/28 21:52:33 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exitS;

int main(int ac, char **av, char **envp)
{
    t_data  data;
    int status;
    int     buffer_size;
    char path[PATH_MAX];

    (void)**av;
    if (ac == 1)
    {
        data.envp_ = envp;
        data.buffer = NULL;
        set_environment(&data, envp);
        while (1)
        {
            signals_handler();
            buffer_size = 0;
            data.err = 0;
            while (!buffer_size)
            {
                data.buffer = readline("(minishell@Developers)$> ");
                if (!data.buffer)
                {
                    //// HANDLE CTRL + D
                    exitS = 2;
                    ft_putstr_fd("exit", 1);
                    exit (exitS);
                }
                buffer_size = ft_strlen(data.buffer);
            }
            add_history(data.buffer);
            data.cmds = parse_line(&data);
            free_tokens_list(&data);
            /////// EXECUTION PART /////
            execute_command(data.cmds,get_path(data.cmds->str[0],&data,&status ),envp);
            
        }
    }
    return (0);
}
