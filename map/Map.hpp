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
		typedef Key 										key_type;
		typedef T 											mapped_type;
		typedef ft::pair<const key_type, mapped_type> 		value_type;
		typedef Compare 									key_compare;
		typedef Allocator 									allocator_type;
		typedef value_type 									&reference;
		typedef const value_type							&const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer 		const_pointer;
		typedef std::size_t									size_type;
		typedef std::ptrdiff_t 								difference_type;


		class value_compare
		{
		protected:
			key_compare 									_comp;
		public:
			value_compare(const key_compare& comp) : _comp(comp)
			{}

			bool operator()(const value_type &x, const value_type &y) const
			{
				return (_comp(x.first, y.first));
			}

		};

		typedef typename ft::RBTree<value_type, value_compare, Allocator> 	tree;
		typedef value_compare 												value_compare;
		typedef typename tree::iterator 									iterator;
		typedef typename tree::const_iterator 								const_iterator;
		typedef typename tree::reverse_iterator 							reverse_iterator;
		typedef typename tree::const_reverse_iterator 						const_reverse_iterator;

	private:

		tree 							_mapTree;
		key_compare 					_comp;
		allocator_type					_alloc;


	public:

		map(const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
				:
				  _mapTree(tree(comp, alloc)),
				  _comp(comp),
				  _alloc(alloc)
		{
		}

		template<class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
			:
			    _mapTree(tree(first, last, comp, alloc)),
				_comp(comp),
				_alloc(alloc)
		{
//			while (first != last)
//			{
//				_mapTree.insert(*first);
//				++first;
//			}
		}

		map(const map &x) :
		_mapTree(x._mapTree),
		_comp(x._comp)
		{
			*this = x;
		}

		map& operator=(const map &obj)
		{
			if (this == &obj)
			{
				_mapTree = obj._mapTree;
				_comp = obj._comp;
				_alloc = obj._alloc;
			}
			return (*this);
		}

		mapped_type& operator[] (const key_type& k)
		{
			return 	(_mapTree.insert(make_pair(k, mapped_type()))->value->second);
		}

		iterator begin() { return _mapTree.begin(); }
		const_iterator cbegin() const { return _mapTree.cbegin(); }
		iterator end() { return _mapTree.end(); }
		const_iterator cend() const { return _mapTree.cend(); }
		reverse_iterator rbegin() { return _mapTree.rbegin(); }
		reverse_iterator rend() { return _mapTree.rend(); }

		void clear()
		{
			_mapTree.clear();
		}

		size_type count(const key_type &key) const
		{
			return (find(key) == end() ? 0 : 1);
		}

		iterator find (const key_type& k)
		{
			return (iterator(_mapTree.find(ft::make_pair(k,mapped_type()))));
		}

		const_iterator find (const key_type& k) const
		{
			return (const_iterator(_mapTree.find(ft::make_pair(k,mapped_type()))));
		}

		bool empty() const
		{
			return (_mapTree.empty());
		}

		size_type size() const
		{
			return (_mapTree.size());
		}

		iterator lower_bound (const key_type& k)
		{
			return (_mapTree.lowerBound(ft::make_pair(k, mapped_type())));
		}

		const_iterator lower_bound (const key_type& k) const
		{
			return (_mapTree.lowerBound(ft::make_pair(k, mapped_type())));
		}

		iterator upper_bound (const key_type& k)
		{
			return (_mapTree.upperBound(ft::make_pair(k, mapped_type())));
		}

		const_iterator upper_bound (const key_type& k) const
		{
			return (_mapTree.upperBound(ft::make_pair(k, mapped_type())));
		}

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		pair<iterator,iterator>             equal_range (const key_type& k)
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		void erase (iterator position)
		{
			iterator tmp = find(position->first);
			if (tmp != end())
				_mapTree.erase(tmp);
		}

		size_type erase (const key_type& k)
		{
			iterator tmp = find(k);
			if (tmp != end())
			{
				_mapTree.erase(*tmp);
				return (1);
			}
			return (0);
		}

		template<class iterator>
		void erase (iterator first, iterator last, typename
		ft::enable_if<!ft::is_integral<iterator>::value>::type * = 0)
		{
			while (first != last)
			{
				erase(first->first);
				++first;
			}

		}

		allocator_type get_allocator() const
		{
			return (_alloc);
		}

		key_compare key_comp() const
		{
			return (_comp);
		}


		value_compare value_comp() const
		{
			return (_mapTree.getValCompare());
		}

		size_type max_size() const
		{
			return (_mapTree.max_size());
		}

		void swap (map& x)
		{
			_mapTree.swap(x._mapTree);
			std::swap(_alloc, x._alloc);
			std::swap(_comp, x._comp);
		}


		pair<iterator,bool> insert (const value_type& val)
		{
			iterator f = find(val.first);
			bool find = !(f.base()->isNil);
			return (find
				? ft::make_pair(f, false)
				: ft::make_pair(iterator(_mapTree.insert(val)), true));
		}

		iterator insert (iterator position, const value_type& val)
		{
			return (iterator(_mapTree.insert(position,ft::make_pair(val))));
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last,
					 typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
		{
			while(first != last)
			{
				_mapTree.insert(*first);
				++first;
			}
		}

		//TODO del

		void printTree()
		{
			_mapTree.print_tree();
		}

	};

}

#endif //FT_CONTAINERS_MAP_HPP
