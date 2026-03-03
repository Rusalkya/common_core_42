/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:37:06 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/03 11:43:05 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
#define ITER_HPP
#include <iostream>
#include <string>

template <typename T, typename F>
void	iter(T* array, size_t len, F function)
{
	for (size_t i = 0;i < len; ++i)
		function(array[i]);
}
#endif