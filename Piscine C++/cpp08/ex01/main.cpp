/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:10:56 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/11 17:41:57 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(std::time(NULL));

	try
	{
		std::cout << "=== Remplissage avec nombres aléatoires ===" << std::endl;

		const unsigned int SIZE = 100;
		Span sp(SIZE);

		//vector rempli de valeurs random
		std::vector<int> values;
		values.reserve(SIZE);

		for (unsigned int i = 0; i < SIZE; ++i)
			values.push_back(std::rand());
		sp.addNumber(values.begin(), values.end());

		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span : " << sp.longestSpan() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}


// int main()
// {
// Span sp = Span(5);
// sp.addNumber(6);
// sp.addNumber(3);
// sp.addNumber(17);
// sp.addNumber(9);
// sp.addNumber(11);
// std::cout << sp.shortestSpan() << std::endl;
// std::cout << sp.longestSpan() << std::endl;
// return 0;
// }