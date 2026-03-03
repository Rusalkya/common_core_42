/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:44:00 by clfouger          #+#    #+#             */
/*   Updated: 2026/01/16 12:38:50 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

int main() {
	std::srand(std::time(NULL)); // initialise le hasard

	std::cout << CYAN << "=== SHRUBBERY : signature & exécution OK ===" << RESET << std::endl;
	try {
		Bureaucrat emma("Emma", 1);
		ShrubberyCreationForm form("garden");
		emma.signForm(form);
		emma.executeForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== SHRUBBERY : exécution sans signature ===" << RESET << std::endl;
	try {
		Bureaucrat klaus("Klaus", 1);
		ShrubberyCreationForm form("forest");
		klaus.executeForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== SHRUBBERY : signature refusée (grade bas) ===" << RESET << std::endl;
	try {
		Bureaucrat low("Low", 150);
		ShrubberyCreationForm form("city");
		low.signForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== SHRUBBERY : exécution refusée (grade bas) ===" << RESET << std::endl;
	try {
		Bureaucrat signer("Signer", 1);
		Bureaucrat executor("Executor", 150);
		ShrubberyCreationForm form("park");
		signer.signForm(form);
		executor.executeForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	// std::cout << CYAN << "\n=== SHRUBBERY : double exécution ===" << RESET << std::endl;
	// try {
	// 	Bureaucrat boss("Boss", 1);
	// 	ShrubberyCreationForm form("yard");
	// 	boss.signForm(form);
	// 	boss.executeForm(form);
	// 	boss.executeForm(form); // autorisé, recrée le fichier
	// } catch (std::exception& e) {
	// 	std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	// }

	std::cout << CYAN << "\n=== ROBOTOMY : success ou fail ===" << RESET << std::endl;
	try {
		Bureaucrat roboto("Nono le robot", 1);
		RobotomyRequestForm form("marvin");
		roboto.signForm(form);
		for (int i = 0; i < 5; ++i)
			roboto.executeForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== ROBOTOMY : exécution refusée sans signature ===" << RESET << std::endl;
	try {
		Bureaucrat exec("Exec", 1);
		RobotomyRequestForm form("targetX");
		exec.executeForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== PARDON : exécution OK ===" << RESET << std::endl;
	try {
		Bureaucrat pres("Prez", 1);
		PresidentialPardonForm form("Trillian");
		pres.signForm(form);
		pres.executeForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== PARDON : refusé (pas signé) ===" << RESET << std::endl;
	try {
		Bureaucrat exec("Exec", 1);
		PresidentialPardonForm form("Ford");
		exec.executeForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	std::cout << CYAN << "\n=== PARDON : refusé (grade trop bas) ===" << RESET << std::endl;
	try {
		Bureaucrat low("LowGuy", 150);
		PresidentialPardonForm form("Wanis");
		low.signForm(form);
		low.executeForm(form);
	} catch (std::exception& e) {
		std::cerr << RED << "Erreur : " << e.what() << RESET << std::endl;
	}

	return 0;
}