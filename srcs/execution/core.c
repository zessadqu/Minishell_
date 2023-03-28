/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:01:09 by zessadqu          #+#    #+#             */
/*   Updated: 2023/03/28 22:54:05 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_call(t_data *data, int her_file)
{
	int		i;
	int		check;
	char	*path;

	i = 0;
	check = 2;
	data->pipex= malloc(sizeof(t_pipe));
	data->pipex->p_c = count_pps(data->cmds);
	if (data->pipex->p_c)
    {
		exec_pipes(data->cmds, data, her_file, data->envp_);
        //free here
		return ;
	}

	if (!data->cmds->str[0] || !builtin(data, data->cmds))
	{
		return ;
	}

	path = get_path(data->cmds->str[0], data, &check);
	execute_command(data->cmds, path, data->envp_);

	if (!check) {
		free(path);
	}

	//free here
	return ;
}
