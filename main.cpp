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

template <class T>
void fillVector(std::vector<T>&vec1, std::vector<T>&vec2, ft::vector<T>&myVec1, ft::vector<T>&myVec2, std::size_t size)
{
	for (std::size_t i = 0; i <= size; ++i)
	{
		vec1.push_back(i);
		if (i == size)
		{
			for (std::size_t j = i; j != 0; --j)
				vec2.push_back(j);
		}
	}
	for (std::size_t i = 0; i <= size; ++i)
	{
		myVec1.push_back(i);
		if (i == size)
		{
			for (std::size_t j = i; j != 0; --j)
				myVec2.push_back(j);
		}
	}
}

void swapTest()
{
	std::cout << GREENCOL << "-----------------------SWAP TEST--------------------------------" << RESCOL << std::endl;
	ft::vector<int> myVec1(5,10);
	ft::vector<int> myVec2(5,10);
	std::vector<int> vec1(5,10);
	std::vector<int> vec2(5,10);

	fillVector(vec1,vec2,myVec1,myVec2, 1);
	std::vector<int>::iterator it1 = vec1.begin() + 10;
	std::vector<int>::iterator it2 = vec2.begin() + 10;
	for (std::size_t i = 0; i < myVec1.size(); ++i)
	{
		std::cout << *myVec1.testPrint(i) << " ";
	}
	std::cout << std::endl;
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

	//vec1.reserve(50);
	fillVector(vec1, vec2, myVec1, myVec2, 20);
	std::vector<int>::iterator it1 = vec1.begin();
	std::vector<int>::iterator it2 = vec2.begin();

	std::cout << "data of vec1 before resize" << std::endl;
	for (; it1 != vec1.end(); ++it1)
		std::cout << *it1 << " ";

	std::cout << std::endl <<  "data of vec2 before resize" << std::endl;
	for (; it2 != vec2.end(); ++it2)
		std::cout << *it2 << " ";
	std::cout << std::endl << "------------------------------------------------" << std::endl;
	std::cout <<  "data of myVec1 before resize" << std::endl;
	for (std::size_t i = 0; i < myVec1.size(); ++i)
		std::cout << *myVec1.testPrint(i) << " ";

	std::cout << std::endl <<  "data of myVec2 before resize" << std::endl;
	for (std::size_t i = 0; i < myVec2.size(); ++i)
		std::cout << *myVec2.testPrint(i) << " ";
	std::cout << std::endl << "------------------------------------------------" << std::endl;
	std::cout << "size and capacity of vec1 before resize " << vec1.size() << " " << vec1.capacity() << std::endl;
	std::cout << "size and capacity of vec1 before resize " << vec2.size() << " " << vec2.capacity() << std::endl;

	std::cout << std::endl << "size and capacity of vec1 before resize " << myVec1.size() << " " << myVec1.capacity() << std::endl;
	std::cout << "size and capacity of myVec2 before resize " << myVec2.size() << " " << myVec2.capacity() << std::endl;



	vec1.resize(35, 50);
	vec2.resize(35, 50);
	myVec1.resize(35, 50);
	myVec2.resize(35, 50);
	it1 = vec1.begin();
	it2 = vec2.begin();

	std::cout << std::endl << "data of vec1 after resize" << std::endl;
	for (; it1 != vec1.end(); ++it1)
		std::cout << *it1 << " ";

	std::cout << std::endl <<  "data of vec2 after resize" << std::endl;
	for (; it2 != vec2.end(); ++it2)
		std::cout << *it2 << " ";
	std::cout << std::endl << "------------------------------------------------" << std::endl;
	std::cout <<  "data of myVec1 after resize" << std::endl;
	for (std::size_t i = 0; i < myVec1.size(); ++i)
		std::cout << *myVec1.testPrint(i) << " ";

	std::cout << std::endl <<  "data of myVec2 after resize" << std::endl;
	for (std::size_t i = 0; i < myVec2.size(); ++i)
		std::cout << *myVec2.testPrint(i) << " ";
	std::cout << std::endl << "------------------------------------------------" << std::endl;
	std::cout <<  "size and capacity of vec1 after resize " << vec1.size() << " " << vec1.capacity() << std::endl;
	std::cout << "size and capacity of vec1 before after " << vec2.size() << " " << vec2.capacity() << std::endl;

	std::cout << std::endl << "size and capacity of myVec1 after resize " << myVec1.size() << " " << myVec1.capacity() << std::endl;
	std::cout << "size and capacity of myVec2 before after " << myVec2.size() << " " << myVec2.capacity() << std::endl;


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
	//myVec.reserve(50);
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
	//resizeTest();

	return (0);
}