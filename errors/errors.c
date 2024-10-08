/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 09:51:21 by hrhirha           #+#    #+#             */
/*   Updated: 2020/10/14 10:11:16 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	given_info_error(char *s)
{
	ft_putstr_fd("Error\nWrong number of informations given to ", 1);
	ft_putstr_fd(s, 0);
	ft_putstr_fd("\n", 0);
}

void	load_error_msg(t_data *data)
{
	if (data->res.loaded == -1)
	{
		ft_putstr_fd("Error\nResolution not found..\n", 1);
		exit(-1);
	}
	if (data->amb.loaded == -1)
	{
		ft_putstr_fd("Error\nAmbient light not found..\n", 1);
		exit(-1);
	}
	if (!data->cams)
	{
		ft_putstr_fd("Error\nCouldn't find any cameras..\n", 1);
		exit(-1);
	}
}

int		check_errors(char **tab)
{
	if (tab_len(tab) != 4 && ((tab[0][0] == 's' && tab[0][1] == 'p') ||
							(tab[0][0] == 'p' && tab[0][1] == 'l')))
	{
		given_info_error(tab[0]);
		return (1);
	}
	if (tab_len(tab) != 5 && ((tab[0][0] == 't' && tab[0][1] == 'r') ||
							(tab[0][0] == 's' && tab[0][1] == 'q')))
	{
		given_info_error(tab[0]);
		return (1);
	}
	if (tab_len(tab) != 6 && (tab[0][0] == 'c' && tab[0][1] == 'y'))
	{
		given_info_error(tab[0]);
		return (1);
	}
	return (-1);
}

void	tab_len_error(char **tab, int num)
{
	if (tab_len(tab) != num)
	{
		given_info_error(tab[0]);
		free_tab(tab);
		exit(-1);
	}
}

void	neg_dist_error(char **tab, double d, int i)
{
	if (d < 0)
	{
		ft_putstr_fd("Error\nNegative distance at ", 1);
		ft_putstr_fd(tab[0], 1);
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(tab[i], 1);
		ft_putstr_fd("\n", 1);
		free_and_exit(tab);
	}
}
