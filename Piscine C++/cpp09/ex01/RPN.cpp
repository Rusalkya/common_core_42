/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:38:39 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/14 18:23:30 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(const std::string &expression) : _expression(expression)
{
	this->parseExpression();
	this->calcul();
}

RPN::RPN(const RPN &other) : _stack(other._stack), _expression(other._expression)
{
}

RPN::RPN() {}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		_stack = other._stack;
		_expression = other._expression;
	}
	return *this;
}

RPN::~RPN() {}

static void char_checking(const std::string &expression)
{
	for (size_t i = 0; i < expression.size(); i++)
	{
		char c = expression[i];

		if (!isdigit(c) && c != ' ' && c != '+' && c != '-' && c != '*' && c != '/')
			throw std::invalid_argument("Error");
	}
}

static void content_checker(const std::string &expression)
{
	int count = 0;

	for (size_t i = 0; i < expression.size(); i++)
	{
		if (expression[i] == ' ')
			continue;

		if (isdigit(expression[i]))
			count++;

		else
		{
			if (count < 2)
				throw std::invalid_argument("Error");

			count--;
		}
	}

	if (count != 1)
		throw std::invalid_argument("Error");
}

void RPN::parseExpression()
{
	if (_expression.empty())
		throw std::invalid_argument("Error");

	char_checking(_expression);

	content_checker(_expression);
}

void RPN::calcul()
{
	for (size_t i = 0; i < _expression.size(); i++)
	{
		char c = _expression[i];

		if (c == ' ')
			continue;

		if (isdigit(c))
		{
			_stack.push(c - '0');
		}
		else
		{
			if (_stack.size() < 2)
				throw std::invalid_argument("Error");

			int b = _stack.top();
			_stack.pop();

			int a = _stack.top();
			_stack.pop();

			switch (c)
			{
				case '+':
					_stack.push(a + b);
					break;

				case '-':
					_stack.push(a - b);
					break;

				case '*':
					_stack.push(a * b);
					break;

				case '/':
					if (b == 0)
						throw std::invalid_argument("Error");

					_stack.push(a / b);
					break;

				default:
					throw std::invalid_argument("Error");
			}
		}
	}

	if (_stack.size() != 1)
		throw std::invalid_argument("Error");

	std::cout << _stack.top() << std::endl;
}
