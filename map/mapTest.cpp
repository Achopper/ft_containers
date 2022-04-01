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

#define _ratio 10000


template <class T, class V, class C>
void fillMap(ft::map<T, V, C> &mp) {
	mp.insert(ft::make_pair(16, 3));
	mp.insert(ft::make_pair(8, 3));
	mp.insert(ft::make_pair(23, 3));
	mp.insert(ft::make_pair(7, 3));
	mp.insert(ft::make_pair(19, 3));
	mp.insert(ft::make_pair(29, 3));
	mp.insert(ft::make_pair(41, 3));
	mp.insert(ft::make_pair(4, 3));
	mp.insert(ft::make_pair(11, 3));
}

template <class T, class V>
ft::vector<int> comparator_test(ft::map<T, V> mp) {

	ft::vector<int> v;
	fillMap(mp);
	for (typename ft::map<T, V>::iterator it = mp.begin(); it != mp.end(); it++) { v.push_back(it->first); }
	for (typename ft::map<T, V>::iterator it = --mp.end(); it != mp.begin(); it--) { v.push_back(it->first); }
	ft::map<int, int, std::greater<int> > mp1;
	fillMap(mp1);
	v.push_back(mp1.begin()->first);
	mp1.erase(41);
	v.push_back(mp1.begin()->first);
	mp1.erase(29);
	v.push_back(mp1.begin()->first);
	ft::map<int, int, std::greater<int> > mp2;
	mp2.insert(ft::make_pair(3, 3));
	v.push_back(mp2.begin()->first);
	mp2.erase(3);
	if (mp2.begin() == mp2.end())
		v.push_back(1);
	ft::map<int, int, std::plus<int> > mp3;
	fillMap(mp3);
	for (typename ft::map<T, V>::iterator it = mp3.begin(); it != mp3.end(); it++) { v.push_back(it->first); }
	for (typename ft::map<T, V>::iterator it = --mp3.end(); it != mp3.begin(); it--) { v.push_back(it->first); }
	ft::map<int, int, std::minus<int> > mp4;
	fillMap(mp4);
	for (typename ft::map<T, V>::iterator it = mp4.begin(); it != mp4.end(); it++) { v.push_back(it->first); }
	for (typename ft::map<T, V>::iterator it = --mp4.end(); it != mp4.begin(); it--) { v.push_back(it->first); }
	ft::map<int, int, std::greater_equal<int> > mp5;
	fillMap(mp5);
	for (typename ft::map<T, V>::iterator it = mp5.begin(); it != mp5.end(); it++) { v.push_back(it->first); }
	for (typename ft::map<T, V>::iterator it = --mp5.end(); it != mp5.begin(); it--) { v.push_back(it->first); }
	ft::map<int, int, std::multiplies<int> > mp6;
	fillMap(mp6);
	for (typename ft::map<T, V>::iterator it = mp6.begin(); it != mp6.end(); it++) { v.push_back(it->first); }
	for (typename ft::map<T, V>::iterator it = --mp6.end(); it != mp6.begin(); it--) { v.push_back(it->first); }
	ft::map<int, int, std::bit_xor<int> > mp7;
	fillMap(mp7);
	for (typename ft::map<T, V>::iterator it = mp7.begin(); it != mp7.end(); it++) { v.push_back(it->first); }
	for (typename ft::map<T, V>::iterator it = --mp7.end(); it != mp7.begin(); it--) { v.push_back(it->first); }
	ft::map<int, int, std::logical_and<int> > mp8;
	fillMap(mp8);
	for (typename ft::map<T, V>::iterator it = mp8.begin(); it != mp8.end(); it++) { v.push_back(it->first); }
	for (typename ft::map<T, V>::iterator it = --mp8.end(); it != mp8.begin(); it--) { v.push_back(it->first); }
	v.push_back(mp1.size());
	for (auto &i : v)
		std::cout << i;
	std::cout << std::endl;
	return v;
}


template <class T, class V>
ft::vector<int> insert_test_3(ft::map<T, V> mp) {
	ft::vector<int> v;
	typename ft::map<T, V>::iterator it = mp.end();
	for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
		mp.insert(it, ft::make_pair(i, j));
	}
	typename ft::map<T, V>::iterator it2 = mp.begin();
	for (; it2 != mp.end(); ++it2) {
		v.push_back(it2->first);
		v.push_back(it2->second);
	}
	return v;
}


