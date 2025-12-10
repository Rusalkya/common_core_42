/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:32:21 by clfouger          #+#    #+#             */
/*   Updated: 2025/12/01 14:40:14 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "contact.hpp"

Contact::Contact(){}
Contact::~Contact(){}

void	Contact::setfirstname(const std::string &firstname)
{
	_firstname = firstname;
}

void	Contact::setlastname(const std::string &lastname)
{
	_lastname = lastname;	
}

void	Contact::setnickname(const std::string &nickname)
{
	_nickname = nickname;
}

void	Contact::setdarkestsecret(const std::string &darkestsecret)
{
	_darkestsecret = darkestsecret;
}

void	Contact::setphonenumber(const std::string &phonenumber)
{
	_phonenumber = phonenumber;
}

std::string		Contact::getfirstname() const
{
	return(_firstname);
}

std::string		Contact::getlastname() const
{
	return(_lastname);
}

std::string		Contact::getnickname() const
{
	return(_nickname);
}

std::string		Contact::getdarkestsecret() const
{
	return(_darkestsecret);
}

std::string		Contact::getphonenumber() const
{
	return(_phonenumber);
}