/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseIterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achopper <achopper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 14:54:54 by achopper          #+#    #+#             */
/*   Updated: 2022/02/13 14:54:54 by achopper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_CONTAINERS_REVERSEITERATOR_HPP
#define FT_CONTAINERS_REVERSEITERATOR_HPP

#include "../utils/Utils.hpp"

namespace ft
{
	template<class Iterator>
	class reverse_iterator
	{
	public:

		typedef Iterator														iterator_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type			difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer					pointer;
		typedef typename ft::iterator_traits<Iterator>::reference				reference;
		typedef typename ft::iterator_traits<Iterator>::value_type				value_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category 		iterator_category;
	private:
		Iterator 																_it;

	public:

		reverse_iterator() :_it() {}

		reverse_iterator (iterator_type it) : _it(it) {}

		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) : _it(rev_it.base()) {}

		iterator_type base () const
		{
			return (_it);
		}

		reference operator*() const
		{
			iterator_type tmp = _it;
			return (*--tmp);

		}
		pointer   operator->() const
		{
			return &(operator*());
		}

		reverse_iterator& operator++()
		{
			--_it;
			return (*this);
		}

		reverse_iterator  operator++(int)
		{
			reverse_iterator tmp = (*this);
			++(*this);
			return (tmp);
		}

		reverse_iterator& operator--()
		{
			++_it;
			return (*this);
		}
		reverse_iterator  operator--(int)
		{
			reverse_iterator tmp = (*this);
			--(*this);
			return (tmp);
		}

		reverse_iterator  operator+ (difference_type n) const
		{
			return (reverse_iterator(_it - n));
		}

		reverse_iterator& operator+=(difference_type n)
		{
			_it -= n;
			return (*this);
		}

		reverse_iterator  operator- (difference_type n) const
		{
			return (reverse_iterator(_it + n));
		}

		reverse_iterator& operator-=(difference_type n)
		{
			_it += n;
			return (*this);
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}
	};

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it)
	{
		return reverse_iterator<Iterator>(rev_it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}


}

#endif //FT_CONTAINERS_REVERSEITERATOR_HPP