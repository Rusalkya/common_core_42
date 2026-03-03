/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 09:53:33 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/04 09:59:30 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "Array.hpp"

static void printTitle(const std::string& title)
{
    std::cout << "\n--- " << title << " ---" << std::endl;
}

int main()
{
    printTitle("Empty array");
    Array<int> a;
    std::cout << "a.size() = " << a.size() << std::endl;

    printTitle("Fill array with values");
    Array<int> b(7);
    for (unsigned int i = 0; i < b.size(); ++i)
        b[i] = i * i;

    for (unsigned int i = 0; i < b.size(); ++i)
        std::cout << "[" << i << "]=" << b[i] << " ";
    std::cout << std::endl;

    printTitle("Copy constructor deep copy check");
    Array<int> c(b);
    b[3] = 9999;

    std::cout << "b[3] = " << b[3] << std::endl;
    std::cout << "c[3] = " << c[3] << " (must be unchanged)" << std::endl;

    printTitle("Assignment operator deep copy check");
    Array<int> d(3);
    d = b;
    b[0] = -42;

    std::cout << "b[0] = " << b[0] << std::endl;
    std::cout << "d[0] = " << d[0] << " (must be unchanged)" << std::endl;

    printTitle("Const access test");
    const Array<int> constRef(d);
    std::cout << "constRef[2] = " << constRef[2] << std::endl;

    printTitle("Out of range exception test");
    try
    {
        std::cout << b[100] << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    printTitle("Template test with strings");
    Array<std::string> words(4);
    words[0] = "42";
    words[1] = "Network";
    words[2] = "C++";
    words[3] = "Templates";

    for (unsigned int i = 0; i < words.size(); ++i)
        std::cout << words[i] << " | ";
    std::cout << std::endl;

    printTitle("Modify copied string array");
    Array<std::string> wordsCopy = words;
    words[1] = "Changed";

    std::cout << "Original: " << words[1] << std::endl;
    std::cout << "Copy:     " << wordsCopy[1] << std::endl;

    printTitle("End of tests");
    return 0;
}