/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:15:51 by clfouger          #+#    #+#             */
/*   Updated: 2026/01/09 13:32:58 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(): AForm("PresidentialPardonForm", 25, 5),
	_target("defaulttarget") 
{}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target):
	AForm("PresidentialPardonForm", 25, 5), _target(target)
{}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& src): AForm(src),
	_target(src._target)
{}

PresidentialPardonForm::~PresidentialPardonForm()
{}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& src)
{
	if (this != &src)
	{
		AForm::operator=(src);
		_target = src._target;
	}
	return *this;
}

const std::string&	PresidentialPardonForm::getTarget(void) const
{
	return _target;
}

void	PresidentialPardonForm::execute(const Bureaucrat& executor) const
{
	check_signed_toExec(executor, getExec());
	std::cout << getTarget() << " has been pardonned by Zaphos Beeblerox" << std::endl;
}
