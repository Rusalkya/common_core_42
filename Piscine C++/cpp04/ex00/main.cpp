/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 11:12:39 by clfouger          #+#    #+#             */
/*   Updated: 2025/12/31 19:41:01 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

int main() 
{
    std::cout << BLUE << "=== Animal Polymorphism Test ===" << RESET << std::endl;
    const Animal* meta = new Animal();
    const Animal* dog  = new Dog();
    const Animal* cat  = new Cat();

    std::cout << GREEN << "Types:" << RESET << std::endl;
    std::cout << " - " << dog->getType() << std::endl;
    std::cout << " - " << cat->getType() << std::endl;
    std::cout << " - " << meta->getType() << std::endl;

    std::cout << YELLOW << "Sounds:" << RESET << std::endl;
    std::cout << "Dog makes: "; dog->makeSound();
    std::cout << "Cat makes: "; cat->makeSound();
    std::cout << "Animal makes: "; meta->makeSound();

    delete meta;
    delete dog;
    delete cat;

    std::cout << CYAN << "\n=== WrongAnimal Polymorphism Test ===" << RESET << std::endl;
    const WrongAnimal* wmeta = new WrongAnimal();
    const WrongAnimal* wcat  = new WrongCat();

    std::cout << GREEN << "Types (Wrong):" << RESET << std::endl;
    std::cout << " - " << wmeta->getType() << std::endl;
    std::cout << " - " << wcat->getType() << " (should be WrongCat)" << std::endl;

    std::cout << YELLOW << "Sounds (Wrong):" << RESET << std::endl;
    std::cout << "WrongAnimal makes: "; wmeta->makeSound();
    std::cout << "WrongCat makes (unexpected): "; wcat->makeSound();

    delete wmeta;
    delete wcat;

    std::cout << MAGENTA << "\n=== End of Tests ===" << RESET << std::endl;
    return 0;
}