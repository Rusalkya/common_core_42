/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:57:32 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/10 13:34:03 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

#include <iostream>
#include <list>
#include <stack>

int main()
{
	std::cout << "--- MutantStack test ---" << std::endl;
	MutantStack<int> mstack;
	std::cout << "push: 5" << std::endl;
	mstack.push(5);
	std::cout << "push: 17" << std::endl;
	mstack.push(17);
	std::cout << "top: " << mstack.top() << std::endl;
	mstack.pop();
	std::cout << "size after pop: " << mstack.size() << std::endl;
	std::cout << "push: 3, 5, 737, 0" << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);
	std::cout << "iterate:" << std::endl;
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << "  " << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);

	std::cout << "\n--- std::list test ---" << std::endl;
	std::list<int> lst;
	std::cout << "push_back: 5" << std::endl;
	lst.push_back(5);
	std::cout << "push_back: 17" << std::endl;
	lst.push_back(17);
	std::cout << "back: " << lst.back() << std::endl;
	lst.pop_back();
	std::cout << "size after pop_back: " << lst.size() << std::endl;
	std::cout << "push_back: 3, 5, 737, 0" << std::endl;
	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	
	lst.push_back(0);
	std::cout << "iterate:" << std::endl;
	std::list<int>::iterator lit = lst.begin();
	std::list<int>::iterator lite = lst.end();
	++lit;
	--lit;
	while (lit != lite)
	{
		std::cout << "  " << *lit << std::endl;
		++lit;
	}
	return 0;
}