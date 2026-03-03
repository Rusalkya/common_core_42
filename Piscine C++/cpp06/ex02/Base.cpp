/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:13:20 by clfouger          #+#    #+#             */
/*   Updated: 2026/01/23 18:19:55 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base* generate()
{
	int random = rand() % 3;
	if (random == 0)
		return new A();
	else if (random == 1)
		return new B();
	else
		return new C();
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "p: A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "p: B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "p: C" << std::endl;
	else
		std::cout << "Unknown type" << std::endl;
}

void identify(Base& p)
{
	try {
		A& a = dynamic_cast<A&>(p);
		std::cout << "p: A" << std::endl;
		(void)a;
		return ;
	} catch (...) {}

	try {
		B& b = dynamic_cast<B&>(p);
		std::cout << "p: B" << std::endl;
		(void)b;
		return ;
	} catch (...) {}

	try {
		C& c = dynamic_cast<C&>(p);
		std::cout << "p: C" << std::endl;
		(void)c;
		return ;
	} catch (...) {
	}
	std::cout << "Uknow type" << std::endl;
}