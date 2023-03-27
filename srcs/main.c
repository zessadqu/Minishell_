/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:07 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/27 23:54:45 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
            buffer_size = 0;
            data.err = 0;
            while (!buffer_size)
            {
                data.buffer = readline("minishell$> ");
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
