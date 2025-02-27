/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:07 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/29 22:09:42 by zessadqu         ###   ########.fr       */
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
    int   her_file = 0;

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
                    exitS = 2;
                    ft_putstr_fd("\nexit\n", 1);
                    exit (exitS);
                }
                buffer_size = ft_strlen(data.buffer);
            }
            add_history(data.buffer);
            data.cmds = parse_line(&data);
            free_tokens_list(&data);
            /////// EXECUTION PART /////
            if (data.cmds)
                cmd_call(&data,her_file);
        }
    }
    return (0);
}
