/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:02:17 by clfouger          #+#    #+#             */
/*   Updated: 2025/12/15 15:07:39 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() : _rawBits(0)
{
}

Fixed::Fixed(const Fixed& other)
{
    *this = other;
}

Fixed& Fixed::operator=(const Fixed& other)
{
    if (this != &other)
        this->_rawBits = other._rawBits;
    return *this;
}

Fixed::~Fixed()
{
}

Fixed::Fixed(const int n)
{
    _rawBits = n << _fractionalBits;
}

Fixed::Fixed(const float f)
{
    _rawBits = roundf(f * (1 << _fractionalBits));
}

int Fixed::getRawBits(void) const
{
    return _rawBits;
}

void Fixed::setRawBits(int const raw)
{
    _rawBits = raw;
}

float Fixed::toFloat(void) const
{
    return (float)_rawBits / (1 << _fractionalBits);
}

int Fixed::toInt(void) const
{
    return _rawBits >> _fractionalBits;
}

bool Fixed::operator>(const Fixed& other) const { return _rawBits > other._rawBits; }
bool Fixed::operator<(const Fixed& other) const { return _rawBits < other._rawBits; }
bool Fixed::operator>=(const Fixed& other) const { return _rawBits >= other._rawBits; }
bool Fixed::operator<=(const Fixed& other) const { return _rawBits <= other._rawBits; }
bool Fixed::operator==(const Fixed& other) const { return _rawBits == other._rawBits; }
bool Fixed::operator!=(const Fixed& other) const { return _rawBits != other._rawBits; }

Fixed Fixed::operator+(const Fixed& other) const
{
    Fixed result;
    result._rawBits = this->_rawBits + other._rawBits;
    return result;
}

Fixed Fixed::operator-(const Fixed& other) const
{
    Fixed result;
    result._rawBits = this->_rawBits - other._rawBits;
    return result;
}

Fixed Fixed::operator*(const Fixed& other) const
{
    Fixed result;
    long tmp = (long)this->_rawBits * (long)other._rawBits;
    result._rawBits = tmp >> _fractionalBits;
    return result;
}

Fixed Fixed::operator/(const Fixed& other) const
{
    Fixed result;
    long tmp = ((long)this->_rawBits << _fractionalBits) / other._rawBits;
    result._rawBits = tmp;
    return result;
}

Fixed& Fixed::operator++()
{
    _rawBits++;
    return *this;
}

Fixed Fixed::operator++(int)
{
    Fixed temp(*this);
    _rawBits++;
    return temp;
}

Fixed& Fixed::operator--()
{
    _rawBits--;
    return *this;
}

Fixed Fixed::operator--(int)
{
    Fixed temp(*this);
    _rawBits--;
    return temp;
}

Fixed& Fixed::min(Fixed& a, Fixed& b)
{
    return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
    return (a < b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b)
{
    return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
    return (a > b) ? a : b;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed)
{
    os << fixed.toFloat();
    return os;
}