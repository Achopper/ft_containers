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


#ifndef FT_CONTAINERS_SET_HPP
#define FT_CONTAINERS_SET_HPP

#include "../utils/RB_tree.hpp"

namespace ft
{

	template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set
	{
	public:
		typedef std::size_t size_type;
		typedef Compare key_compare;
		typedef key_compare value_compare;
		typedef Key value_type;
		typedef Allocator allocator_type;
		typedef RBTree<value_type, key_compare, allocator_type> tree;
		typedef typename tree::iterator iterator;
		typedef typename tree::const_iterator const_iterator;
		typedef typename tree::reverse_iterator reverse_iterator;



	private:

		tree _setTree;
		key_compare _comp;
		allocator_type _alloc;


	public:

		set(const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
				:
				_setTree(tree(comp, alloc)),
				_comp(comp),
				_alloc(alloc)
		{
		}

		template<class InputIterator>
		set(InputIterator first, InputIterator last,
		const key_compare &comp = key_compare(),
		const allocator_type &alloc = allocator_type())
		:
		_setTree(tree(first, last, comp, alloc)),
		_comp(comp),
		_alloc(alloc)
		{
		}

		set(const set &x) :
				_setTree(tree(key_compare(), allocator_type())),
				_comp(x._comp)
		{
			*this = x;
		}

		~set() {};

		set &operator=(const set &obj)
		{
			if (this != &obj)
			{
				_setTree = obj._setTree;
				_comp = obj._comp;
				_alloc = obj._alloc;
			}
			return (*this);
		}

		iterator begin()
		{ return _setTree.begin(); }

		iterator begin() const
		{ return _setTree.begin(); }

		const_iterator cbegin() const
		{ return _setTree.cbegin(); }

		iterator end()
		{ return _setTree.end(); }

		iterator end() const
		{ return _setTree.end(); }

		const_iterator cend() const
		{ return _setTree.cend(); }

		reverse_iterator rbegin()
		{ return _setTree.rbegin(); }

		reverse_iterator rend()
		{ return _setTree.rend(); }

		void clear()
		{
			_setTree.clear();
		}

		size_type count(const value_type &key) const
		{
			return (find(key) == end() ? 0 : 1);
		}

		iterator find(const value_type &k)
		{
			return (iterator(_setTree.find(k)));
		}

		const_iterator find(const value_type &k) const
		{
			return (const_iterator(_setTree.find(k)));
		}

		bool empty() const
		{
			return (_setTree.empty());
		}

		size_type size() const
		{
			return (_setTree.size());
		}

		iterator lower_bound(const value_type &k)
		{
			return (_setTree.lowerBound(k));
		}

		const_iterator lower_bound(const value_type &k) const
		{
			return (_setTree.lowerBound(k));
		}

		iterator upper_bound(const value_type &k)
		{
			return (_setTree.upperBound(k));
		}

		const_iterator upper_bound(const value_type &k) const
		{
			return (_setTree.upperBound(k));
		}

		pair<const_iterator, const_iterator> equal_range(const value_type &k) const
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		void erase(iterator position)
		{
			iterator tmp = find(*position);
			if (tmp != end())
				_setTree.erase(*tmp);
		}

		size_type erase(const value_type &k)
		{
			return (_setTree.erase(k));
		}

		template<class iterator>
		void erase(iterator first, iterator last)
		{
			_setTree.erase(first, last);
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
			return (_setTree.getValCompare());
		}

		size_type max_size() const
		{
			return (_setTree.max_size());
		}

		void swap(set &x)
		{
			_setTree.swap(x._setTree);
			std::swap(_alloc, x._alloc);
			std::swap(_comp, x._comp);
		}


		pair<iterator, bool> insert(const value_type &val)
		{
			iterator f = find(val);
			bool find = !(f.base()->isNil);
			return (find
					? ft::make_pair(f, false)
					: ft::make_pair(iterator(_setTree.insert(val)), true));
		}

		iterator insert(iterator position, const value_type &val)
		{
			return (iterator(_setTree.insert(position, val)));
		}

		template<class InputIterator>
		void insert(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
		{
			while (first != last)
			{
				_setTree.insert(*first);
				++first;
			}
		}

//		void printTree()
//		{
//			_setTree.print_tree();
//		}
//
	};

	template<class K, class C, class A>
	void swap(set<K, C, A> &lhs, set<K, C, A> &rhs)
	{
		lhs.swap(rhs);
	}

	template<class Key, class Compare, class Alloc>
	bool operator==(const set<Key, Compare, Alloc> &lhs,
					const set<Key, Compare, Alloc> &rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<class Key,  class Compare, class Alloc>
	bool operator!=(const set<Key, Compare, Alloc> &lhs,
					const set<Key, Compare, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template<class Key, class Compare, class Alloc>
	bool operator<(const set<Key, Compare, Alloc> &lhs,
				   const set<Key, Compare, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}


	template <class Key, class Compare, class Alloc>
	bool operator<= ( const set<Key,Compare,Alloc>& lhs,
					  const set<Key,Compare,Alloc>& rhs )
	{
		return !(rhs < lhs);
	}

	template <class Key, class Compare, class Alloc>
	bool operator>  ( const set<Key,Compare,Alloc>& lhs,
					  const set<Key,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template <class Key, class Compare, class Alloc>
	bool operator>= ( const set<Key,Compare,Alloc>& lhs,
					  const set<Key,Compare,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}

}
#endif //FT_CONTAINERS_SET_HPP
