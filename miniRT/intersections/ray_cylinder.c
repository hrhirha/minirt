/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 12:26:36 by hrhirha           #+#    #+#             */
/*   Updated: 2020/10/14 14:01:30 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	g_a;
double	g_b;
double	g_c;
double	g_disc;
double	g_t1;
double	g_t2;

t_vec	get_normal(t_vec p, t_cy cy)
{
	t_vec	c0;
	t_vec	v;
	t_vec	cyp;
	t_vec	cy2p;
	double	d;

	cyp = subvec(p, cy.pos);
	cy2p = subvec(p, cy.pos2);
	if (dot(cy.normal, cyp) == 0 && dot(cyp, cyp) <= cy.radius * cy.radius)
		return (invec(cy.normal));
	if (dot(cy.normal, cy2p) == 0 && dot(cy2p, cy2p) <= cy.radius * cy.radius)
		return (cy.normal);
	d = sqrt(dot(cyp, cyp) - cy.radius * cy.radius);
	if (dot(cy.normal, cyp) < 0)
		cy.normal = invec(cy.normal);
	c0 = addvec(cy.pos, mulvec(d, cy.normal));
	v = normalize(subvec(p, c0));
	return (v);
}

int		intersect_disk(t_ray ray, t_cy cy, t_vec c, double *t)
{
	t_vec	normal;
	double	dist;
	double	denom;
	t_vec	p;
	t_vec	cp;

	normal = get_normal(c, cy);
	denom = dot(ray.dir, normal);
	if (denom >= 0)
		return (-1);
	dist = dot(subvec(c, ray.start), normal) / denom;
	if (dist < T_MIN)
		return (-1);
	p = addvec(ray.start, mulvec(dist, ray.dir));
	cp = subvec(p, c);
	if (dot(cp, cp) > cy.radius * cy.radius)
		return (-1);
	*t = dist;
	return (1);
}

int		limit_cy(t_ray ray, t_cy cy, double *t)
{
	double	h;
	t_vec	p;
	double	d1;
	double	d2;
	int		cap1;
	int		cap2;

	p = addvec(ray.start, mulvec(*t, ray.dir));
	h = dot(subvec(p, cy.pos), cy.normal);
	cap1 = intersect_disk(ray, cy, cy.pos, &d1) == 1;
	cap2 = intersect_disk(ray, cy, cy.pos2, &d2) == 1;
	if (h < 0 || h > cy.height)
	{
		if (cap1 == 1 || cap2 == 1)
			*t = g_t2;
		else
			return (-1);
	}
	// if (cap1 == 1 && d1 < *t)
	// 	*t = d1;
	// if (cap2 == 1 && d2 < *t)
	// 	*t = d2;
	return (1);
}

double	cylinder_intersect(t_ray ray, t_cy cy)
{
	double	t;
	t_vec	p0;

	p0 = subvec(ray.start, cy.pos);
	g_a = 1 - pow(dot(cy.normal, ray.dir), 2);
	g_b = dot(p0, ray.dir) - dot(cy.normal, p0) * dot(cy.normal, ray.dir);
	g_c = dot(p0, p0) - pow(dot(cy.normal, p0), 2) - pow(cy.radius, 2);
	g_disc = g_b * g_b - g_a * g_c;
	if (g_disc < 0)
		return (-1);
	g_t1 = (-g_b - sqrt(g_disc)) / g_a;
	g_t2 = (-g_b + sqrt(g_disc)) / g_a;
	if (g_t2 < T_MIN)
		return (-1);
	if (g_t1 > T_MIN)
		t = g_t1;
	else
		t = g_t2;
	if (limit_cy(ray, cy, &t) == -1)
		return (-1);
	return (t);
}

void	closest_cy(t_data *data, t_vec *inter_pt, t_vec *n, t_vec *col)
{
	double	t;
	t_cy	cy;

	cy = *(t_cy *)data->curr_shape;
	t = cylinder_intersect(data->ray, cy);
	if (t != -1 && t < (data->t_min))
	{
		*col = cy.color;
		data->t_min = t;
		*inter_pt = addvec(data->ray.start, mulvec(t, data->ray.dir));
		*n = get_normal(*inter_pt, cy);
	}
}
