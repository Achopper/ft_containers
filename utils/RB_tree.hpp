/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RB_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achopper <achopper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:19:37 by achopper          #+#    #+#             */
/*   Updated: 2022/02/14 19:19:37 by achopper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_RB_TREE_HPP
#define FT_CONTAINERS_RB_TREE_HPP

#include "Utils.hpp"
#include "../iterators/TreeIterator.hpp"
#include "../iterators/ReverseIterator.hpp"

namespace ft
{
	template<class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
	class RBTree
	{
	public:
		typedef T 																	value_type;
		typedef Compare 															value_compare;
		typedef Allocator 															allocator_type;
		typedef ft::Node<value_type>												node;
		typedef typename Allocator::template rebind<ft::Node<value_type> >::other 	node_allocator;
		typedef typename node_allocator::pointer 									node_pointer;
		typedef typename allocator_type::pointer 									pointer;
		typedef typename allocator_type::const_pointer								const_pointer;
		typedef std::size_t 														size_type;
		typedef ft::TreeIterator<value_type> 										iterator;
		typedef ft::TreeIterator<const value_type> 									const_iterator;
		typedef ft::reverse_iterator<iterator> 										reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> 								const_reverse_iterator;


	private:

		node_pointer 						_root;
		node_pointer 						_nil;
		node_allocator 						_nodeAllocator;
		allocator_type 						_valAllocator;
		value_compare 						_comp;
		size_type 							_size;

	public:


		RBTree()
		:
		_nodeAllocator(node_allocator()),
		_valAllocator(allocator_type()),
		_comp(value_compare()),
		_size(0)
		{
			node_pointer newNode = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(newNode, _makeValue());
			_nil = newNode;
			_nil->isNil = true;
			_nil->color = 'B';
			_root = _nil;
		}

		RBTree(const value_compare &comp, const allocator_type &alloc = allocator_type())
		:
		_nodeAllocator(node_allocator()),
		_valAllocator(alloc),
		_comp(comp),
		_size(0)
		{
			node_pointer newNode = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(newNode, _makeValue());
			_nil = newNode;
			_nil->isNil = true;
			_nil->color = 'B';
			_root = _nil;
		}

		template<class InputIterator>
		RBTree(typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type first, InputIterator last,
		const value_compare &comp,
		const allocator_type &alloc = allocator_type()
		)
		:
			_nodeAllocator(node_allocator()),
			_valAllocator(alloc),
			_comp(comp),
			_size(0)
		{
//			if (&first > &last)
//				throw std::logic_error("");
			node_pointer newNode = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(newNode,  _makeValue());
			_nil = newNode;
			_nil->isNil = true;
			_nil->color = 'B';
			_root = _nil;
			for (; first != last; ++first)
				insert(*first);
		}

		RBTree(const RBTree &obj) :
		_root(NULL),
		_comp(obj._comp),
		_size(0)
		{
			*this = obj;
		}


		~RBTree()
		{
			_clearTree(_root);
			_deleteNode(_nil);
		}

		RBTree &operator=(const RBTree &obj)
		{
			if (this == &obj)
				return (*this);
			if (_root != _nil && _root)
			{
				_clearTree(this->_root);
			}
			_deleteNode(_nil);
			_nodeAllocator = obj._nodeAllocator;
			_valAllocator = obj._valAllocator;
			_comp = obj._comp;
			node_pointer newNode = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(newNode, _makeValue());
			_nil = newNode;
			_nil->isNil = true;
			_nil->color = 'B';
			_root = _nil;
			_makeTreeCopy(obj._root, obj._nil);
			return (*this);
		}

	private:

		void _makeTreeCopy(node_pointer root, node_pointer nil)
		{
			if (root != nil)
			{
				insert(*(root->value));
				_makeTreeCopy(root->left, nil);
				_makeTreeCopy(root->right, nil);
			}
		}

		pointer _makeValue(const value_type &value = value_type())
		{
			pointer new_val = _valAllocator.allocate(1);
			_valAllocator.construct(new_val, value);
			return new_val;
		}

		void _deleteNode(node_pointer node)
		{
			_valAllocator.destroy(node->value);
			_valAllocator.deallocate(node->value, 1);
			_nodeAllocator.destroy(node);
			_nodeAllocator.deallocate(node, 1);
		}

		void _clearTree(node_pointer root)
		{
			if (root == _nil)
				return;
			_clearTree(root->left);
			_clearTree(root->right);
			_deleteNode(root);
			--_size;
			root = _nil;
		}

		node_pointer _insert(node_pointer root, node_pointer newNode)
		{
			if (_root == _nil)
			{
				_root = newNode;
				return newNode;
			}
			if (_comp(*newNode->value, *root->value))
			{
				if (root->left != _nil)
					return (_insert(root->left, newNode));
				root->left = newNode;
			}
			else
			{
				if (root->right != _nil)
					return (_insert(root->right, newNode));
				root->right = newNode;
			}
			newNode->parent = root;
			_insertFixup(newNode);
			//_setNils();
			_nil->parent = _root;
			return (newNode);
		}

		node_pointer _treeMin(node_pointer root) const
		{

			while (root != _nil &&  root->left != _nil)
				root = root->left;
			return root;
		}

		node_pointer _treeMax(node_pointer root) const
		{
			while (root != _nil && root->right != _nil)
				root = root->right;
			return root;
		}

		node_pointer _findKey(node_pointer root, const value_type &val) const
		{
			if (root == _nil)
				return (_nil);
			if (root->value->first == val.first)
				return (root);
			if (_comp(val, *(root->value)))
				return _findKey(root->left, val);
			else if (_comp(*(root->value), val))
				return _findKey(root->right, val);
			return (root);
		}

		void _rotateLeft(node_pointer node)
		{
			node_pointer y = node->right;
			node->right = y->left;

			if (node->left != _nil)
				y->left->parent = node;

			y->parent = node->parent;

			if (node->parent == _nil)
				_root = y;
			else if (node == node->parent->left)
				node->parent->left = y;
			else
				node->parent->right = y;

			y->left = node;
			node->parent = y;
		}

		void _rotateRight(node_pointer node)
		{
			node_pointer y = node->left;
			node->left = y->right;

			if (node->right != _nil)
				y->right->parent = node;

			y->parent = node->parent;

			if (node->parent == _nil)
				_root = y;
			else if (node == node->parent->left)
				node->parent->left = y;
			else
				node->parent->right = y;

			y->right = node;
			node->parent = y;
		}


		void _insertFixup(node_pointer newNode)
		{
			node_pointer uncle;
			if (newNode != _root && newNode->parent != _root)
			{
				while (newNode != _root && newNode->parent->color == 'R')
				{
					if (newNode->parent == newNode->parent->parent->left)
					{
						uncle = newNode->parent->parent->right;
						if (uncle->color == 'R')
						{
							newNode->parent->color = 'B';
							uncle->color = 'B';
							newNode->parent->parent->color = 'R';
							newNode = newNode->parent->parent;
						}
						else
						{
							if (newNode == newNode->parent->right)
							{
								newNode = newNode->parent;
								_rotateLeft(newNode);
							}
							newNode->parent->color = 'B';
							newNode->parent->parent->color = 'R';
							_rotateRight(newNode->parent->parent);
						}
					}
					else
					{
						uncle = newNode->parent->parent->left;
						if (uncle->color == 'R')
						{
							newNode->parent->color = 'B';
							uncle->color = 'B';
							newNode->parent->parent->color = 'R';
							newNode = newNode->parent->parent;
						}
						else
						{
							if (newNode == newNode->parent->left)
							{
								newNode = newNode->parent;
								_rotateRight(newNode);
							}
							newNode->parent->color = 'B';
							newNode->parent->parent->color = 'R';
							_rotateLeft(newNode->parent->parent);
						}
					}
				}
			}
			_root->color = 'B';
		}

		void _rbTrpl(node_pointer x, node_pointer y)
		{
			if (x == _root)
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->parent = x->parent;
		}


		void _deleteFix(node_pointer node)
		{
			node_pointer bro;
			while (node != _root && node->color == 'B')
			{
				if (node == node->parent->left)
				{
					bro = node->parent->right;
					if (bro->color == 'R')
					{
						bro->color = 'B';
						node->parent->color = 'R';
						_rotateLeft(node->parent);
						bro = node->parent->right;
					}
					if (bro->left->color == 'B' && bro->right->color == 'B')
					{
						bro->color = 'R';
						node = node->parent;
					}
					else
					{
						if (bro->right->color == 'B')
						{
							bro->left->color = 'B';
							bro->color = 'R';
							_rotateRight(bro);
							bro = node->parent->right;
						}
						bro->color = node->parent->color;
						node->parent->color = 'B';
						bro->right->color = 'B';
						_rotateLeft(node->parent);
						node = _root;
					}
				}
				else
				{
					bro = node->parent->left;
					if (bro->color == 'R')
					{
						bro->color = 'B';
						node->parent->color = 'R';
						_rotateRight(node->parent);
						bro = node->parent->left;
					}
					if (bro->right->color == 'B' && bro->left->color == 'B')
					{
						bro->color = 'R';
						node = node->parent;
					}
					else
					{
						if (bro->left->color == 'B')
						{
							bro->right->color = 'B';
							bro->color = 'R';
							_rotateLeft(bro);
							bro = node->parent->left;
						}
						bro->color = node->parent->color;
						node->parent->color = 'B';
						bro->left->color = 'B';
						_rotateRight(node->parent);
						node = _root;
					}
				}
			}
			node->color = 'B';
		}

		void _delete(node_pointer z)
		{
			node_pointer x;
			node_pointer y = z;
			node_pointer toD = z;
			char col = y->color;
			if (z->left == _nil)
			{
				x = z->right;
				_rbTrpl(z, z->right);
			}
			else if (z->right == _nil)
			{
				x = z->left;
				_rbTrpl(z, z->left);
			}
			else
			{
				y = _treeMin(z->right);
				col = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					_rbTrpl(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				_rbTrpl(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			if (col == 'B')
				_deleteFix(x);
			_deleteNode(toD);
			--_size;
			_nil->parent = _root;
		}


	public:


		iterator lowerBound(const value_type &val)
		{
			iterator pos = begin();
			iterator end(_nil);
			for (; pos != end; ++pos)
			{
				if (!(_comp(*pos, val)))
					return (pos);
			}
			return (end);
		}

		const_iterator lowerBound(const value_type &val) const
		{
			const_iterator end = cend();
			const_iterator pos = cbegin();
			for (; pos != end; ++pos)
			{
				if (!(_comp(*pos, val)))
					return (pos);
			}
			return (end);
		}

		iterator upperBound(const value_type &val)
		{
			iterator end(_nil);
			iterator pos = begin();
			for (; pos != end; ++pos)
			{
				if (_comp(val, *pos))
					return (pos);
			}
			return (end);
		}

		const_iterator upperBound(const value_type &val) const
		{
			const_iterator end = cend();
			const_iterator pos = cbegin();
			for (; pos != end; ++pos)
			{
				if (_comp(val, *pos))
					return (pos);
			}
			return (end);
		}

		node_pointer insert(const value_type &val)
		{
			node_pointer find;
			if ((find = _findKey(_root, val)) != _nil)
			{
				return (find);
			}
			node_pointer newNode = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(newNode, node(_makeValue(val)));
			newNode->left = _nil;
			newNode->right = _nil;
			newNode->parent = _nil;
			newNode->nil = _nil;
			newNode->isNil = false;
			newNode->color = 'R';
			_insert(_root, newNode);
			_root->color = 'B';
			_nil->parent = _root;
			++_size;
			return (newNode);
		}

		iterator insert(iterator position, const value_type &val)
		{
			node_pointer pos = find(*position.base()->value);
			node_pointer newNode = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(newNode, node(_makeValue(val)));
			newNode->left = _nil;
			newNode->right = _nil;
			newNode->parent = _nil;
			newNode->isNil = false;
			newNode->color = 'R';
			if (pos != _nil && _comp(val, *pos->value) && find(val) == _nil)
			{
				++_size;
				return (iterator(_insert(position.base(), newNode)));
			}
			else
			{
				_deleteNode(newNode);
				return (iterator(insert(val)));
			}
		}

		value_compare getValCompare()
		{
			return (_comp);
		}

		node_pointer find(const value_type &key)
		{
			node_pointer res = _findKey(_root, key);
			return (res == _nil ? _treeMax(res) : res);
		}

		node_pointer find(const value_type &key) const
		{
			node_pointer res = _findKey(_root, key);
			return (res == _nil ? _treeMax(res) : res);
		}

		size_type erase(const value_type &key)
		{
			node_pointer toDel = _findKey(_root, key);
			if (toDel != _nil)
			{
				_delete(toDel);
				return (1);
			}
			return (0);
		}

		template<class iterator>
		void erase (typename ft::enable_if< !ft::is_integral<iterator>::value, iterator >::type first, iterator last)
		{
			for (; first != last; )
				erase(*first++);
		}

		void clear()
		{
			_clearTree(_root);
			_root = _nil;
		}

		size_type size() const
		{
			return (_size);
		}

		bool empty() const
		{
			return (_size == 0);
		}

		size_type max_size() const
		{
			return (_nodeAllocator.max_size());
		}

		allocator_type getAllocator()
		{
			return (_valAllocator);
		}

		iterator begin()
		{
			return (iterator(_treeMin(_root)));
		}

		iterator begin() const
		{
			return (iterator(_treeMin(_root)));
		}

		const_iterator cbegin() const
		{
			return (const_iterator(_treeMin(_root)));
		}

		iterator end()
		{
			return (iterator(_nil));
		}

		iterator end() const
		{
			return (iterator(_nil));
		}

		const_iterator cend() const
		{
			return (const_iterator(_nil));
		}

		reverse_iterator rbegin()
		{
			return (iterator(_nil));
		}

		const_reverse_iterator crbegin() const
		{
			return (const_iterator(_nil));
		}

		reverse_iterator rend()
		{
			return (iterator(_treeMin(_root)));
		}

		const_reverse_iterator crend() const
		{
			return (const_iterator(_treeMin(_root)));
		}

		void swap(const RBTree &obj)
		{
			std::swap(_root, obj._root);
			std::swap(_nil, obj._nil);
			std::swap(_nodeAllocator, obj._nodeAllocator);
			std::swap(_valAllocator, obj._valAllocator);
			std::swap(_comp, obj._comp);
			std::swap(_size, obj._size);
		}


		//TODO del
		void print_tree()
		{
			inorderPrint(_root);
			std::cout << std::endl;
			std::cout << "min " << _treeMin(_root)->value->first << " | max " << _treeMax(_root)->value->first
					<< std::endl;
			//std::cout << "min " << _nil->left->value->first << " | max " << _nil->right->value->first << std::endl;
			std::cout << "size is " << size() << std::endl;
			std::cout << "max size is " << max_size() << std::endl;
			ft::pair<int, int> x = ft::make_pair(27, 27);
		//	node_pointer prev = findPrev(x);
		//	std::cout << "lower " << prev->value->first << " " << prev->value->second << std::endl;
		//	node_pointer next = findNext(x);
		//	std::cout << "upper " << next->value->first << " " << next->value->second << std::endl;
		}

		void inorderPrint(node_pointer root)
		{
			if (root == _nil)
				return;

			inorderPrint(root->left);
			root->color == 'B' ? std::cout << GREENCOL : std::cout << REDCOL;
			std::cout << "<" << root->value->first << " " << root->value->second << ">" << " " << RESCOL;
			inorderPrint(root->right);

		}

	};

	//TODO swap

}

#endif //FT_CONTAINERS_RB_TREE_HPP
