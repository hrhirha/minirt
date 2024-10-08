/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 09:54:13 by hrhirha           #+#    #+#             */
/*   Updated: 2020/04/23 09:54:15 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	g_a;
double	g_b;
double	g_c;
double	g_disc;
t_vec	g_rs;
double	g_t;
double	g_t1;
double	g_t2;

double	sphere_intersect(t_ray ray, t_sp sp)
{
	g_rs = subvec(ray.start, sp.center);
	g_a = dot(ray.dir, ray.dir);
	g_b = dot(ray.dir, g_rs);
	g_c = dot(g_rs, g_rs) - (sp.radius * sp.radius);
	g_disc = g_b * g_b - g_a * g_c;
	if (g_disc < 0)
		return (-1);
	g_t1 = (-g_b - sqrt(g_disc)) / g_a;
	g_t2 = (-g_b + sqrt(g_disc)) / g_a;
	if (g_t2 < T_MIN)
		return (-1);
	if (g_t1 > T_MIN)
		g_t = g_t1;
	else
		g_t = g_t2;
	return (g_t);
}

void	closest_sp(t_data *data, t_vec *inter_pt, t_vec *n, t_vec *col)
{
	double	t;
	t_sp	sp;

	sp = *(t_sp *)data->curr_shape;
	t = sphere_intersect(data->ray, sp);
	if (t != -1 && t < (data->t_min))
	{
		*col = sp.color;
		data->t_min = t;
		*inter_pt = addvec(data->ray.start, mulvec(t, data->ray.dir));
		*n = normalize(subvec(*inter_pt, sp.center));
	}
}
