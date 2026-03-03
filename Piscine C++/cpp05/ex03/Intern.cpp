/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:02:13 by clfouger          #+#    #+#             */
/*   Updated: 2026/01/10 14:56:03 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include <iostream>

struct FormPair {
	std::string name;
	AForm* (*create)(const std::string&);
};

Intern::Intern() {}

Intern::Intern(const Intern& src) {
	(void)src;
}

Intern::~Intern() {}

Intern& Intern::operator=(const Intern& src) {
	(void)src;
	return *this;
}

AForm* createShrubbery(const std::string& target) {
	return new ShrubberyCreationForm(target);
}

AForm* createRobotomy(const std::string& target) {
	return new RobotomyRequestForm(target);
}

AForm* createPardon(const std::string& target) {
	return new PresidentialPardonForm(target);
}

AForm*	Intern::makeForm(const std::string& nameform, const std::string& target) const
{
	FormPair forms[3] = {
		{"shrubbery creation", createShrubbery},
		{"robotomy request", createRobotomy},
		{"presidential pardon", createPardon}
	};
	
	for (int i = 0; i < 3 ; ++i)
	{
		if (nameform == forms[i].name)
		{
			std::cout << "Intern creates " << forms[i].name << std::endl;
			return forms[i].create(target);
		}
	}
	std::cout << "Intern can't create form " << nameform << std::endl;
	return NULL;
}