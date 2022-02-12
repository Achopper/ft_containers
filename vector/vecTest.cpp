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

#include "Vector.hpp"
#include <iostream>

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

void splitter(std::string spl)
{
	std::cout << GREENCOL << "------------------------------------------------------------------" << spl
						  << "------------------------------------------------------------------" << RESCOL <<std::endl;
}

template <class T>
void printVec(std::vector<T>&vec1, ft::vector<T>&myVec1)
{
	for (std::size_t i = 0; i <= vec1.size() - 1; ++i)
		std::cout << vec1.at(i) << " ";
	std::cout << std::endl;
	for (std::size_t i = 0; i <= myVec1.size() - 1; ++i)
		std::cout << myVec1.at(i) << " ";
	std::cout << std::endl << "std::vec cap and size " << std::endl << vec1.capacity() << " " << vec1.size() << std::endl <<
	myVec1.capacity() << " " << myVec1.size() << std::endl << std::endl;
}

template <class T>
void fillVector(std::vector<T>&vec1, ft::vector<T>&myVec1, std::size_t size)
{
	for (std::size_t i = 0; i <= size; ++i)
		vec1.push_back(i);
	for (std::size_t i = 0; i <= size; ++i)
		myVec1.push_back(i);
}

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
	vec2.push_back(0);
	for (std::size_t i = 0; i <= size; ++i)
	{
		myVec1.push_back(i);
		if (i == size)
		{
			for (std::size_t j = i; j != 0; --j)
			{
				myVec2.push_back(j);
			}
		}
	}
	myVec2.push_back(0);
}

void elemAccTest()
{
	splitter("ACCESS TEST");
	ft::vector<int> myVec1;
	myVec1.reserve(20);
	myVec1.push_back(1);
	myVec1.push_back(2);
	
	std::vector<int> vec1;
	vec1.reserve(20);
	vec1.push_back(1);
	vec1.push_back(2);

	std::cout << "Front and back of std vector " << vec1.front() << " " << vec1.back() << std::endl <<
		"Front and back of ft vector " << myVec1.front() << " " << myVec1.back() << std::endl <<
		"value at index [0] and [1] of std vector " << vec1[0] << " " << vec1[1] << std::endl <<
		"value at index [0] and [1] of ft vector " << myVec1[0] << " " << myVec1[1] << std::endl <<
		"value at(0) and at(1) of std vector " << vec1.at(0) << " " << vec1.at(1) << std::endl <<
		"value at(0) and at(1) of ft vector " << myVec1.at(0) << " " << myVec1.at(1) << std::endl <<
		"now at(2) std::vec " << std::endl;
	try
	{
		std::cout << vec1.at(5) << std::endl;
	}
	catch (std::exception &r)
	{
		std::cout << r.what() << std::endl;
	}
	std::cout << "now at(2) ft::vec " << std::endl;
	try
	{
		std::cout << myVec1.at(2) << std::endl;
	}
		catch (std::exception& r)
	{
		std::cout << r.what() << std::endl;
	}
}

