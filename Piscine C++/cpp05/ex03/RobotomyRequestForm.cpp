/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:44:45 by clfouger          #+#    #+#             */
/*   Updated: 2026/01/09 13:32:58 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(): AForm("RobotomyRequestForm", 72, 45),
												_target("defaultarget")
{}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target):
								AForm("RobotomyRequestForm", 72, 45),
											_target(target)
{}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& src):
											AForm(src), _target(src._target)
{}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm&	RobotomyRequestForm::operator=(const RobotomyRequestForm& src)
{
	if (this != &src)
	{
		AForm::operator=(src);
		_target = src._target;
	}
	return *this;
}

const std::string&		RobotomyRequestForm::getTarget( void ) const
{
	return _target;
}

void			RobotomyRequestForm::execute(const Bureaucrat& executor) const
{
	check_signed_toExec(executor, getExec());
	std::cout << "* some drilling noises *" << std::endl;
	if (std::rand() % 2 == 0)
		std::cout << getTarget() << " has been robotized !" << std::endl;
	else
		std::cout << "The robotomy failed..." << std::endl;
}