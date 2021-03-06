/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 17:29:50 by alushenk          #+#    #+#             */
/*   Updated: 2017/07/06 17:29:53 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	display_stack(t_stack *stack)
{
	int i;

	i = 0;
	while (i < stack->length)
	{
		ft_putstr(ft_itoa(stack->x->value));
		ft_putchar('\n');
		rotate_up(stack);
		i++;
	}
}

void	display_instructions(t_inst_lst *stack)
{
	int		i;
	t_inst	*elem;

	elem = stack->x;
	i = 0;
	while (i < stack->length)
	{
		ft_putstr(elem->name);
		ft_putchar('\n');
		elem = elem->next;
		i++;
	}
}

void	display_array(t_array *array)
{
	int	i;

	i = 0;
	while (i < array->length)
	{
		ft_putnbr(array->array[i]);
		ft_putchar('\n');
		i++;
	}
}

void	display_both(t_stack *a, t_stack *b)
{
	int	i;

	i = 0;
	while (i < a->length || i < b->length)
	{
		if (i < a->length)
		{
			ft_putnbr(a->x->value);
			rotate_up(a);
		}
		ft_putchar('\t');
		if (i < b->length)
		{
			ft_putnbr(b->x->value);
			rotate_up(b);
		}
		ft_putchar('\n');
		i++;
	}
}
