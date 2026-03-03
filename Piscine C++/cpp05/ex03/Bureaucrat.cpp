/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:39:11 by clfouger          #+#    #+#             */
/*   Updated: 2026/01/09 12:56:35 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(void) : _name("defaultname"), _grade(1) {} //constructeur par default

Bureaucrat::Bureaucrat(const std::string& name, int grade): _name(name)
{
	if (grade < 1)
		throw GradeTooHighException();
	else if (grade > 150)
		throw GradeTooLowException();
	_grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat& src): _name(src._name), _grade(src._grade) {}

Bureaucrat::~Bureaucrat(void) {} //destructeur

Bureaucrat& Bureaucrat::operator=(const Bureaucrat &src)
{
	if (this != &src)
		this->_grade = src.getGrade();
	return *this;
}

const std::string& Bureaucrat::getName(void) const
{
	return _name;
}

int	Bureaucrat::getGrade(void) const
{
	return _grade;
}

void	Bureaucrat::upGrade(void)
{
	if (_grade - 1 < 1)
		throw GradeTooHighException();
	_grade--;
}

void	Bureaucrat::downGrade(void)
{
	if (_grade + 1 > 150)
		throw GradeTooLowException();
	_grade++;
}

std::ostream& operator<<(std::ostream &out, const Bureaucrat& bureaucrat)
{
	out << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
	return out;
}

void	Bureaucrat::signForm(AForm& AForm)
{
	try 
	{
		AForm.beSigned(*this);
		std::cout << this->getName() << " signed " << AForm.getName() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << this->getName() << " couldn't sign " << AForm.getName() << " because "
			<< e.what() << std::endl;
	}
}

void	Bureaucrat::executeForm(AForm& AForm)
{
	try
	{
		AForm.execute(*this);
		std::cout << this->getName() << " executed " << AForm.getName() << std::endl;
	} 
	catch (std::exception& e)
	{
		std::cout << this->getName() << " can't execute " << AForm.getName()
			<< " because " << e.what() << std::endl;
	}
}