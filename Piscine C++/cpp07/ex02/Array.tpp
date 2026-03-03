/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 09:44:45 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/04 09:50:58 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

template <typename T>
T& Array <T>::operator[](unsigned int index)
{
	if (index >= this->size())
		throw std::out_of_range("array index out of bounds");
	return this->_array[index];
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const
{
	if (index >= this->size())
		throw std::out_of_range("array index out of boundes");
	return this->_array[index];
} 