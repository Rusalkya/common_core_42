/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:13:07 by clfouger          #+#    #+#             */
/*   Updated: 2026/01/23 17:37:42 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main()
{
	Data data;
	data.i = 42;
	data.f = 3.14f;
	data.d = 2.71825;
	data.c = 'A';

	std::cout << "Original Data address: " << &data << std::endl;
	std::cout << "Original data.i = " << data.i << std::endl;
	std::cout << "Original data.f = " << data.f << std::endl;
	std::cout << "Original data.d = " << data.d << std::endl;
	std::cout << "Original data.c = " << data.c << std::endl;
	std::cout << std::endl;

	// serialisation
	uintptr_t serialized = Serializer::serialize(&data);
	std::cout << "Serialized value: " << serialized << std::endl;

	// deserialization
	Data* deserialized = Serializer::deserialize(serialized);
	std::cout << "Deserialized address: " << deserialized << std::endl;
	std::cout << std::endl;

	// verif que les deux pointeurs sont identiques
	if (deserialized == &data)
	{
		std::cout << "✓ Pointers are equal!" << std::endl;
		std::cout << "Data members from deserialized pointer:" << std::endl;
		std::cout << "deserialized->i = " << deserialized->i << std::endl;
		std::cout << "deserialized->f = " << deserialized->f << std::endl;
		std::cout << "deserialized->d = " << deserialized->d << std::endl;
		std::cout << "deserialized->c = " << deserialized->c << std::endl;
	}
	else
	{
		std::cout << "✗ Pointers are NOT equal!" << std::endl;
	}

	return 0;
}