/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:02:12 by clfouger          #+#    #+#             */
/*   Updated: 2026/01/07 10:15:34 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm(void) :_name("defaultname"), _toSign(1), _toExec(1), _isSigned(false) {}

AForm::AForm(const std::string &name, int toSign, int toExec): _name(name),
		_toSign(toSign), _toExec(toExec), _isSigned(false)
{
	if (toSign < 1 || toExec < 1)
		throw GradeTooHighException();
	else if (toSign > 150 || toExec > 150)
		throw GradeTooLowException();
}

AForm::AForm(const AForm &src): _name(src._name), _toSign(src._toSign), 
		_toExec(src._toExec), _isSigned(src._isSigned) {}

AForm::~AForm() {}

AForm& AForm::operator=(const AForm &src)
{
	if (this != &src)
	{
		_isSigned = src._isSigned;
	}
	return *this;
}

const std::string& AForm::getName(void) const
{
	return _name;
}

int	AForm::getSign(void) const
{
	return _toSign;
}

int	AForm::getExec(void) const
{
	return _toExec;
}

bool	AForm::getSigned(void) const
{
	return _isSigned;
}

void	AForm::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > _toSign)
		throw GradeTooLowException();
	_isSigned = true;
}

std::ostream& operator<<(std::ostream &out, const AForm& f)
{
	out << f.getName() << ", AForm " << (f.getSigned() ? "signed" : "not signed")
		<< ", requires grade " << f.getSign() << " to sign and " << f.getExec() 
		<< " to execute.";
	return out;
}

void	AForm::check_signed_toExec(const Bureaucrat& executor, int toExec) const
{
	if (!_isSigned)
		throw IsNotSigned();
	else if (executor.getGrade() > toExec)
		throw GradeTooLowException();
}