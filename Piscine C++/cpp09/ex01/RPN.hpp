/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:38:42 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/14 17:36:39 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <string>

class RPN
{

	private:
			std::stack<int>	_stack;
			std::string		_expression;
			RPN();
			void parseExpression();
			void calcul();
	public:
			RPN(const std::string &expression);
			RPN(const RPN &other);
			RPN &operator=(const RPN &other);
			~RPN();
};

#endif