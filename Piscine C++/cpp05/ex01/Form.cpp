/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:02:12 by clfouger          #+#    #+#             */
/*   Updated: 2026/01/07 10:15:34 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form(void) :_name("defaultname"), _toSign(1), _toExec(1), _isSigned(false) {}

Form::Form(const std::string &name, int toSign, int toExec): _name(name),
		_toSign(toSign), _toExec(toExec), _isSigned(false)
{
	if (toSign < 1 || toExec < 1)
		throw GradeTooHighException();
	else if (toSign > 150 || toExec > 150)
		throw GradeTooLowException();
}

Form::Form(const Form &src): _name(src._name), _toSign(src._toSign), 
		_toExec(src._toExec), _isSigned(src._isSigned) {}

Form::~Form() {}

Form& Form::operator=(const Form &src)
{
	if (this != &src)
	{
		_isSigned = src._isSigned;
	}
	return *this;
}

const std::string& Form::getName(void) const
{
	return _name;
}

int	Form::getSign(void) const
{
	return _toSign;
}

int	Form::getExec(void) const
{
	return _toExec;
}

bool	Form::getSigned(void) const
{
	return _isSigned;
}

void	Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > _toSign)
		throw GradeTooLowException();
	_isSigned = true;
}

std::ostream& operator<<(std::ostream &out, const Form& f)
{
	out << f.getName() << ", Form " << (f.getSigned() ? "signed" : "not signed")
		<< ", requires grade " << f.getSign() << " to sign and " << f.getExec() 
		<< " to execute.";
	return out;
}