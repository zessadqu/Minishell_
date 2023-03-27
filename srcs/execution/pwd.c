/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 21:06:56 by zessadqu          #+#    #+#             */
/*   Updated: 2023/03/27 23:33:11 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_data *data)
{
	getcwd(data->path, PATH_MAX);
	ft_putendl_fd(data->path, data->cmds->out_file);
	exitS = 0;
	return (0);
}
