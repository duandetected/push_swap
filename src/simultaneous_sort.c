//
// Created by Anton Lushenko on 7/5/17.
//

#include "push_swap.h"

t_instructions	*get_instructions(int length)
{
	t_instructions	*result;
	t_instruction	*instruction;
	int				i;

	result = create_list();
	g_instructions->length -= length;
	instruction = g_instructions->x;
	i = 0;
	while (i < length)
	{
		instruction = instruction->prev;
		i++;
	}
	instruction->prev->next = g_instructions->x;
	g_instructions->x->prev = instruction->prev;
	i = 0;
	while (i < length)
	{
		add_instruction(result, instruction->name);
		instruction = instruction->next;
		i++;
	}
	return (result);
}

void	rename_command(char *name)
{
	if (ft_strcmp(name, "sa") == 0)
		name[1] = 's';
	else if (ft_strcmp(name, "sb") == 0)
		name[1] = 's';
	else if (ft_strcmp(name, "ra") == 0)
		name[1] = 'r';
	else if (ft_strcmp(name, "rb") == 0)
		name[1] = 'r';
	else if (ft_strcmp(name, "rra") == 0)
		name[2] = 'r';
	else if (ft_strcmp(name, "rrb") == 0)
		name[2] = 'r';
}

void	rename_command_b(char *name)
{
	if (ft_strcmp(name, "sa") == 0)
		name[1] = 'b';
	else if (ft_strcmp(name, "ra") == 0)
		name[1] = 'b';
	else if (ft_strcmp(name, "rra") == 0)
		name[2] = 'b';
}

void	merge_instructions_a(t_instructions *a, t_instructions *b)
{
	int i;
	int j;
	t_instruction *instruction;

	i = 0;
	while (i < a->length && strcmp(a->x->name, b->x->name))
	{
		a->x = a->x->next;
		i++;
	}
	j = 0;
	while (i < a->length && j < b->length && strcmp(a->x->name, b->x->name) == 0)
	{
		rename_command(a->x->name);
		a->x = a->x->next;
		b->x = b->x->next;
		j++;
		i++;
	}
	while (i < a->length)
	{
		a->x = a->x->next;
		i++;
	}
	instruction = b->x;
	while (j < b->length)
	{
		rename_command_b(instruction->name);
		add_instruction(a, instruction->name);
		instruction = instruction->next;
		j++;
	}

	instruction = a->x;
	i = 0;
	while (i < a->length)
	{
		add_instruction(g_instructions, instruction->name);
		instruction = instruction->next;
		i++;
	}
}

void	merge_instructions_b(t_instructions *a, t_instructions *b)
{
	int i;
	int j;
	t_instruction *instruction;

	i = 0;
	while (i < a->length && strcmp(a->x->name, b->x->name))
	{
		rename_command_b(a->x->name);
		a->x = a->x->next;
		i++;
	}
	j = 0;
	while (i < a->length && j < b->length && strcmp(a->x->name, b->x->name) == 0)
	{
		rename_command(a->x->name);
		a->x = a->x->next;
		b->x = b->x->next;
		j++;
		i++;
	}
	while (i < a->length)
	{
		rename_command_b(a->x->name);
		a->x = a->x->next;
		i++;
	}
	instruction = b->x;
	while (j < b->length)
	{
		add_instruction(a, instruction->name);
		instruction = instruction->next;
		j++;
	}

	instruction = a->x;
	i = 0;
	while (i < a->length)
	{
		add_instruction(g_instructions, instruction->name);
		instruction = instruction->next;
		i++;
	}
}

void 	simultaneous_sort(t_stack *a, t_stack *b)
{
	int	count;
	int b_group_length;
	t_instructions *a_list;
	t_instructions *b_list;
	t_instruction *instruction;
	int i;

	if (a->x->group_length == 0 || b->x->group_length == 0)
		return ;
	b_group_length = b->x->group_length;
	count = g_instructions->length;
	sort_a(a, a->x->group_length);
	a_list = get_instructions(g_instructions->length - count);
	sort_b(b, b->x->group_length);
	b_list = get_instructions(g_instructions->length - count);


	if (b_list->x == NULL)
	{
		instruction = a_list->x;
		i = 0;
		while (i < a_list->length)
		{
			add_instruction(g_instructions, instruction->name);
			instruction = instruction->next;
			i++;
		}
		replace_group(a, b, b_group_length);
		return ;
	}
	if (a_list->x == NULL)
	{
		instruction = b_list->x;
		i = 0;
		while (i < b_list->length)
		{
			rename_command_b(instruction->name);
			add_instruction(g_instructions, instruction->name);
			instruction = instruction->next;
			i++;
		}
		replace_group(a, b, b_group_length);
		return ;
	}

	if (a_list->length > b_list->length)
		merge_instructions_a(a_list, b_list);
	else
		merge_instructions_b(b_list, a_list);

	replace_group(a, b, b_group_length);
}