template <class T, class V>
ft::vector<int>    iterators_test(ft::map<T, V> mp) {
	ft::vector<int> v;
	ft::map<T, V> mpp;
	fillMap(mpp);
	for (typename ft::map<T, V>::iterator it = mpp.begin(); it != mpp.end(); it++) { v.push_back(it->first); }
	for (typename ft::map<T, V>::iterator it = --mpp.end(); it != mpp.begin(); it--) { v.push_back(it->first); }
	ft::map<int, int> mp0;
	ft::map<int, int>::iterator ii = mp0.insert(ft::make_pair(3, 3)).first;
	ii++;
	v.push_back((--ii)->first);
	for (int i = 0, j = 10; i < 5; ++i, ++j)
		mp.insert(ft::make_pair(i, j));
	typename ft::map<T, V>::iterator it = mp.begin();
	typename ft::map<T, V>::iterator it2 = mp.end();
	v.push_back(it->first);
	it++;
	it++;
	it++;
	it++;
	v.push_back(it->first);
	it++;
	it--;
	v.push_back(it->first);
	it2--;
	v.push_back(it2->first);
	v.push_back(it2 == it);
	v.push_back((--it2)->first);
	v.push_back((it2--)->first);
	v.push_back((it2++)->first);
	v.push_back((++it2)->first);
	return v;
}


template <class T, class V>
ft::vector<int>    reverse_iterators_test_std(ft::map<T, V> mp) {
	ft::vector<int> v;

	mp.insert(ft::make_pair(5, 5));
	mp.insert(ft::make_pair(3, 3));
	mp.insert(ft::make_pair(7, 7));
	typename ft::map<T, V>::reverse_iterator rit = mp.rbegin();
	typename ft::map<T, V>::reverse_iterator rit2 = mp.rend();
	v.push_back(rit->first);
	rit++;
	rit2--;
	v.push_back(rit->first);
	v.push_back(rit2->first);
	rit++;
	v.push_back(*rit == *rit2);
	rit2--;
	v.push_back(rit->first);
	v.push_back(rit2->first);
	v.push_back(*rit2 > *rit);
	v.push_back(*rit2 < *rit);
	v.push_back((--rit)->first);
	v.push_back((++rit2)->first);
	v.push_back((rit--)->first);
	v.push_back((rit2++)->first);
	return v;
}

template <class T, class V>
ft::vector<int> assign_overload_test(ft::map<T, V> mp) {
	ft::vector<int> v;
	for (int i = 0, j = 10; i < 2 * _ratio; ++i, ++j)
		mp.insert(ft::make_pair(i, j));
	ft::map<T, V> mp2;
	for (int i = 2 * _ratio, j = 2; i < 4 * _ratio; ++i, ++j)
		mp2.insert(ft::make_pair(i, j));
	//mp2 = mp;
	mp2.swap(mp);
	//mp2.printTree();
	typename ft::map<T, V>::iterator it = mp2.begin();
	for (; it != mp2.end(); ++it) {
		v.push_back(it->first);
		v.push_back(it->second);
	}
	v.push_back(mp2.size());
	for (const auto &i : v)
		std::cout << i << " ";
	std::cout << std::endl;
	return v;
}

template <class T, class V>
void test(ft::map<T,V> mp)
{
	ft::vector<int> v;
	for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j)
		mp.insert(ft::make_pair(i, j));

	for (auto it = mp.begin(); it != mp.end(); ++it)
		v.push_back(it->first);
	for (const auto &i : v)
		std::cout << i << " ";

}

template <class T, class V>
ft::vector<int> clear_test(ft::map<T, V> mp) {
	ft::vector<int> v;
	mp.clear();
	for (int i = 0, j = 0; i < 25 * _ratio; ++i, ++j)
		mp.insert(ft::make_pair(i, j));
	v.push_back(mp.size());
	mp.clear();
	v.push_back(mp.size());
	typename ft::map<T, V>::iterator it = mp.begin();
	if (it == mp.end())
		v.push_back(1);
	for (const auto &i : v)
		std::cout << i << " ";
	std::cout << std::endl;
	return v;
}

