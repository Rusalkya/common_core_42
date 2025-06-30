/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:24:45 by clfouger          #+#    #+#             */
/*   Updated: 2025/06/30 15:21:45 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"

typedef struct s_node
{
	int				value;
	struct s_node	*next;
}	t_node;

//stack
t_node	*create_node(int value);
void	append_node(t_node **stack, t_node *new_node);
void	print_stack(t_node *stack);
void	free_stack(t_node **stack);
int		ft_stacksize(t_node *stack);
//push
void	pa(t_node **a, t_node **b, int print);
void	pb(t_node **a, t_node **b, int print);
//swap
void	sa(t_node **a, int print);
void	sb(t_node **b, int print);
void	ss(t_node **a, t_node **b, int print);
//rotate
void	ra(t_node **a, int print);
void	rb(t_node **b, int print);
void	rr(t_node **a, t_node **b, int print);
//revrotate
void	rra(t_node **a, int print);
void	rrb(t_node **b, int print);
void	rrr(t_node **a, t_node **b, int print);
//parsing
char	**get_args_split(int argc, char *argv[]);
void	parse_args_to_stack(char **args, t_node **a);
void	free_split(char **split);
//parsing_check
int		is_valid_int(const char *str);
int		ft_atoi_safer(const char *str);
int		is_sorted(t_node *stack);
//parsing_utils
int		check_duplicates(t_node *stack);
int		parsing_is_valid(char **args, t_node *a);
//sort
int		*normalize_stack(t_node *stack);
int		*sort_int_tab(int *tab, int size);
int		find_index(int *array, int value, int size);
void	update_stack_values(t_node *stack, int *sorted, int size);
void	apply_normalization(t_node *stack);
//push_little_swap
void	push_little_swap(t_node **a, t_node **b);
void	sort_three(t_node **a);
void	sort_small_stack(t_node **a, t_node **b);
int		find_minimum(t_node *stack);
//radix
void	radix_pass(t_node **a, t_node **b, int bit);
void	restore_stack(t_node **a, t_node **b);
void	radix_sort(t_node **a, t_node **b);
//push_swap
int		get_max_bits(t_node *stack);
void	choose_sort(t_node **a, t_node **b, int size);
int		init_args_and_stack(int argc, char **argv, char ***args,
			t_node **a);
void	push_swap(int argc, char **argv);

#endif