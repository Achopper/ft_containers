/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeIterator.hpp                		            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achopper <achopper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:38:27 by achopper          #+#    #+#             */
/*   Updated: 2022/03/07 20:38:27 by achopper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TreeIterator_HPP
#define FT_CONTAINERS_TreeIterator_HPP

#include "../utils/Utils.hpp"

namespace ft
{

	template<class T>
	class TreeIterator
	{
	public:
		typedef typename ft::iterator_traits<T *>::difference_type	difference_type;
		typedef typename ft::iterator_traits<T *>::pointer 			pointer;
		typedef typename ft::iterator_traits<T *>::value_type		value_type;
		typedef typename ft::iterator_traits<T *>::reference		reference;
		typedef ft::Node<value_type>								*node_pointer;
		typedef ft::bidirectional_iterator_tag						iterator_category;

	private:
		node_pointer _ptr;

		node_pointer _getMin(node_pointer ptr) const
		{
			while (!ptr->left->isNil)
				ptr = ptr->left;
			return (ptr);
		}

		node_pointer _getMax(node_pointer ptr) const
		{
			while (!ptr->right->isNil)
				ptr = ptr->right;
			return (ptr);
		}

	public:
		TreeIterator() : _ptr(0)
		{}

		TreeIterator(const node_pointer ptr) : _ptr(ptr)
		{}

		TreeIterator(const TreeIterator &obj) : _ptr(obj._ptr)
		{}

		TreeIterator const &operator=(const TreeIterator &obj)
		{
			if (this == &obj)
				return (*this);
			_ptr = obj._ptr;
			return (*this);
		}

		~TreeIterator()
		{}

		node_pointer base() const
		{
			return (_ptr);
		}

		reference operator*()
		{
			return *(_ptr->value);
		}

		pointer operator->()
		{
			return (_ptr->value);
		}

		reference operator*() const
		{
			return *(_ptr->value);
		}

		pointer operator->() const
		{
			return (_ptr->value);
		}

		TreeIterator& operator++()
		{
			node_pointer y;
			if (!_ptr->right->isNil)
				_ptr = _getMin(_ptr->right);
			else
			{
				y = _ptr->parent;
				while (!y->isNil && _ptr == y->right)
				{
					_ptr = y;
					y = y->parent;
				}
				_ptr = y;
			}
			return (*this);
		}

		TreeIterator operator++(int)
		{
			TreeIterator tmp = *this;
			operator++();
			return (tmp);
		}

		TreeIterator& operator--()
		{
			node_pointer y;
			if (_ptr->isNil)
			{
				_ptr = _getMax(_ptr->parent);
				return (*this);
			}
			if (!_ptr->left->isNil)
				_ptr = _getMax(_ptr->left);
			else
			{
				y = _ptr->parent;
				while (!y->isNil && _ptr == y->left)
				{
					_ptr = y;
					y = y->parent;
				}
				_ptr = y;
			}
			return (*this);
		}

		TreeIterator operator--(int)
		{
			TreeIterator tmp = *this;
			operator--();
			return (tmp);
		}
	};

	template<class Iter1, class Iter2>
	bool operator==(const TreeIterator<Iter1>& l, const TreeIterator<Iter2>& r)
	{
		return (l.base() == r.base());
	}

	template<class Iter1, class Iter2>
	bool operator!=(const TreeIterator<Iter1>& l, const TreeIterator<Iter2>& r)
	{
		return (l.base() != r.base());
	}

}

#endif //FT_CONTAINERS_TreeIterator_HPP
