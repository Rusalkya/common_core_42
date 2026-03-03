/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:02:15 by clfouger          #+#    #+#             */
/*   Updated: 2026/01/07 10:55:01 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include <string>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form {
	private:
		const std::string	_name;
		const int			_toSign;
		const int			_toExec;
		bool				_isSigned;
	
	public:
		Form();
		Form(const std::string &name, int toSign, int toExec);
		Form(const Form &src);
		~Form();
		
		Form&	operator=(const Form &src);
		const std::string& getName(void) const;
		int		getSign(void) const;
		int		getExec(void) const;
		bool	getSigned(void) const;
		
		class GradeTooHighException : public std::exception
		{
			public: const char* what() const throw()
			{
				return "Grade is too high !";
			}
		};
		class GradeTooLowException : public std::exception
		{
			public: const char* what() const throw()
			{
				return "Grade is too low !";
			}
		};

		void	beSigned(const Bureaucrat& bureaucrat);
};

std::ostream& operator<<(std::ostream &out, const Form& Form);

#endif