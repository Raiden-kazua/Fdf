/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 08:44:40 by bsouchet          #+#    #+#             */
/*   Updated: 2016/03/11 08:47:18 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		check_hex(char *s, int x, int *e, t_var v)
{
	int letter;
	int num;
	int i;

	i = 0;
	num = 0;
	letter = -1;
	while (x++ > -1 && num++ > -1 && s[x] != 32 && s[x] != 0)
		if ((s[x] < 48 || s[x] > 57) && (s[x] < 65 || s[x] > 70) && (*e)++ == 0)
			ft_pr(v, 6);
		else if ((letter == -1 || s[x] == letter) && i++ > -1)
			letter = s[x];
		else if (s[x] != letter)
			i = 0;
	if (((num == 4 && i != 3) || (num != 4 && num != 7)) && (*e)++ == 0)
		ft_pr(v, 6);
	return (1);
}

static t_var	check_num(t_var v, int e)
{
	if (v.c[v.x] == 43 || v.c[v.x] == 45)
		while (v.x++ > -1 && v.c[v.x] != 32 && v.c[v.x] != 0 && v.c[v.x] != 44)
			if (e == 0 && (v.c[v.x] < 48 || v.c[v.x] > 57) && ft_pr(v, 7) < 0)
				e++;
	v.x--;
	while (v.x++ > -5 && v.c[v.x] != 32 && v.c[v.x] != 0 && v.c[v.x] != 44)
		if (e == 0 && (v.c[v.x] < 48 || v.c[v.x] > 57) && ft_pr(v, 4) < 0)
			e++;
	if (v.c[v.x] == 44 && v.c[v.x + 1] == 48 && v.c[v.x + 2] == 120
			&& check_hex(v.c, v.x + 2, &e, v) > 0)
		while (v.x++ > -1 && v.c[v.x] != 32 && v.c[v.x] != 0)
			;
	else if (v.c[v.x] == 44)
	{
		if (e++ == 0)
			ft_pr(v, 4);
		while (v.x++ > -1 && v.c[v.x] != 32 && v.c[v.x] != 0)
			;
	}
	if (e != 0)
		v.inv = e;
	return (v);
}

t_var			check(t_var v, int num)
{
	v.lns++;
	v.x = 0;
	while (v.c[v.x] != 0)
	{
		while (v.c[v.x] == 32)
			v.x++;
		if (v.c[v.x] != 32 && v.c[v.x] != 0 && num++ > -1)
			v = check_num(v, 0);
	}
	if (v.wth == -1)
		v.wth = num;
	else if (v.wth != -1 && num != v.wth)
		v.wth = -2;
	return (v);
}