/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achopper <achopper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:15:02 by achopper          #+#    #+#             */
/*   Updated: 2022/02/02 20:15:02 by achopper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/Utils.hpp"

#ifndef FT_CONTAINERS_RANDOMACCESSITERATOR_HPP
#define FT_CONTAINERS_RANDOMACCESSITERATOR_HPP

namespace ft
{
	template<class T>
	class random_access_iterator {

	public:
		typedef typename iterator_traits<T*>::difference_type			differnce_type;
		typedef typename iterator_traits<T*>::pointer					pointer;
		typedef typename iterator_traits<T*>::value_type				value_type;
		typedef typename iterator_traits<T*>::reference					reference;
		typedef pointer 												iterator_type;
		typedef random_access_terator_tag								iterator_category;

	private:
		pointer _ptr;

	public:

		random_access_iterator() : _ptr() {}

		random_access_iterator(pointer ptr) : _ptr(ptr) {}

		random_access_iterator(const random_access_iterator & obj) : _ptr(obj._ptr) {}

		random_access_iterator const & operator=(random_access_iterator & obj)
		{
			if (this == &obj)
				return (*this);
			_ptr = obj._ptr;
			return (*this);
		}

		virtual ~random_access_iterator() {}

		random_access_iterator operator +(const differnce_type &v) const
		{
			return (_ptr + v);
		}

		random_access_iterator operator -(const differnce_type &v) const
		{
			return (_ptr - v);
		}

		random_access_iterator & operator +=(const differnce_type &v)
		{
			_ptr += v;
			return (*this);
		}

		random_access_iterator & operator -=(const differnce_type &v)
		{
			_ptr -= v;
			return (*this);
		}

		random_access_iterator& operator++()
		{
			++_ptr;
			return (*this);
		}

		random_access_iterator operator++(int)
		{
			random_access_iterator tmp(*this);
			++_ptr;
			return (tmp);
		}

		random_access_iterator& operator--()
		{
			--_ptr;
			return (*this);
		}
		random_access_iterator operator--(int)
		{
			random_access_iterator tmp(*this);
			--_ptr;
			return (tmp);
		}

		random_access_iterator operator->() const
		{
			return (_ptr);
		}

		random_access_iterator operator*() const
		{
			return (*_ptr);
		}

		random_access_iterator operator[](const differnce_type idx)
		{
			return (_ptr[idx]);
		}


	};

}
#endif
