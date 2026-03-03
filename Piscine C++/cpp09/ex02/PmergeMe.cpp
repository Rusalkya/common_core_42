/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:15:43 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/16 16:39:58 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//_constructeurs et destructeurs_________________________________

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	_vector = other._vector;
	_deq = other._deq;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vector = other._vector;
		_deq = other._deq;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

//_remplir les containers_______________________

void PmergeMe::fillVector(char **argv)
{
	for (int i = 1; argv[i]; i++)
	{
		std::istringstream iss(argv[i]);
		int value;
		if (!(iss >> value) || value < 0)
			throw std::runtime_error("Error");
		_vector.push_back(value);
	}
}

void PmergeMe::fillDeque(char **argv)
{
	for (int i = 1; argv[i]; i++)
	{
		std::istringstream iss(argv[i]);
		int value;
		if (!(iss >> value) || value < 0)
			throw std::runtime_error("Error");
		_deq.push_back(value);
	}
}

//_fonction d'affichage______________________________________________

void PmergeMe::printContainers() const
{
	std::cout << "Vector : ";
	for (size_t i = 0; i < _vector.size(); i++)
		std::cout << _vector[i] << " ";
	std::cout << std::endl;
	std::cout << "Deque : ";
	for (size_t i = 0; i < _deq.size(); i++)
		std::cout << _deq[i] << " ";
	std::cout << std::endl;
}

//_tri dans les containers_______________________________________________

void PmergeMe::mergeInsertSortVector()
{
	if (_vector.size() <= 1)
		return;

	std::vector<int> mainChain;
	std::vector<int> pending;

	//creation des paires
	for (size_t i = 0; i < _vector.size(); i += 2)
	{
		if (i + 1 < _vector.size())
		{
			if (_vector[i] > _vector[i + 1])
			{
				mainChain.push_back(_vector[i]);
				pending.push_back(_vector[i + 1]);
			}
			else
			{
				mainChain.push_back(_vector[i + 1]);
				pending.push_back(_vector[i]);
			}
		}
		else
			pending.push_back(_vector[i]);
	}

	//tri des grands nombres
	std::sort(mainChain.begin(), mainChain.end());


	//insertion des petits
	for (size_t i = 0; i < pending.size(); i++)
	{
		std::vector<int>::iterator pos;

		pos = std::lower_bound(
			mainChain.begin(),
			mainChain.end(),
			pending[i]);

		mainChain.insert(pos, pending[i]);
	}

	_vector = mainChain;
}

void PmergeMe::mergeInsertSortDeque()
{
	if (_deq.size() <= 1)
		return;
	std::deque<int> mainChain;
	std::deque<int> pending;
	for (size_t i = 0; i < _deq.size(); i += 2)
	{
		if (i + 1 < _deq.size())
		{
			if (_deq[i] > _deq[i + 1])
			{
				mainChain.push_back(_deq[i]);
				pending.push_back(_deq[i + 1]);
			}
			else
			{
				mainChain.push_back(_deq[i + 1]);
				pending.push_back(_deq[i]);
			}
		}
		else
			pending.push_back(_deq[i]);
	}
	std::sort(mainChain.begin(), mainChain.end());
	for (size_t i = 0; i < pending.size(); i++)
	{
		std::deque<int>::iterator pos;
		pos = std::lower_bound(
			mainChain.begin(),
			mainChain.end(),
			pending[i]);

		mainChain.insert(pos, pending[i]);
	}
	_deq = mainChain;
}

//_mesure du temps______________________________________________

static long getTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}
//_________________________________________

void PmergeMe::sort(char **argv)
{

	fillVector(argv);
	fillDeque(argv);
	std::cout << "Before: ";
	for (size_t i = 0; i < _vector.size(); i++)
		std::cout << _vector[i] << " ";
	std::cout << std::endl;
	long startVec = getTime();
	mergeInsertSortVector();
	long endVec = getTime();
	long startDeq = getTime();
	mergeInsertSortDeque();
	long endDeq = getTime();
	std::cout << "After: ";
	for (size_t i = 0; i < _vector.size(); i++)
		std::cout << _vector[i] << " ";
	std::cout << std::endl;
	std::cout
	<< "Time to process a range of "
	<< _vector.size()
	<< " elements with std::vector : "
	<< (endVec - startVec)
	<< " us"
	<< std::endl;
	std::cout
	<< "Time to process a range of "
	<< _deq.size()
	<< " elements with std::deque : "
	<< (endDeq - startDeq)
	<< " us"
	<< std::endl;
}
