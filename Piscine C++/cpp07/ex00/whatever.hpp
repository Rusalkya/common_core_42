/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:10:59 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/03 10:35:11 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
#define WHATEVER_HPP

#include <iostream>
#include <string>

template <typename T>

void	swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
T min(const T &a, const T &b)
{
	if (a < b)
		return a;
	return b;
}

template <typename T>
T max(const T &a, const T &b)
{
	if (a > b)
		return a;
	return b;
}

#endif
