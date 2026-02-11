/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:10:59 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/09 18:30:25 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		_numbers = other._numbers;
		_max_size = other._max_size;
	}
	return *this;
}

void Span::addNumber(int n) 
{
	if (_numbers.size() >= _max_size)
		throw std::runtime_error("span is full, cannot add more numbers");

	_numbers.push_back(n);
}

long Span::shortestSpan() const
{
	if (_numbers.size() <= 1)
		throw std::runtime_error("not enough numbers to find a span");

	std::vector<int> sorted_numbers = _numbers;
	std::sort(sorted_numbers.begin(), sorted_numbers.end());

	long shortest = std::numeric_limits<long>::max();

	for (size_t i = 1; i < sorted_numbers.size(); i++)
	{
		long span = static_cast<long>(sorted_numbers[i]) - static_cast<long>(sorted_numbers[i - 1]);
		if (span < shortest)
			shortest = span;
	}
	return shortest;
}

long Span::longestSpan() const
{
	if (_numbers.size() <= 1)
		throw std::runtime_error("not enough numbers to find a span");

	int min = *std::min_element(_numbers.begin(), _numbers.end());
	int max = *std::max_element(_numbers.begin(), _numbers.end());

	return static_cast<long>(max) - static_cast<long>(min);
}
