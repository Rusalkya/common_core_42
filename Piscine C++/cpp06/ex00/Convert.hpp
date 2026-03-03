/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:39:26 by clfouger          #+#    #+#             */
/*   Updated: 2026/01/19 17:26:03 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_HPP
#define CONVERT_HPP

#include <string>
#include <iostream>
#include <cstdlib>
#include <limits.h>
#include <cerrno>
#include <cmath>

class ScalarConverter {
	private:
			ScalarConverter();
	public:
		static void convert(const std::string &str);
		
};

#endif