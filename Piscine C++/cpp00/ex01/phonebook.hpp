/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:32:30 by clfouger          #+#    #+#             */
/*   Updated: 2025/12/01 12:50:52 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "contact.hpp"

class Phonebook
{
private:
		Contact	_contacts[8];
		int		_i;
public:
		Phonebook();
		~Phonebook();
		void	addcontact();
		void	displaycontacts() const;
		void	displayonecontact(int i) const;
		int		geti() const;
};

#endif
