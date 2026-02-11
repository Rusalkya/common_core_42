/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:11:01 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/10 13:33:46 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include <iterator>
#include <iostream>
#include <list>
#include <stack>

class Span 
{
	private:
		std::vector<int> _numbers;
		unsigned int _max_size;
		
	public:
		Span(unsigned int n) : _max_size(n) {}
		Span(const Span& other) : _numbers(other._numbers), _max_size(other._max_size) {}
		Span& operator=(const Span& other);
		~Span() {}

		void addNumber(int n);
		
		template <typename Iterator>
		void addNumber(Iterator begin, Iterator end);

		long shortestSpan() const;
		long longestSpan() const;
};

template <typename Iterator>
void Span::addNumber(Iterator begin, Iterator end)
{
	size_t distance = std::distance(begin, end);

	if (_numbers.size() + distance > _max_size)
		throw std::runtime_error("span is full, cannot add more numbers");

	_numbers.insert(_numbers.end(), begin, end);
}

#endif
