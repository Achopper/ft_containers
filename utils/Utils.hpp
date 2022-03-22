/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achopper <achopper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:49:22 by achopper          #+#    #+#             */
/*   Updated: 2022/01/30 17:49:22 by achopper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_UTILS_H
#define FT_CONTAINERS_UTILS_H

#include <memory>
#include <map>
#include <iostream>

#define RESCOL "\33[00m"
#define GREENCOL "\33[32m"
#define REDCOL "\33[31m"

namespace ft {

//------------------------PAIR--------------------------------------

template<class K, class V>
struct pair
{
	typedef K				first_type;
	typedef V				second_type;
	first_type 				first;
	second_type 			second;

	pair() : first(), second() {}
	template<class T, class T1>
	pair( const pair<T, T1>& obj) : first(obj.first), second(obj.second) {}
	pair(const first_type &f_t, const second_type &s_t):	first(f_t), second(s_t) {}
	pair( const pair& obj) : first(obj.first), second(obj.second) {}
	pair& operator=(const pair& obj) { first = obj.first; second = obj.second; return *this; }
	~pair() {}
};

	template <class T1, class T2>
	bool operator==(const pair< T1, T2> &lhs, const pair< T1, T2> &rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	bool operator!=(const pair< T1, T2> &lhs, const pair< T1, T2> &rhs) {
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<(const pair< T1, T2> &lhs, const pair< T1, T2> &rhs) {
		return (lhs.first < rhs.first) || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<=(const pair< T1, T2> &lhs, const pair< T1, T2> &rhs) {
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>(const pair< T1, T2> &lhs, const pair< T1, T2> &rhs) {
		return rhs < lhs;
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return !(lhs < rhs);
	}

template <class K, class V>
		ft::pair< K, V> make_pair(const K key ,const V value)
{
	return (pair< K, V>(key, value));
}
//------------------------ENABLE_IF---------------------------------
	template <bool cond, class T = void>
	struct enable_if { };

	template <class T>
	struct enable_if<true, T>
	{ typedef T type; };

//------------------------INTEGRAL_CONSTANT--------------------------
	template< class T, T v >
	struct integral_constant
	{
		typedef T 							value_type;
		typedef integral_constant<T, v> 	type;
		static const value_type value = 	v;

		operator value_type() const
		{
			return (value);
		}
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type ;

	template<class Obj> struct is_integral				:	ft::false_type {};
	template<> 			struct is_integral<int>			:	ft::true_type {};
	template<> 			struct is_integral<bool>		:	ft::true_type {};
	template<> 			struct is_integral<char>		:	ft::true_type {};
	template<> 			struct is_integral<char16_t> 	:	ft::true_type {};
	template<> 			struct is_integral<char32_t> 	:	ft::true_type {};
	template<> 			struct is_integral<wchar_t> 	:	ft::true_type {};
	template<> 			struct is_integral<short>		:	ft::true_type {};
	template<> 			struct is_integral<long>		:	ft::true_type {};
	template<> 			struct is_integral<long long>	:	ft::true_type {};
	//TODO add values

//-------------------------------NODE---------------------------------------------------
	template<class Data>
	struct Node
	{
		typedef Data 			value_type;
		value_type 				*value;
		Node					*left;
		Node					*right;
		Node					*parent;
		bool 					isNil;
		char					color;

		//Node() : value(value_type()), color(0) {}

		Node(Data *val = NULL) : value(val), left(NULL), right(NULL), parent(NULL), isNil(false), color('B') {}

		Node(Node *l, Node *r, Node *p, char col, const value_type &val)
				:
				value(val),
				left(l),
				right(r),
				parent(p),
				color(col)
		{}

		Node(const Node& obj)
				:
				value(obj.value),
				left(obj.left),
				right(obj.right),
				parent(obj.parent),
				color(obj.color)

		{}

		Node& operator=(const Node& obj)
		{
			if (this == &obj)
			{
				value = obj.val;
				left = obj.left;
				right = obj.right;
				parent = obj.parent;
				color = obj.color;
				isNil = obj.isNil;
			}
			return (*this);
		}

		~Node() {}

	};
//---------------------------ITERATORS_UTILS---------------------------------

	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag  : public bidirectional_iterator_tag{};

template<class Iterator>
		struct iterator_traits
	{
			typedef typename Iterator::difference_type				difference_type;
			typedef typename Iterator::pointer						pointer;
			typedef typename Iterator::reference					reference;
			typedef typename Iterator::value_type					value_type;
			typedef typename Iterator::iterator_category			iterator_category;
	};

template <class T>
		struct iterator_traits<T*>
	{
			typedef std::ptrdiff_t 									difference_type;
			typedef T												value_type;
			typedef T*												pointer;
			typedef T&												reference;
			typedef  random_access_iterator_tag						iterator_category;
	};

template <class T>
		struct iterator_traits<const T*>
	{
			typedef std::ptrdiff_t 									difference_type;
			typedef T												value_type;
			typedef T*												pointer;
			typedef T&												reference;
			typedef random_access_iterator_tag						iterator_category;
	};

	template <class InputIter>
	typename ft::iterator_traits<InputIter>::difference_type distance(InputIter first, InputIter last)
	{
		typename ft::iterator_traits<InputIter>::difference_type res = 0;
		while (first != last)
		{
			first++;
			res++;
		}
		return (res);
	}

	//STL-------------------------------------------------------------------------------

	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								  InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
}

#endif
