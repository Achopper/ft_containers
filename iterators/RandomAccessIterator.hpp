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


#ifndef FT_CONTAINERS_RANDOMACCESSITERATOR_HPP
#define FT_CONTAINERS_RANDOMACCESSITERATOR_HPP

#include "../utils/Utils.hpp"

namespace ft
{
	template<class T>
	class random_access_iterator {

	public:
		typedef typename ft::iterator_traits<T*>::difference_type			difference_type;
		typedef typename ft::iterator_traits<T*>::pointer					pointer;
		typedef typename ft::iterator_traits<T*>::value_type				value_type;
		typedef typename ft::iterator_traits<T*>::reference					reference;
		typedef ft::random_access_iterator_tag								iterator_category;

	private:
		pointer _ptr;

	public:

		random_access_iterator() : _ptr(0) {}

		random_access_iterator(pointer ptr) : _ptr(ptr) {}

		random_access_iterator(const random_access_iterator & obj) : _ptr(obj._ptr) {}

		random_access_iterator const& operator=(const random_access_iterator & obj)
		{
			if (this == &obj)
				return (*this);
			_ptr = obj._ptr;
			return (*this);
		}

		virtual ~random_access_iterator() {}

		operator random_access_iterator <const value_type> () const {
			return random_access_iterator<const value_type>(_ptr);
		}

		pointer base() const
		{
			return (_ptr);
		}

		random_access_iterator operator +(const difference_type &v) const
		{
			return (_ptr + v);
		}

		random_access_iterator operator -(const difference_type &v) const
		{
			return (_ptr + (-v));
		}

		difference_type operator +(const random_access_iterator<value_type> &v) const
		{
			return (_ptr + v.base());
		}

		difference_type operator -(const  random_access_iterator<value_type> &v) const
		{
			return (_ptr - v.base());
		}

		random_access_iterator & operator +=(const difference_type &v)
		{
			_ptr += v;
			return (*this);
		}

		random_access_iterator & operator -=(const difference_type &v)
		{
			_ptr +=  (-v);
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

		pointer operator->()
		{
			return (_ptr);
		}

		reference operator*()
		{
			return (*_ptr);
		}

		pointer operator->() const
		{
			return (_ptr);
		}

		reference operator*() const
		{
			return (*_ptr);
		}

		reference operator[](const difference_type idx)
		{
			return (_ptr[idx]);
		}

		reference operator[](const difference_type idx) const
		{
			return (_ptr[idx]);
		}
	};

	template<class Iter1, class Iter2>
	bool operator==(const random_access_iterator<Iter1>& l, const random_access_iterator<Iter2>& r)
	{
		return (l.base() == r.base());
	}

	template<class Iter1, class Iter2>
	bool operator<(const random_access_iterator<Iter1>& l, const random_access_iterator<Iter2>& r)
	{
		return (l.base() < r.base());
	}

	template<class Iter1, class Iter2>
	bool operator!=(const random_access_iterator<Iter1>& l, const random_access_iterator<Iter2>& r)
	{
		return !(l == r);
	}

	template<class Iter1, class Iter2>
	bool operator>(const random_access_iterator<Iter1>& l, const random_access_iterator<Iter2>& r)
	{
		return (r < l);
	}

	template<class Iter1, class Iter2>
	bool operator>=(const random_access_iterator<Iter1>& l, const random_access_iterator<Iter2>& r)
	{
		return !(l < r);
	}

	template<class Iter1, class Iter2>
	bool operator<=(const random_access_iterator<Iter1>& l, const random_access_iterator<Iter2>& r)
	{
		return !(r < l);
	}

	template<class Iter1>
	bool operator==(const random_access_iterator<Iter1>& l, const random_access_iterator<Iter1>& r)
	{
		return (l.base() == r.base());
	}

	template<class Iter1>
	bool operator<(const random_access_iterator<Iter1>& l, const random_access_iterator<Iter1>& r)
	{
		return (l.base() < r.base());
	}

	template<class Iter1>
	bool operator!=(const random_access_iterator<Iter1>& l, const random_access_iterator<Iter1>& r)
	{
		return !(l == r);
	}

	template<class Iter1>
	bool operator>(const random_access_iterator<Iter1>& l, const random_access_iterator<Iter1>& r)
	{
		return (r < l);
	}

	template<class Iter1>
	bool operator>=(const random_access_iterator<Iter1>& l, const random_access_iterator<Iter1>& r)
	{
		return !(l < r);
	}

	template<class Iter1>
	bool operator<=(const random_access_iterator<Iter1>& l, const random_access_iterator<Iter1>& r)
	{
		return !(r < l);
	}

	template<class Iter1, class Iter2>
	typename Iter1::pointer operator-(const random_access_iterator<Iter1>& l, const
	random_access_iterator<Iter2>& r)
	{
		return r.base() - l.base();
	}

}
#endif
