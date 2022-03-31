/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapTest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achopper <achopper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 22:20:47 by achopper          #+#    #+#             */
/*   Updated: 2022/03/15 22:20:47 by achopper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Set.hpp"
#include "../vector/Vector.hpp"
#include <set>


template <class T>
void test(ft::set<T> s)
{
	ft::set<int> a;
	for (int i = 0; i < 10000; ++i)
		a.insert(i);
	s.insert(a.begin(), a.end());
	if (a == s)
		std::cout << "is equal!" << std::endl;
	s.erase(--s.end());
	if (a < s)
		std::cout << "now a less than s" << std::endl;
	a.erase(a.find(500));
	if (a.size() == s.size())
		std::cout << "size is equal " << std::endl;
	std::cout << "lower bound " << *a.lower_bound(5) << " upper " << *a.upper_bound(100) << std::endl;
}

int main ()
{
	ft::set<int> a;
	test(a);
}