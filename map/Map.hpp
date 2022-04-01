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
		typedef Key														key_type;
		typedef T 														mapped_type;
		typedef ft::pair<const key_type, mapped_type> 					value_type;
		typedef Compare 												key_compare;
		typedef Allocator 												allocator_type;
		typedef std::size_t 											size_type;


		class value_compare
		{
		private:
			key_compare 							 _comp;
		public:
			value_compare(const key_compare &comp) : _comp(comp)
			{}

			bool operator()(const value_type &x, const value_type &y) const
			{
				return (_comp(x.first, y.first));
			}

		};

		typedef typename ft::RBTree<value_type, value_compare, Allocator> tree;
		typedef value_compare value_compare;
		typedef typename tree::iterator iterator;
		typedef typename tree::const_iterator const_iterator;
		typedef typename tree::reverse_iterator reverse_iterator;

	private:

		tree _mapTree;
		key_compare _comp;
		allocator_type _alloc;


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
		}

		map(const map &x) :
				_mapTree(tree(key_compare(), allocator_type())),
				_comp(x._comp)
		{
			*this = x;
		}

		map &operator=(const map &obj)
		{
			if (this != &obj)
			{
				_mapTree = obj._mapTree;
				_comp = obj._comp;
				_alloc = obj._alloc;
			}
			return (*this);
		}

		mapped_type &operator[](const key_type &k)
		{
			return (_mapTree.insert(make_pair(k, mapped_type()))->value->second);
		}

		iterator begin()
		{ return _mapTree.begin(); }

		iterator begin() const
		{ return _mapTree.begin(); }

		const_iterator cbegin() const
		{ return _mapTree.cbegin(); }

		iterator end()
		{ return _mapTree.end(); }

		iterator end() const
		{ return _mapTree.end(); }

		const_iterator cend() const
		{ return _mapTree.cend(); }

		reverse_iterator rbegin()
		{ return _mapTree.rbegin(); }

		reverse_iterator rend()
		{ return _mapTree.rend(); }

		void clear()
		{
			_mapTree.clear();
		}

		size_type count(const key_type &key) const
		{
			return (find(key) == end() ? 0 : 1);
		}

		iterator find(const key_type &k)
		{
			return (iterator(_mapTree.find(ft::make_pair(k, mapped_type()))));
		}

		const_iterator find(const key_type &k) const
		{
			return (const_iterator(_mapTree.find(ft::make_pair(k, mapped_type()))));
		}

		bool empty() const
		{
			return (_mapTree.empty());
		}

		size_type size() const
		{
			return (_mapTree.size());
		}

		iterator lower_bound(const key_type &k)
		{
			return (_mapTree.lowerBound(ft::make_pair(k, mapped_type())));
		}

		const_iterator lower_bound(const key_type &k) const
		{
			return (_mapTree.lowerBound(ft::make_pair(k, mapped_type())));
		}

		iterator upper_bound(const key_type &k)
		{
			return (_mapTree.upperBound(ft::make_pair(k, mapped_type())));
		}

		const_iterator upper_bound(const key_type &k) const
		{
			return (_mapTree.upperBound(ft::make_pair(k, mapped_type())));
		}

		pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		void erase(iterator position)
		{
			iterator tmp = find(position->first);
			if (tmp != end())
				_mapTree.erase(*tmp);
		}

		size_type erase(const key_type &k)
		{
			return (_mapTree.erase(ft::make_pair(k, mapped_type())));
		}

		template<class iterator>
		void erase(iterator first, iterator last)
		{
			_mapTree.erase(first, last);
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

		void swap(map &x)
		{
			_mapTree.swap(x._mapTree);
			std::swap(_alloc, x._alloc);
			std::swap(_comp, x._comp);
		}


		pair<iterator, bool> insert(const value_type &val)
		{
			iterator f = find(val.first);
			bool find = !(f.base()->isNil);
			return (find
					? ft::make_pair(f, false)
					: ft::make_pair(iterator(_mapTree.insert(val)), true));
		}

		iterator insert(iterator position, const value_type &val)
		{
			return (iterator(_mapTree.insert(position, val)));
		}

		template<class InputIterator>
		void insert(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
		{
			while (first != last)
			{
				_mapTree.insert(*first);
				++first;
			}
		}

//		void printTree()
//		{
//			_mapTree.print_tree();
//		}

	};

	template<class K, class T, class C, class A>
	void swap(map<K, T, C, A> &lhs, map<K, T, C, A> &rhs)
	{
		lhs.swap(rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs,
				   const map<Key, T, Compare, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}


	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,
					  const map<Key,T,Compare,Alloc>& rhs )
	{
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs,
					  const map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs,
					  const map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}

}

#endif //FT_CONTAINERS_MAP_HPP
