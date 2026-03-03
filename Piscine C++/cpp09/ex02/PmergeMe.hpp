/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:15:46 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/16 11:31:15 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <sys/time.h>

class PmergeMe
{
	private:
		std::vector<int> _vector;
		std::deque<int> _deq;
		
		void mergeInsertSortVector();
		void mergeInsertSortDeque();
		void fillVector(char **argv);
		void fillDeque(char **argv);
		void printContainers() const;
	
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		void sort(char **argv);
};

#endif