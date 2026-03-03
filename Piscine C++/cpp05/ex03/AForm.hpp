/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:02:15 by clfouger          #+#    #+#             */
/*   Updated: 2026/01/07 10:55:01 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AForm_HPP
#define AForm_HPP

#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm {
	private:
		const std::string	_name;
		const int			_toSign;
		const int			_toExec;
		bool				_isSigned;
	
	public:
		AForm();
		AForm(const std::string &name, int toSign, int toExec);
		AForm(const AForm &src);
		virtual ~AForm();
		
		AForm&	operator=(const AForm &src);
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

		class IsNotSigned : public std::exception
		{
			public: const char* what() const throw()
			{
				return "Form is not signed !";
			}
		};

		void			beSigned(const Bureaucrat& bureaucrat);
		virtual void	execute(const Bureaucrat& executor) const = 0;
		void			check_signed_toExec(const Bureaucrat& executor, int toExec) const;
};

std::ostream& operator<<(std::ostream &out, const AForm& AForm);

#endif