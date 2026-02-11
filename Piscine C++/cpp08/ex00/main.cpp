/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 10:58:03 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/06 13:38:03 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

static void	testVector()
{
	std::cout << "\n--- std::vector test ---" << std::endl;

	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(5);
	vec.push_back(10);
	vec.push_back(42);
	vec.push_back(100);

	// Test 1: Chercher une valeur qui existe
	try
	{
		std::vector<int>::iterator it = easyfind(vec, 42);
		std::cout << "Found 42 at index: "
				  << std::distance(vec.begin(), it) << std::endl;
		std::cout << "Value: " << *it << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	// Test 2: Chercher une valeur qui existe (première occurrence)
	try
	{
		std::vector<int>::iterator it = easyfind(vec, 1);
		std::cout << "Found 1 at index: "
				  << std::distance(vec.begin(), it) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	// Test 3: Chercher une valeur qui n'existe pas
	try
	{
		std::vector<int>::iterator it = easyfind(vec, 99);
		std::cout << "Found 99 at index: "
				  << std::distance(vec.begin(), it) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "99 not found (expected): " << e.what() << std::endl;
	}
}

static void	testList()
{
	std::cout << "\n--- std::list test ---" << std::endl;

	std::list<int> lst;
	lst.push_back(7);
	lst.push_back(14);
	lst.push_back(21);
	lst.push_back(28);
	lst.push_back(35);

	// Test 1: Chercher une valeur qui existe au milieu
	try
	{
		std::list<int>::iterator it = easyfind(lst, 21);
		std::cout << "Found 21 in list" << std::endl;
		std::cout << "Value: " << *it << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	// Test 2: Chercher une valeur qui n'existe pas
	try
	{
		std::list<int>::iterator it = easyfind(lst, 50);
		(void)it;
		std::cout << "Found 50 in list" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "50 not found (expected): " << e.what() << std::endl;
	}
}

static void	testDuplicates()
{
	std::cout << "\n--- duplicates test ---" << std::endl;

	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(10);
	vec.push_back(5);  // Duplicate
	vec.push_back(20);
	vec.push_back(5);  // Duplicate

	// Test: Doit trouver la PREMIÈRE occurrence
	try
	{
		std::vector<int>::iterator it = easyfind(vec, 5);
		std::cout << "First 5 at index: "
				  << std::distance(vec.begin(), it) << std::endl;
		std::cout << "Expected index: 0" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}

int main()
{
	std::cout << "Easyfind tests" << std::endl;

	testVector();
	testList();
	testDuplicates();

	std::cout << "\nDone" << std::endl;

	return 0;
}