template <class T, class V>
ft::vector<int> erase_test_1(ft::map<T, V> mp) {
	ft::vector<int> v;
	v.push_back(mp.erase(3));
	for (int i = 0, j = 0; i < 30 * _ratio; ++i, ++j)
		mp.insert(ft::make_pair(i, j));
	typename ft::map<T, V>::iterator it = mp.begin();
	v.push_back(it->first);
	v.push_back(mp.erase(-5));
	v.push_back(mp.size());
	v.push_back(mp.erase(0));
	v.push_back(mp.size());
	it = mp.begin();
	v.push_back(it->first);
	typename ft::map<T, V>::iterator it4 = mp.begin();
	for (; it4 != mp.end(); it4 = mp.begin())
		mp.erase(it4->first);
	typename ft::map<T, V>::iterator it2 = mp.end();
	it2--;
	v.push_back(mp.erase(30 * _ratio - 1));
	v.push_back(mp.size());
	ft::map<int, int> mp2;
	for (int i = 0, j = 0; i < 10 ; ++i, ++j)
		mp2.insert(ft::make_pair(i, j));
	mp2.erase(2);
	mp2.erase(7);
	typename ft::map<T, V>::iterator it3 = mp2.begin();
	for (; it3 != mp2.end(); ++it3) {
		v.push_back(it3->first);
		v.push_back(it3->second);
	}
	for (const auto &i : v)
		std::cout << i << " ";
	std::cout << std::endl;
	return v;
}

template <class T, class V>
ft::vector<int> erase_test_2(ft::map<T, V> mp) {
	ft::vector<int> v;
	for (int i = 0, j = 0; i < 30 * _ratio; ++i, ++j)
		mp.insert(ft::make_pair(i, j));
	typename ft::map<T, V>::iterator it = mp.begin();
	v.push_back(it->first);
	mp.erase(it);
	v.push_back(mp.size());
	it = mp.begin();
	mp.erase(++it);
	v.push_back(mp.size());
	it = mp.begin();
	v.push_back(it->first);
	typename ft::map<T, V>::iterator it4 = mp.begin();

	for (; it4 != mp.end(); it4 = mp.begin())
		mp.erase(it4);

	v.push_back(mp.size());
	ft::map<int, int> mp2;
	for (int i = 0, j = 0; i < 10 ; ++i, ++j)
		mp2.insert(ft::make_pair(i, j));
	typename ft::map<T, V>::iterator ittest = mp2.begin();
	for (int i = 0; i < 2; ++i) ittest++;
	mp2.erase(ittest);
	ittest = mp2.begin();
	for (int i = 0; i < 5; ++i) ittest++;
	mp2.erase(ittest);
	typename ft::map<T, V>::iterator it3 = mp2.begin();
	for (; it3 != mp2.end(); ++it3) {
		v.push_back(it3->first);
		v.push_back(it3->second);
	}
	for (const auto &i : v)
		std::cout << i << " ";
	std::cout << std::endl;
	return v;
}

template <class T, class V>
ft::vector<int> erase_test_3(ft::map<T, V> mp) {
	ft::vector<int> v;
	for (int i = 0, j = 0; i < 100 * _ratio; ++i, ++j)
		mp.insert(ft::make_pair(i, j));


	mp.erase(mp.begin(), --mp.end());

	v.push_back(mp.begin()->first);
	for (const auto &i : v)
		std::cout << i << " ";
	std::cout << std::endl;
	return v;
}

template <class T, class V>
ft::vector<int> swap_test(ft::map<T, V> mp) {
	ft::vector<int> v;
	for (int i = 0, j = 0; i < 25 * _ratio; ++i, ++j)
		mp.insert(ft::make_pair(i, j));
	ft::map<T, V> mp2;
	for (int i = 25 * _ratio, j = 0; i < 35 * _ratio; ++i, --j)
		mp.insert(ft::make_pair(i, j));
	long *adr1 = reinterpret_cast<long *>(&mp);
	long *adr2 = reinterpret_cast<long *>(&mp2);
	mp.swap(mp2);
	if (reinterpret_cast<long *>(&mp) == adr1 && reinterpret_cast<long *>(&mp2) == adr2)
		v.push_back(1);
	v.push_back(mp2.size());
	typename ft::map<T, V>::iterator it = mp2.begin();
	for (; it != mp2.end(); ++it) {
		v.push_back(it->first);
		v.push_back(it->second);
	}
	std::swap(mp, mp2);
	typename ft::map<T, V>::iterator it2 = mp2.begin();
	for (; it2 != mp2.end(); ++it2) {
		v.push_back(it2->first);
		v.push_back(it2->second);
	}
	return v;
}

