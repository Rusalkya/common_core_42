/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:38:50 by clfouger          #+#    #+#             */
/*   Updated: 2026/01/23 18:13:36 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	Base* basePtr = generate();
	std::cout << "Using pointer:" << std::endl;
	identify(basePtr);
	delete basePtr;

	Base& baseRef = *generate();
	std::cout << "Using reference:" << std::endl;
	identify(baseRef);
	delete &baseRef;

	return 0;
}