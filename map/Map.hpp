/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achopper <achopper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 17:01:28 by achopper          #+#    #+#             */
/*   Updated: 2022/03/13 17:01:28 by achopper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include "../utils/RB_tree.hpp"

namespace ft
{

	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key,
			T> > >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;


		class value_compare
		{
		protected:
			key_compare _comp;
		public:
			value_compare(key_compare comp) : _comp(comp)
			{}

			bool operator()(const value_type &x, const value_type &y) const
			{
				return (comp(x.first, y.first));
			}

		};

		typedef typename ft::RBTree<value_type, value_compare, Allocator> tree;
		typedef value_compare value_compare;
		typedef typename tree::iterator iterator;
		typedef typename tree::const_iterator const_iterator;
		typedef typename tree::reverse_iterator reverse_iterator;
		typedef typename tree::const_reverse_iterator const_reverse_iterator;

	private:

		tree _mapTree;
		key_compare _comp;
		allocator_type _alloc;

	public:

		map(const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
				:
				  _comp(comp),
				  _alloc(alloc)
		{

		}


		template<class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) :
				_comp(comp),
				_alloc(alloc)
		{

		}

		map(const map &x)
		{
			*this = x;
		}

	};

}

#endif //FT_CONTAINERS_MAP_HPP
