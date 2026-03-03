/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:31:07 by clfouger          #+#    #+#             */
/*   Updated: 2026/01/07 10:56:30 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat{
		private:
			const std::string	_name;
			int					_grade;
		
		public:
			Bureaucrat(void);
			Bureaucrat(const std::string &name, int grade);
			Bureaucrat(const Bureaucrat &src);
			~Bureaucrat(void);

			Bureaucrat&			operator=(const Bureaucrat &src);
			const std::string&	getName(void) const;
			int					getGrade(void) const;
			void				upGrade(void);
			void				downGrade(void);

			class GradeTooHighException : public std::exception{
				public: const char* what() const throw(){
					return "Grade is too high!";
				}
			};

			class GradeTooLowException : public std::exception{
				public: const char* what() const throw(){
					return "Grade is too low!";
				}
			};
};

std::ostream& operator<<(std::ostream &out, const Bureaucrat& bureaucrat);

#endif