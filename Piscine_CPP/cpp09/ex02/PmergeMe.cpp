/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:18:04 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/20 18:57:49 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.h"
#include <algorithm>
#include <iostream>
#include <list>
#include <ctime>
#include <iomanip>


PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const std::vector<int>& inputSequence) : sequence(inputSequence) {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) {
    sequence = other.sequence;
    sortedSequenceVector = other.sortedSequenceVector;
    sortedSequenceList = other.sortedSequenceList;
    timeVector = other.timeVector;
    timeList = other.timeList;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        sequence = other.sequence;
        sortedSequenceVector = other.sortedSequenceVector;
        sortedSequenceList = other.sortedSequenceList;
        timeVector = other.timeVector;
        timeList = other.timeList;
    }
    return *this;
}

void PmergeMe::mergeSortWithVector() {
    clock_t start = clock();
    sortedSequenceVector = sequence;
    mergeSortVector(sortedSequenceVector);
    clock_t end = clock();
    timeVector = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

void PmergeMe::mergeSortWithList() {
    clock_t start = clock();
    std::list<int> tempList(sequence.begin(), sequence.end());
    mergeSortList(tempList);
    sortedSequenceList.assign(tempList.begin(), tempList.end());
    clock_t end = clock();
    timeList = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

void PmergeMe::displayResults() const {
    std::cout << "Before: ";
    for (std::vector<int>::const_iterator it = sequence.begin(); it != sequence.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "After: ";
    for (std::vector<int>::const_iterator it = sortedSequenceVector.begin(); it != sortedSequenceVector.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Time to process a range of " << sequence.size() << " elements with std::vector: " << std::fixed << std::setprecision(6) << timeVector << " us" << std::endl;
    std::cout << "Time to process a range of " << sequence.size() << " elements with std::list: " << std::fixed << std::setprecision(6) << timeList << " us" << std::endl;
}

void PmergeMe::mergeSortVector(std::vector<int>& vec) {
    if (vec.size() <= 1) {
        return;
    }

    std::size_t middle = vec.size() / 2;
    std::vector<int> left(vec.begin(), vec.begin() + middle);
    std::vector<int> right(vec.begin() + middle, vec.end());

    mergeSortVector(left);
    mergeSortVector(right);

    std::vector<int>::iterator itLeft = left.begin();
    std::vector<int>::iterator itRight = right.begin();
    std::vector<int>::iterator itVec = vec.begin();

    while (itLeft != left.end() && itRight != right.end()) {
        if (*itLeft < *itRight) {
            *itVec++ = *itLeft++;
        } else {
            *itVec++ = *itRight++;
        }
    }

    while (itLeft != left.end()) {
        *itVec++ = *itLeft++;
    }

    while (itRight != right.end()) {
        *itVec++ = *itRight++;
    }
}

void PmergeMe::mergeSortList(std::list<int>& lst) {
    if (lst.size() <= 1) {
        return;
    }

    std::size_t middle = lst.size() / 2;
    std::list<int>::iterator it = lst.begin();
    std::advance(it, middle);
    std::list<int> left(lst.begin(), it);
    std::list<int> right(it, lst.end());

    mergeSortList(left);
    mergeSortList(right);

    std::list<int>::iterator itLeft = left.begin();
    std::list<int>::iterator itRight = right.begin();
    std::list<int>::iterator itLst = lst.begin();

    while (itLeft != left.end() && itRight != right.end()) {
        if (*itLeft < *itRight) {
            *itLst++ = *itLeft++;
        } else {
            *itLst++ = *itRight++;
        }
    }

    while (itLeft != left.end()) {
        *itLst++ = *itLeft++;
    }

    while (itRight != right.end()) {
        *itLst++ = *itRight++;
    }
}
