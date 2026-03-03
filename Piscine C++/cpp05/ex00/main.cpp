/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:44:00 by clfouger          #+#    #+#             */
/*   Updated: 2026/01/06 20:50:48 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

int main() {
	std::cout << CYAN << "===== CONSTRUCTION VALIDE =====" << RESET << std::endl;
	try {
		Bureaucrat a("Wanis", 42);
		std::cout << GREEN << a << RESET << std::endl;

		a.upGrade();
		std::cout << "Après increment: " << GREEN << a << RESET << std::endl;

		a.downGrade();
		std::cout << "Après decrement: " << GREEN << a << RESET << std::endl;
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n===== CONSTRUCTION GRADE TROP HAUT =====" << RESET << std::endl;
	try {
		Bureaucrat b("Emma", 0);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n===== CONSTRUCTION GRADE TROP BAS =====" << RESET << std::endl;
	try {
		Bureaucrat c("Klaus", 200);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n===== INCREMENT AU MAX =====" << RESET << std::endl;
	try {
		Bureaucrat d("Johanna", 1);
		std::cout << GREEN << d << RESET << std::endl;
		d.upGrade();
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n===== DECREMENT AU MIN =====" << RESET << std::endl;
	try {
		Bureaucrat e("Illan", 150);
		std::cout << GREEN << e << RESET << std::endl;
		e.downGrade();
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n===== TEST COPIE & ASSIGNATION =====" << RESET << std::endl;
	try {
		Bureaucrat f("Andrea", 100);
		Bureaucrat g = f;
		Bureaucrat h("Dilan", 50);
		h = f;

		std::cout << "f: " << GREEN << f << RESET << std::endl;
		std::cout << "g (copie de f): " << GREEN << g << RESET << std::endl;
		std::cout << "h (assigné à f): " << GREEN << h << RESET << std::endl;
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	return 0;
}