void swapTest()
{
	splitter("SWAP TEST");
	ft::vector<int> myVec1;
	ft::vector<int> myVec2;
	std::vector<int> vec1;
	std::vector<int> vec2;

	fillVector(vec1,vec2,myVec1,myVec2, 10);
	std::vector<int>::iterator it1 = vec1.begin() + 4;
	std::vector<int>::iterator it2 = vec2.begin() + 4;
	for (std::size_t i = 0; i < myVec1.size(); ++i)
	{
		std::cout << myVec1.at(i) << " ";
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
	splitter("RESIZE TEST");
	ft::vector<int> myVec1;
	ft::vector<int> myVec2;
	std::vector<int> vec1;
	std::vector<int> vec2;

	myVec1.reserve(20);
	myVec2.reserve(20);
	vec1.reserve(20);
	vec2.reserve(20);
	fillVector(vec1, vec2, myVec1, myVec2, 20);
	std::vector<int>::iterator it1 = vec1.begin();
	std::vector<int>::iterator it2 = vec2.begin();
	std::cout << GREENCOL << "[" << *it1 << "]" << RESCOL << std::endl;
	std::cout << "data of vec1 before resize" << std::endl;
	for (; it1 != vec1.end(); ++it1)
		std::cout << *it1 << " ";

	std::cout << std::endl <<  "data of vec2 before resize" << std::endl;
	for (; it2 != vec2.end(); ++it2)
		std::cout << *it2 << " ";
	std::cout << std::endl;

	splitter("-");

	std::cout <<  "data of myVec1 before resize" << std::endl;
	for (std::size_t i = 0; i < myVec1.size(); ++i)
		std::cout << myVec1.at(i) << " ";

	std::cout << std::endl <<  "data of myVec2 before resize" << std::endl;
	for (std::size_t i = 0; i < myVec2.size(); ++i)
		std::cout << myVec1.at(i) << " ";
	std::cout << std::endl;

	splitter("-");

	std::cout << "size and capacity of vec1 before resize " << vec1.size() << " " << vec1.capacity() << std::endl;
	std::cout << "size and capacity of vec2 before resize " << vec2.size() << " " << vec2.capacity() << std::endl;

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

	std::cout << std::endl;
	splitter("-");

	std::cout <<  "data of myVec1 after resize" << std::endl;
	for (std::size_t i = 0; i < myVec1.size(); ++i)
		std::cout <<myVec1.at(i) << " ";

	std::cout << std::endl <<  "data of myVec2 after resize" << std::endl;
	for (std::size_t i = 0; i < myVec2.size(); ++i)
		std::cout << myVec1.at(i) << " ";

	std::cout << std::endl;
	splitter("-");

	std::cout <<  "size and capacity of vec1 after resize " << vec1.size() << " " << vec1.capacity() << std::endl;
	std::cout << "size and capacity of vec1 before after " << vec2.size() << " " << vec2.capacity() << std::endl;

	std::cout << std::endl << "size and capacity of myVec1 after resize " << myVec1.size() << " " << myVec1.capacity() << std::endl;
	std::cout << "size and capacity of myVec2 before after " << myVec2.size() << " " << myVec2.capacity() << std::endl;
}

void rangeTest()
{
	splitter("CONSTRUCTOR TEST");
	ft::vector<int> myVec1;
	myVec1.reserve(20);

	std::vector<int> vec1;
	vec1.reserve(20);
	fillVector(vec1, myVec1, 10);
	std::vector<int>::iterator bIt = vec1.begin(), eIt = vec1.end();
	ft::vector<int>::iterator bMIt = myVec1.begin(), eMI = myVec1.end();

	std::vector<int> vec2(bIt, eIt);
	ft::vector<int> myVec2(bMIt, eMI);
	printVec(vec2, myVec2);

	splitter("for(iterator) TEST");
	for ( std::vector<int>::iterator it = vec1.begin(); it < vec1.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	for ( ft::vector<int>::iterator it = myVec1.begin(); it < myVec1.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

}

void insertTest()
{
	splitter("INSERT TEST");
	splitter("FILL TEST");

	ft::vector<int> myVec1;
	std::vector<int> vec1;
	fillVector(vec1, myVec1, 10);

	printVec(vec1, myVec1);

	ft::vector<int>::iterator it = myVec1.begin() + 11;
	std::vector<int>::iterator stdIt = vec1.begin() + 11;

	vec1.insert(stdIt, 10, 7);
	myVec1.insert(it, 10, 7);

	printVec(vec1, myVec1);

	it = myVec1.begin();
	stdIt = vec1.begin();

	vec1.insert(stdIt + 6, 10, 3);
	myVec1.insert(it + 6, 10, 3);

	printVec(vec1, myVec1);

	splitter("SINGLE TEST");
	myVec1.resize(10);
	vec1.resize(10);

	it = myVec1.begin() ;
	stdIt = vec1.begin();

	printVec(vec1, myVec1);

	stdIt =  vec1.insert(stdIt + 3,  42);
	it = myVec1.insert(it + 3,  42);

	printVec(vec1, myVec1);

	vec1.insert(stdIt,  43);
	myVec1.insert(it,  43);

	printVec(vec1, myVec1);

	std::cout << "value at return iterators. my : " << *it << " std : " << *stdIt << std::endl;

	splitter("RANGE TEST");

	vec1.resize(10);
	std::vector<int> ranVec;
	ft::vector<int> myRanVec;
	fillVector(ranVec, myRanVec, 30);
	myVec1.resize(10);

	printVec(vec1, myVec1);

	std::cout << "vector used to range values" << std::endl ;
	for (size_t i = 0; i < ranVec.size(); ++i)
		std::cout << ranVec.at(i) << " ";
	std::cout  << std::endl;
	for (size_t i = 0; i < myRanVec.size(); ++i)
		std::cout << myRanVec.at(i) << " ";
	std::cout << std::endl  << std::endl;

	it = myVec1.begin();
	stdIt = vec1.begin();
	std::vector<int>::iterator it1 = ranVec.begin();
	std::vector<int>::iterator it2 = ranVec.begin() + 30;
	ft::vector<int>::iterator mit1 = myRanVec.begin();
	ft::vector<int>::iterator mit2 = myRanVec.begin() + 30;


	vec1.insert(stdIt, it1, it2 );
	myVec1.insert(it, mit1, mit2);

	printVec(vec1, myVec1);

	it = myVec1.begin();
	stdIt = vec1.begin();
	it1 = ranVec.begin();
	it2 = ranVec.begin() + 10;
	mit1 = myRanVec.begin();
	mit2 = myRanVec.begin() + 10;

	vec1.insert(stdIt, it1, it2);
	myVec1.insert(it, mit1, mit2);

	printVec(vec1, myVec1);


}

void assignTest()
{
	splitter("ASSIGN TEST");
	splitter("FILL TEST");
	ft::vector<int> myVec1;
	std::vector<int> vec1;
	fillVector(vec1, myVec1, 10);

	printVec(vec1, myVec1);

	vec1.assign(5, 42);
	myVec1.assign(5,42);

	printVec(vec1, myVec1);

	vec1.assign(42, 42);
	myVec1.assign(42,42);

	printVec(vec1, myVec1);

	splitter("RANGE TEST");

	std::vector<int> ranVec;
	ft::vector<int> myRanVec;
	fillVector(ranVec, myRanVec, 50);

	std::cout << "vector used to range values" << std::endl ;
	printVec(ranVec, myRanVec);

	std::vector<int>::iterator it1 = ranVec.begin();
	std::vector<int>::iterator it2 = ranVec.begin() + 50;
	ft::vector<int>::iterator mit1 = myRanVec.begin();
	ft::vector<int>::iterator mit2 = myRanVec.begin() + 50;

	vec1.assign(it1, it2);
	myVec1.assign(mit1, mit2);

	printVec(vec1, myVec1);

}

void eraseTest()
{
	splitter("ERASE TEST");
	splitter("SINGLE TEST");
	ft::vector<int> myVec1;
	std::vector<int> vec1;
	fillVector(vec1, myVec1, 10);
	std::vector<int>::iterator it1 = vec1.begin();
	std::vector<int>::iterator it2 = vec1.end() - 1;
	ft::vector<int>::iterator mit1 = myVec1.begin();
	ft::vector<int>::iterator mit2 = myVec1.end() - 1;

	printVec(vec1, myVec1);

	it1 = vec1.erase(it2);
	mit1 = myVec1.erase(mit2);

	printVec(vec1, myVec1);
	if (mit1 == myVec1.end())
		std::cout << "value of return iterator is end()" << std::endl << std::endl;
	else
		std::cout << "value of return iterator is not valid" << std::endl;

	it2 = vec1.begin() + 3;
	mit2 = myVec1.begin() + 3;

	it1 = vec1.erase(it2);
	mit1 = myVec1.erase(mit2);
	printVec(vec1, myVec1);

	std::cout << "value at return iterators. my : " << *it1 << " std : " << *mit1 << std::endl << std::endl;

	splitter("RANGE TEST");
	vec1.clear();
	myVec1.clear();
	fillVector(vec1, myVec1, 40);
	printVec(vec1, myVec1);

	it1 = vec1.begin() + 2;
	it2 = vec1.end() - 5;
	mit1 = myVec1.begin() + 2;
	mit2 = myVec1.end() - 5;

	std::vector<int>::iterator ret = vec1.erase(it1, it2);
	ft::vector<int>::iterator myRet = myVec1.erase(mit1, mit2);

	printVec(vec1, myVec1);

	std::cout << "value at return iterators. my : " << *myRet << " std : " << *ret << std::endl << std::endl;


	it1 = vec1.begin() + 3;
	it2 = vec1.end() - 1;
	mit1 = myVec1.begin() + 3;
	mit2 = myVec1.end() - 1;

	ret = vec1.erase(it1, it2);
	myRet = myVec1.erase(mit1, mit2);

	printVec(vec1, myVec1);

	std::cout << "value at return iterators. my : " << *myRet << " std : " << *ret << std::endl << std::endl;
}

void compareTest()
{
	ft::vector<int> foo (3,100);
	ft::vector<int> bar (3,100);

	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

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
	std::cout << myVec.size() << " MY " << myVec.capacity() << std::endl;
	std::vector<int> vec(2, 10);
	ft::vector<int> intVec(2, 10);
	std::cout << vec.size() << " VEC " << vec.capacity() << std::endl;
	vec.push_back(20);
	intVec.push_back(20);
	std::cout << vec.size() << " SZ " << vec.capacity() << " " << vec.max_size() << std::endl;
	std::cout << intVec.size() << " SZ " << intVec.capacity() << " " << intVec.max_size() << std::endl;
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << vec.capacity() << std::endl;
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << vec.capacity() << std::endl;
	swapTest();
	resizeTest();
	elemAccTest();
	rangeTest();
	insertTest();
	assignTest();
	eraseTest();
	compareTest();
	return (0);
}