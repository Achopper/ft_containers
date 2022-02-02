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
#include <vector>
#include <iostream>

namespace ft {
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

		explicit operator value_type() const
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

//---------------------------ITERATORS_UTILS---------------------------------

class random_access_terator_tag {};

template<class Iterator>
		class iterator_traits
	{
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::iterator_category	iterator_category;
	};

template <class T>
		class iterator_traits<T*>
	{
			std::ptrdiff_t 									difference_type;
			T												value_type;
			T*												pointer;
			T&												reference;
			typedef random_access_terator_tag				iterator_category;
	};

template <class T>
		class iterator_traits<const T*>
	{
			std::ptrdiff_t 									difference_type;
			T												value_type;
			T*												pointer;
			T&												reference;
			typedef random_access_terator_tag				iterator_category;
	};

}

#endif
