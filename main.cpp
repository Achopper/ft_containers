/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achopper <achopper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:26:56 by achopper          #+#    #+#             */
/*   Updated: 2022/01/06 16:26:56 by achopper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector/Vector.hpp"
#include <iostream>

#define RESCOL "\33[00m"
#define GREENCOL "\33[32m"

class A
{
public:
	int a;
	A() : a(5) {}
};

class B
{
public:
	int c;
	B(int x) : c(x) {}
};

void swapTest()
{
	std::cout << GREENCOL << "-----------------------SWAP TEST--------------------------------" << RESCOL << std::endl;
	ft::vector<int> myVec1;
	ft::vector<int> myVec2;
	std::vector<int> vec1;
	std::vector<int> vec2;

	for (int i = 0; i <= 40; ++i)
	{
		vec1.push_back(i);
		if (i == 40)
		{
			for (int j = i; j != 0; --j)
				vec2.push_back(j);
		}
	}
	std::vector<int>::iterator it1 = vec1.begin() + 10;
	std::vector<int>::iterator it2 = vec2.begin() + 10;
	std::cout << "std::vector iterators before swap " << *it1 << " " << *it2 << std::endl;
	*it1 = 99;
	*it2 = 88;
	std::cout << "std::vector iterators before swap " << *it1 << " " << *it2 << std::endl;
	vec1.swap(vec2);
	std::cout << "std::vector iterators after swap " << *it1 << " " << *it2 << std::endl;
	*it1 = 10;
	*it2 = 30;
	std::cout << "std::vector iterators after swap " << *it1 << " " << *it2 << std::endl;
}

void resizeTest()
{
	std::cout << GREENCOL << "-----------------------RESIZE TEST-------------------------------" << RESCOL <<std::endl;
	ft::vector<int> myVec1;
	ft::vector<int> myVec2;
	std::vector<int> vec1;
	std::vector<int> vec2;

	for (int i = 0; i <= 20; ++i)
	{
		vec1.push_back(i);
		if (i == 20)
		{
			for (int j = i; j != -1; --j)
				vec2.push_back(j);
		}
	}
	std::vector<int>::iterator it1 = vec1.begin();
	std::vector<int>::iterator it2 = vec2.begin();

	std::cout << "data of vec1 before resize" << std::endl;
	for (; it1 != vec1.end(); ++it1)
		std::cout << *it1 << " ";

	std::cout << std::endl <<  "data of vec2 before resize" << std::endl;
	for (; it2 != vec2.end(); ++it2)
		std::cout << *it2 << " ";

	std::cout << std::endl << "size and capacity of vec1 before resize " << vec1.size() << " " << vec1.capacity() << std::endl;
	std::cout << "size and capacity of vec1 before resize " << vec2.size() << " " << vec2.capacity() << std::endl;



	vec1.resize(35, 50);
	vec2.resize(35, 50);
	it1 = vec1.begin();
	it2 = vec2.begin();

	std::cout << std::endl << "data of vec1 after resize" << std::endl;
	for (; it1 != vec1.end(); ++it1)
		std::cout << *it1 << " ";

	std::cout << std::endl <<  "data of vec2 after resize" << std::endl;
	for (; it2 != vec2.end(); ++it2)
		std::cout << *it2 << " ";

	std::cout << std::endl << "size and capacity of vec1 after resize " << vec1.size() << " " << vec1.capacity() << std::endl;
	std::cout << "size and capacity of vec1 before after " << vec2.size() << " " << vec2.capacity() << std::endl;
}

int main()
{
	A a;
	A b;
	b.a = 15;
	ft::vector<A> myVec(10);
	ft::vector<A> myVec1(20, b);
	myVec.swap(myVec1);
	myVec = myVec1;
	myVec.reserve(50);
	std::cout << myVec.size() << " " << myVec.capacity() << std::endl;
	std::vector<int> vec(2, 10);
	std::cout << vec.size() << " " << vec.capacity() << std::endl;
	vec.push_back(20);
	std::cout << vec.size() << " " << vec.capacity() << " " << myVec.max_size() << std::endl;
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << vec.capacity() << std::endl;
	vec.reserve(50);
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << vec.capacity() << std::endl;
	swapTest();
	resizeTest();

	return (0);
}