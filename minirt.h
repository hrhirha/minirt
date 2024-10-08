/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 09:55:00 by hrhirha           #+#    #+#             */
/*   Updated: 2020/10/14 12:22:49 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include "minilibx_mms_20200219/mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"

# define T_MIN 		1.0e-5
# define T_MAX 		1.0e100

# ifdef __APPLE__
#  define ESC_KEY	53
#  define SP_KEY	49
# elif __linux
#  define ESC_KEY	65307
#  define SP_KEY	32
# endif

# define SP 1
# define PL 2
# define TR 3
# define SQ 4
# define CY 5

typedef	struct	s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

typedef	struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_res
{
	int			h;
	int			w;
	int			loaded;
}				t_res;

typedef struct	s_amb
{
	double		ratio;
	t_color		color;
	int			loaded;
}				t_amb;

typedef	struct	s_cam
{
	t_vec		pos;
	t_vec		dir;
	t_vec		right;
	t_vec		up;
	double		fov;
}				t_cam;

typedef	struct	s_ray
{
	t_vec		start;
	t_vec		dir;
}				t_ray;

typedef	struct	s_light
{
	t_vec		pos;
	double		ratio;
	t_color		color;
}				t_light;

typedef	struct	s_sp
{
	int			id;
	t_vec		center;
	double		radius;
	t_vec		color;
}				t_sp;

typedef	struct	s_plane
{
	int			id;
	t_vec		ref;
	t_vec		normal;
	t_vec		color;
}				t_plane;

typedef	struct	s_tr
{
	int			id;
	t_vec		p0;
	t_vec		p1;
	t_vec		p2;
	t_vec		p0p1;
	t_vec		p0p2;
	t_vec		color;
}				t_tr;

typedef	struct	s_sq
{
	int			id;
	t_vec		center;
	t_vec		normal;
	double		side;
	t_vec		u;
	t_vec		v;
	t_vec		color;
}				t_sq;

typedef	struct	s_cy
{
	int			id;
	t_vec		pos;
	t_vec		pos2;
	t_vec		normal;
	double		radius;
	double		height;
	t_vec		color;
}				t_cy;

typedef	struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef	struct	s_data
{
	char		*bmp_name;

	void		*win;
	void		*ptr;
	t_list		*imgs;
	t_img		*curr_img;

	int			save;

	t_res		res;
	t_amb		amb;

	double		t_min;

	t_ray		ray;
	double		hit;
	t_vec		hit_pt;
	t_vec		hit_normal;
	t_vec		hit_color;

	t_ray		ray_lt;
	double		hit_lt;
	t_vec		hit_pt_lt;
	t_vec		hit_normal_lt;
	t_vec		hit_color_lt;

	t_list		*cams;
	t_cam		*curr_cam;
	t_list		*lights;
	t_light		*light;
	t_list		*shapes;
	void		*curr_shape;
	t_color		pxl_color;
}				t_data;

typedef struct	s_bmp
{
	char		type[2];
	int			size;
	int			reserve;
	int			offset;
	int			dib_size;
	int			width;
	int			height;
	short		plane;
	short		bpp;
	int			copmression;
	int			array_size;
	int			x_res;
	int			y_res;
	int			colour;
	int			imp_colour;
}				t_bmp;

void			read_fd(int fd, t_data *data);
void			render_scenes(t_data *data);
void			ray_trace(t_data *data);
int				save_image(t_data *data, int x, int y);

/*
** intersections
*/

double			first_inter(t_data *data, t_vec *inter_pt, t_vec *n,
							t_vec *col);
void			closest_sp(t_data *data, t_vec *inter_pt, t_vec *n, t_vec *col);
void			closest_pl(t_data *data, t_vec *inter_pt, t_vec *n, t_vec *col);
void			closest_tr(t_data *data, t_vec *inter_pt, t_vec *n, t_vec *col);
void			closest_sq(t_data *data, t_vec *inter_pt, t_vec *n, t_vec *col);
void			closest_cy(t_data *data, t_vec *inter_pt, t_vec *n, t_vec *col);
double			sphere_intersect(t_ray ray, t_sp sp);
double			plane_intersect(t_ray ray, t_plane pl);
double			triangle_intersect(t_ray ray, t_tr tr);
double			square_intersect(t_ray ray, t_sq sq);
double			cylinder_intersect(t_ray ray, t_cy cy);

/*
** color clac
*/

t_color			calc_intensity(t_data *data, t_vec inter_pt, t_vec n);
t_color			calc_color(t_data *data, double px, double py);
int				rgb_to_int(t_color c);

/*
** errors
*/

void			given_info_error(char *s);
void			load_error_msg(t_data *data);
int				check_errors(char **tab);
void			normal_error(t_vec normal);
void			tab_len_error(char **tab, int num);
void			ratio_error(char **tab, int i);
void			double_error_msg(char **tab, int i);
void			check_res_values(t_data *data, t_res *res, char **tab);
void			negative_fov(char **tab, double fov);
void			neg_dist_error(char **tab, double d, int i);

/*
** extract data from string
*/

t_vec			ext_vec(char *s);
t_color			ext_color(char *s);
t_vec			ext_color_ratio(char *s);

/*
** implement res and ambient
*/

void			implement_res(t_data *data, char *line, t_res *res);
void			implement_amb(char *line, t_amb *amb);

/*
** implement lights and camera
*/

void			implement_lights(char *line, t_list **lights);
void			implement_cameras(char *line, t_list **cams);

/*
** implement shapes
*/

void			implement_shapes(char *line, t_list **shapes);
void			implement_sp(char **tab, t_list **shapes);
void			implement_pl(char **tab, t_list **shapes);
void			implement_tr(char **tab, t_list **shapes);
void			implement_sq(char **tab, t_list **shapes);
void			implement_cy(char **tab, t_list **shapes);

/*
** utils
*/

int				keys(int key, t_data *data);
int				mclose(void *data);
void			lst_circle(t_list **imgs);
int				tab_len(char **tab);
void			free_tab(char **tab);
void			free_and_exit(char **tab);

int				is_whitespace(int c);
int				is_double(char *s);
int				is_int(char *s);
void			isvalid_rgb(char **sub);
void			isvalid_vec(char **sub);

/*
** vec math
*/

double			dot(t_vec v1, t_vec v2);
t_vec			cross(t_vec v1, t_vec v2);
t_vec			normalize(t_vec v);
t_vec			subvec(t_vec v1, t_vec v2);
t_vec			addvec(t_vec v1, t_vec v2);
t_vec			mulvec(double n, t_vec v);
t_vec			invec(t_vec vec);
int				vec_cmp(t_vec vec1, t_vec vec2);

#endif