template <class T, class V>
ft::vector<int> equal_range_test(ft::map<T, V> mp) {
	ft::vector<int> v;
	mp.insert(ft::make_pair(10, 10));
	mp.insert(ft::make_pair(20, 20));
	mp.insert(ft::make_pair(30, 30));
	mp.insert(ft::make_pair(40, 40));
	mp.insert(ft::make_pair(50, 50));
	mp.insert(ft::make_pair(60, 60));
	const ft::pair<ft::map<int, int>::const_iterator , ft::map<int, int>::const_iterator>& pair = mp.equal_range(10);
	const ft::pair<ft::map<int, int>::const_iterator , ft::map<int, int>::const_iterator>& pair2 = mp.equal_range(11);
	const ft::pair<ft::map<int, int>::const_iterator , ft::map<int, int>::const_iterator>& pair3 = mp.equal_range(1);
	v.push_back(pair.first->first);
	v.push_back(pair.first->second);
	v.push_back(pair.second->first);
	v.push_back(pair.second->second);
	v.push_back(pair2.first->first);
	v.push_back(pair2.first->second);
	v.push_back(pair2.second->first);
	v.push_back(pair2.second->second);
	v.push_back(pair3.first->first);
	v.push_back(pair3.first->second);
	v.push_back(pair3.second->first);
	v.push_back(pair3.second->second);
	return v;
}

void relationn_test ()
{
	std::map<char,int> foo,bar;
	foo['a']=100;
	foo['b']=200;
	bar['a']=10;
	bar['z']=1000;

	// foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}

bool iterator_traits_test() {
	ft::vector<std::string> res;
	ft::vector<std::string> res2;


	res.push_back(typeid(ft::vector<int>::iterator::iterator_category).name());
	res.push_back(typeid(ft::vector<int>::iterator::value_type).name());
	res.push_back(typeid(ft::vector<int>::iterator::difference_type).name());
	res.push_back(typeid(ft::vector<int>::iterator::iterator_type).name());
	res.push_back(typeid(ft::vector<int>::iterator::pointer).name());
	res.push_back(typeid(ft::vector<int>::iterator::reference).name());
	res.push_back(typeid(ft::vector<int>::reverse_iterator::iterator_category).name());
	res.push_back(typeid(ft::vector<int>::reverse_iterator::value_type).name());
	res.push_back(typeid(ft::vector<int>::reverse_iterator::difference_type).name());
	res.push_back(typeid(ft::vector<int>::reverse_iterator::pointer).name());
	res.push_back(typeid(ft::vector<int>::reverse_iterator::reference).name());

	res2.push_back(typeid(std::vector<int>::iterator::iterator_category).name());
	res2.push_back(typeid(std::vector<int>::iterator::value_type).name());
	res2.push_back(typeid(std::vector<int>::iterator::difference_type).name());
	res2.push_back(typeid(std::vector<int>::iterator::iterator_type).name());
	res2.push_back(typeid(std::vector<int>::iterator::pointer).name());
	res2.push_back(typeid(std::vector<int>::iterator::reference).name());
	res2.push_back(typeid(std::vector<int>::reverse_iterator::iterator_category).name());
	res2.push_back(typeid(std::vector<int>::reverse_iterator::value_type).name());
	res2.push_back(typeid(std::vector<int>::reverse_iterator::difference_type).name());
	res2.push_back(typeid(std::vector<int>::reverse_iterator::pointer).name());
	res2.push_back(typeid(std::vector<int>::reverse_iterator::reference).name());
	std::cout << "ft" << std::endl;
	for (const auto &i : res)
	{
		std::cout << i << " ";
	}
	std::cout <<  std::endl;
	std::cout << "std" << std::endl;
	for (const auto &i : res2)
	{
		std::cout << i << " ";
	}
	std::cout <<  std::endl;
	return res == res2;
}

int main ()
{
	ft::map<int ,int> a;
	std::map<int, int> s;
//	test(a);
	assign_overload_test(a);
//	iterators_test(a);
//	reverse_iterators_test_std(a);
//	comparator_test(a);
//	insert_test_3(a);
//	clear_test(a);
//	erase_test_1(a);
//	erase_test_2(a);
//	erase_test_3(a);
//	swap_test(a);
//	equal_range_test(a);
//	relationn_test();
//	iterator_traits_test();


}