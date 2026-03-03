/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:44:00 by clfouger          #+#    #+#             */
/*   Updated: 2026/01/10 16:51:40 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Bureaucrat.hpp"
#include "Intern.hpp"

#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

int main() {
	std::srand(std::time(NULL));

	Intern someRandomIntern;
	AForm* form;
	
	std::cout << CYAN << "=== TEST 1: Intern creates shrubbery creation ===" << RESET << std::endl;
	try {
		form = someRandomIntern.makeForm("shrubbery creation", "home");
		if (form) {
			Bureaucrat johanna("Johanna", 1);
			johanna.signForm(*form);
			johanna.executeForm(*form);
			delete form;
		}
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== TEST 2: Intern creates robotomy request ===" << RESET << std::endl;
	try {
		form = someRandomIntern.makeForm("robotomy request", "Bender");
		if (form) {
			Bureaucrat wanis("Wanis", 1);
			wanis.signForm(*form);
			wanis.executeForm(*form);
			delete form;
		}
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== TEST 3: Intern creates presidential pardon ===" << RESET << std::endl;
	try {
		form = someRandomIntern.makeForm("presidential pardon", "Arthur Dent");
		if (form) {
			Bureaucrat chief("Chief", 1);
			chief.signForm(*form);
			chief.executeForm(*form);
			delete form;
		}
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== TEST 4: Intern with unknown form ===" << RESET << std::endl;
	try {
		form = someRandomIntern.makeForm("unknown form", "target");
		if (form) {
			delete form;
		}
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== TEST 5: Multiple forms creation ===" << RESET << std::endl;
	try {
		AForm* forms[3];
		forms[0] = someRandomIntern.makeForm("shrubbery creation", "garden");
		forms[1] = someRandomIntern.makeForm("robotomy request", "target");
		forms[2] = someRandomIntern.makeForm("presidential pardon", "criminal");
		
		Bureaucrat boss("Boss", 1);
		for (int i = 0; i < 3; ++i) {
			if (forms[i]) {
				boss.signForm(*forms[i]);
				boss.executeForm(*forms[i]);
				delete forms[i];
			}
		}
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	return 0;
}