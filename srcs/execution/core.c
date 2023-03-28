/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:01:09 by zessadqu          #+#    #+#             */
/*   Updated: 2023/03/28 22:07:37 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_call(t_exec *exec, t_data *data, char **envp, int her_file)
{
	int		i;
	int		check;
	char	*path;

	i = 0;
	check = 2;

	if (data->pipex->p_c)
    {
		exec_pipes(exec, data, her_file, envp);
        //free here
		return ;
	}

	i = redirection_handler(data);
	if (!exec->str[0] || exec->in_file == -1 || i == 0 || !builtin(data, exec))
	{
		return ;
	}

	path = get_path(exec->str, data, &check);
	execute_command(exec, path, envp);

	if (!check) {
		free(path);
	}

	//free here
	return ;
}
