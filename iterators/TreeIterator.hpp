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
		typedef typename ft::iterator_traits<T *>::difference_type difference_type;
		typedef typename ft::iterator_traits<T *>::pointer pointer;
		typedef typename ft::iterator_traits<T *>::value_type value_type;
		typedef typename ft::iterator_traits<T *>::reference reference;
		typedef ft::Node<value_type> node_pointer;
		typedef ft::bidirectional_iterator_tag iterator_category;

	private:
		node_pointer _ptr;
	public:
		TreeIterator() : _ptr(0)
		{}

		TreeIterator(node_pointer ptr) : _ptr(ptr)
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
			return (_ptr->value);
		}

	};

}

#endif //FT_CONTAINERS_TreeIterator_HPP
