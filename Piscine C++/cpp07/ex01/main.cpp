/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:43:26 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/03 11:54:39 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

template <typename T>
void increment(T& x)
{
    x += 1;
}

// 2. Fonction qui affiche sans modifier (const ref)
template <typename T>
void printElement(const T& x)
{
    std::cout << x << " ";
}

// 3. Fonction spécifique pour std::string
void toUpper(std::string& s)
{
    for (size_t i = 0; i < s.length(); ++i)
        s[i] = std::toupper(s[i]);
}

int main()
{
    std::cout << "=== Test avec int ===" << std::endl;
    int intArray[] = {1, 2, 3, 4, 5};
    size_t intLen = sizeof(intArray) / sizeof(intArray[0]);

    std::cout << "Avant increment: ";
    iter(intArray, intLen, printElement<int>);
    std::cout << std::endl;

    iter(intArray, intLen, increment<int>);

    std::cout << "Apres increment: ";
    iter(intArray, intLen, printElement<int>);
    std::cout << "\n\n";

    std::cout << "=== Test avec double ===" << std::endl;
    double dblArray[] = {0.5, 1.5, 2.5};
    size_t dblLen = sizeof(dblArray) / sizeof(dblArray[0]);

    std::cout << "Valeurs: ";
    iter(dblArray, dblLen, printElement<double>);
    std::cout << "\n\n";

    std::cout << "=== Test avec std::string ===" << std::endl;
    std::string strArray[] = {"hello", "world", "iter", "template"};
    size_t strLen = sizeof(strArray) / sizeof(strArray[0]);

    std::cout << "Avant toUpper: ";
    iter(strArray, strLen, printElement<std::string>);
    std::cout << std::endl;

    iter(strArray, strLen, toUpper);

    std::cout << "Apres toUpper: ";
    iter(strArray, strLen, printElement<std::string>);
    std::cout << std::endl;

    return 0;
}