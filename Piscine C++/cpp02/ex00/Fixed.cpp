/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:19:10 by clfouger          #+#    #+#             */
/*   Updated: 2025/12/11 14:25:02 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

//cree un objet sans valeur definie = 0 / si je ne cree pas cet objet ca ne compile pas
Fixed::Fixed() : _rawBits(0) {
	std::cout << "Default constructor called" << std::endl;
}

//on cree un nvl objet a partir de celui du dessus
Fixed::Fixed(const Fixed& other){
	std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

//copier l'etat d'un objet dans un objet existant  -> on affecte un contenu qui existe deja
Fixed& Fixed::operator=(const Fixed& other){
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		this->_rawBits = other.getRawBits();
	return *this;
}

Fixed::~Fixed(){
    std::cout << "Destructor called" << std::endl;
}

//va lire la valeur brute stockee dans l'objet 
int	Fixed::getRawBits(void) const{
	std::cout << "getRawBits member function called" << std::endl;
	return this-> _rawBits;
}

//modifie directement la valeur du nombre Fixed-point / est capable de calculer une conversion
void Fixed::setRawBits(int const raw) {
    this->_rawBits = raw;
}
