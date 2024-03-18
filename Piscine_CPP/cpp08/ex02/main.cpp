/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:32:37 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/18 10:42:10 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <iostream>
#include <list>
#include <stack>


int main() {
	// MUTANTSTACK OUTPUT
    {
		MutantStack<int> mstack;
    	mstack.push(5);
    	mstack.push(17);
    	std::cout << mstack.top() << std::endl;
    	mstack.pop();
    	std::cout << mstack.size() << std::endl;
    	mstack.push(3);
    	mstack.push(5);
    	mstack.push(737);
    	mstack.push(0);
	
    	MutantStack<int>::iterator it = mstack.begin();
    	MutantStack<int>::iterator ite = mstack.end();
    	++it;
    	--it;
    	while (it != ite) {
    	    std::cout << *it << std::endl;
    	    ++it;
    	}
    	std::stack<int> s(mstack);
		std::cout << "================================" << std::endl;
	}

	// LIST OUTPUT
	{
		std::cout << "LIST OUTPUT" << std::endl;
		std::list<int> lstack;
    	lstack.push_back(5);
    	lstack.push_back(17);
    	std::cout << lstack.back() << std::endl;
    	lstack.pop_back();
    	std::cout << lstack.size() << std::endl;
    	lstack.push_back(3);
    	lstack.push_back(5);
    	lstack.push_back(737);
    	lstack.push_back(0);
	
    	std::list<int>::iterator it = lstack.begin();
    	std::list<int>::iterator ite = lstack.end();
    	++it;
    	--it;
    	while (it != ite) {
    	    std::cout << *it << std::endl;
    	    ++it;
    	}
    	std::stack<int, std::list<int> > s(lstack);
	}

	// MORE TEST
	{
		std::cout << "Random test" << std::endl;
		MutantStack<char> mstack;
		mstack.push('a');
		mstack.push('b');
		std::cout << mstack.top() << std::endl;
		mstack.pop();
		std::cout << mstack.size() << std::endl;
		mstack.push('c');
		mstack.push('d');
		mstack.push('e');
		mstack.push('f');
		MutantStack<char>::iterator it = mstack.begin();
		MutantStack<char>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite) {
			std::cout << *it << std::endl;
			++it;
		}
		std::stack<char> s(mstack);
	}
    return 0;
}