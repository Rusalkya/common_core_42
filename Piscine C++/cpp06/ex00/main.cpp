/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:40:57 by clfouger          #+#    #+#             */
/*   Updated: 2026/01/21 19:05:29 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cerr << "usage= ./convert arg" << std::endl;
		return 1;
	}
	ScalarConverter::convert(argv[1]);
	return 0;
}

