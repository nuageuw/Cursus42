/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:17:50 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/18 22:59:54 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_H
#define PMERGEME_H

#include <vector>
#include <string>
#include <list>

class PmergeMe {
public:
    PmergeMe(const std::vector<int>& inputSequence);
    
    void mergeSortList(std::list<int>& lst);
    void mergeSortVector(std::vector<int>& vec);
    void displayResults() const;
    void mergeSortWithVector();
    void mergeSortWithList();

private:
    std::vector<int> sequence;
    std::vector<int> sortedSequenceVector;
    std::vector<int> sortedSequenceList;
    double timeVector;
    double timeList;
};

#endif