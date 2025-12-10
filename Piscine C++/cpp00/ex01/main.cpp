/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:32:25 by clfouger          #+#    #+#             */
/*   Updated: 2025/12/03 09:41:46 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"
#include "contact.hpp"

static void	search_func(const Phonebook &phonebook)
{
	std::string		input;
	int		number;
	phonebook.displaycontacts();
	if (!phonebook.geti())
		return;
	while (1)
	{
		std::cout << "Enter the index of the contact that you want to display : ";
		if (!std::getline(std::cin, input))
		{
			std::cout << "\033[31mEOF detected. End of program.\033[0m" << std::endl;
			exit(0);
		}
		std::istringstream iss(input);
		if (iss >> number && iss.eof())
		{
			if (number > phonebook.geti() || number < 1 || number > 8)
			{
				std::cout << "\033[31mPlease enter a correct index.\033[0m" << std::endl;
				continue ;
			}
			phonebook.displayonecontact(number);
			break;
		}
		else
		{
			std::cout << "\033[31mInvalid input. Please enter a number.\033[0m" << std::endl;
		}
	}
}

int		main(void)
{
	Phonebook	phonebook;
	std::string	input;
	while (1)
	{
		std::cout << "Enter your command [ADD, SEARCH, EXIT]" << std::endl;
		std::cout << ">";
		if (!std::getline(std::cin, input))
		{
			std::cout << "\033[31mEOF detected. End of program.\033[0m" << std::endl;
			return (0);
		}
		else if (input == "EXIT")
			break ;
		else if (input == "ADD")
			phonebook.addcontact();
		else if (input == "SEARCH")
			search_func(phonebook);
	}
	std::cout << "\033[34mmerci, ciao\033[0m" << std::endl;
	return (0);
}