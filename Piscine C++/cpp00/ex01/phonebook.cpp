/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:32:32 by clfouger          #+#    #+#             */
/*   Updated: 2025/12/01 15:12:57 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

static	std::string		troncstr(const std::string &str)
{
	if (str.length() > 10)
		return (str.substr(0, 9) + ".");
	return (str);
}

Phonebook::Phonebook()
{
	_i = 0;
}

Phonebook::~Phonebook() {}

void	Phonebook::displaycontacts() const
{
	if (!_i)
	{
		std::cout << "\033[31mPlease add a contact before trying to display the contacts.\033[0m" << std::endl;
		return;
	}	
	std::cout << "___________________________________________" << std::endl;
	std::cout << "|    Index|First name| Last name| Nickname|" << std::endl;
	std::cout << "___________________________________________" << std::endl;
	for (int j = 0; j < 8; j++)
	{
		if (j >= _i)
			break;
		std::cout << "|" << std::setw(10) << std::right << j + 1 
			<< "|" << std::setw(10) << std::right 
			<< troncstr(_contacts[j].getfirstname())
			<< "|" << std::setw(10) << std::right 
			<< troncstr(_contacts[j].getlastname())
			<< "|" << std::setw(10) << std::right 
			<< troncstr(_contacts[j].getnickname())
			<< "|" << std::endl;
		std::cout << "___________________________________________"
			<< std::endl;
	}
}

void	Phonebook::addcontact()
{
	std::string		input;
	Contact	new_contact;
	
	while (1)
	{
		std::cout << "enter first name" << std::endl << ">";
		if (!std::getline(std::cin, input))
		{
			std::cout << "\033[31mEOF detected. End of program.\033[0m" << std::endl;
			exit(0);
		}
		new_contact.setfirstname(input);
		if (!input.empty() && input != "")
			break;
	}

	while (1)
	{
		std::cout << "enter last name" << std::endl << ">";
		if (!std::getline(std::cin, input))
		{
			std::cout << "\033[31mEOF detected. End of program.\033[0m" << std::endl;
			exit(0);
		}
		new_contact.setlastname(input);
		if (!input.empty() && input != "")
			break;
	}

	while (1)
	{
		std::cout << "enter nickname" << std::endl << ">";
		if (!std::getline(std::cin, input))
		{
			std::cout << "\033[31mEOF detected. End of program.\033[0m" << std::endl;
			exit(0);
		}
		new_contact.setnickname(input);
		if (!input.empty() && input != "")
			break;
	}
	
	while (1)
	{
		std::cout << "enter darkest secret" << std::endl << ">";
		if (!std::getline(std::cin, input))
		{
			std::cout << "\033[31mEOF detected. End of program.\033[0m" << std::endl;
			exit(0);
		}
		new_contact.setdarkestsecret(input);
		if (!input.empty() && input != "")
			break;
	}

	while (1)
	{
		std::cout << "enter phone number" << std::endl << ">";
		if (!std::getline(std::cin, input))
		{
			std::cout << "\033[31mEOF detected. End of program.\033[0m" << std::endl;
			exit(0);
		}
		new_contact.setphonenumber(input);
		if (!input.empty() && input != "")
			break;
	}
	_contacts[_i % 8] = new_contact;
	_i++;
}

void	Phonebook::displayonecontact(int i) const
{
	if (i < 1 || i > 8 || i > _i)
	{
		std::cout << "\033[31mInvalid index!\033[0m" << std::endl;
		return;
	}
	std::cout << "First name : \033[32m" << _contacts[i - 1].getfirstname() << "\033[0m" << std::endl;
	std::cout << "Last name : \033[32m" << _contacts[i - 1].getlastname() << "\033[0m" << std::endl;
	std::cout << "Nickname : \033[32m" << _contacts[i - 1].getnickname() << "\033[0m" << std::endl;
	std::cout << "Phone Number : \033[32m" << _contacts[i - 1].getphonenumber() << "\033[0m" << std::endl;
	std::cout << "Darkest secret : \033[32m" << _contacts[i - 1].getdarkestsecret() << "\033[0m" << std::endl;
}

int	Phonebook::geti() const
{
	return(_i);
}
