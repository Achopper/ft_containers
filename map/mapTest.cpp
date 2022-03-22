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

#include "Map.hpp"
#include "../vector/Vector.hpp"
#include <map>
#include <vector>

#define _ratio 1

template <class T, class V>
ft::vector<int> assign_overload_test(ft::map<T, V> mp) {
	ft::vector<int> v;
	for (int i = 0, j = 10; i < 2 * _ratio; ++i, ++j)
		mp.insert(ft::make_pair(i, j));
	ft::map<T, V> mp2;
	for (int i = 2 * _ratio, j = 2; i < 4 * _ratio; ++i, ++j)
		mp2.insert(ft::make_pair(i, j));
	mp2 = mp;
	typename ft::map<T, V>::iterator it = mp2.begin();
	for (; it != mp2.end(); it++) {
		v.push_back(it->first);
		v.push_back(it->second);
	}
	v.push_back(mp2.size());
	for (const auto &i : v)
		std::cout << i;
	std::cout << std::endl;
	return v;
}

template <class K, class M>
void test(ft::map<K,M>)
{

}

int main ()
{
	ft::map<int ,int> a;
	test(a);
	assign_overload_test(a);
}