/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:55:15 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/04 09:54:35 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <string>
#include <stdexcept>

template <typename T>
class Array
{
	private:
		T* _array;
		size_t _size;
	
	public:
		Array() : _array(NULL), _size(0) {}
		
		Array(unsigned int n) : _array(new T[n]()), _size(n) {}
		
		Array(const Array& other) : _array(NULL), _size(other._size)
		{
			_array = new T[_size];
			for (size_t i = 0; i < _size; ++i)
				_array[i] = other._array[i];
		}

		~Array() 
		{
			delete[] _array;
		}
		
		Array& operator=(const Array& other)
		{
			if (this != &other)
			{
				delete[] _array;
				_size = other._size;
				if (_size > 0)
				{
					_array = new T[_size];
					for (size_t i = 0; i < _size; ++i)
						_array[i] = other._array[i];
				}
				else
				{
					_array = NULL;
				}
			}
			return *this;
		}

		unsigned int size() const
		{
			return _size;
		}

		T &operator[] (unsigned int index);
		
		const T &operator[](unsigned int index) const;
};

#include "Array.tpp"

#endif
