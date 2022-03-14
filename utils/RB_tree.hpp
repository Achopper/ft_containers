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
		typedef T value_type;
		typedef Compare value_compare;
		typedef Allocator allocator_type;
		typedef ft::Node<value_type> node;
		typedef typename Allocator::template rebind<ft::Node<value_type> >::other node_allocator;
		typedef typename node_allocator::pointer node_pointer;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef std::size_t size_type;
		typedef ft::TreeIterator<value_type> iterator;
		typedef ft::TreeIterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;


	private:

		node_pointer _root;
		node_pointer _nil;
		node_allocator _nodeAllocator;
		allocator_type _valAllocator;
		value_compare _comp;
		size_type _size;

	public:


		RBTree(const value_compare &comp = value_compare()) : _comp(comp), _size(0)
		{
			node_pointer newNode = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(newNode, node());
			_nil = newNode;
			_nil->isNil = true;
			_nil->color = 'B';
			_root = _nil;
		}

		RBTree(const RBTree &obj)
		{
			*this = obj;
		}

		//assign

		~RBTree()
		{
			_clearTree(_root);
			_deleteNode(_nil);
		}

		RBTree &operator=(const RBTree &obj)
		{
			if (this == &obj)
				return (*this);
			if (this->_root != _nil)
				_clearTree(this->_root);
			_deleteNode(_nil);
			_nodeAllocator = obj._nodeAllocator;
			_valAllocator = obj._valAllocator;
			_comp = obj._comp;
			node_pointer newNode = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(newNode, node());
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
				//_setNils();
				return newNode;
			}
			if (_comp(*root->value, *newNode->value))
			{
				if (root->right != _nil)
					return (_insert(root->right, newNode));
				root->right = newNode;
			}
			else
			{
				if (root->left != _nil)
					return (_insert(root->left, newNode));
				root->left = newNode;
			}
			newNode->parent = root;
			_insertFixup(newNode);
			//_setNils();
			_nil->parent = _root;
			return (newNode);
		}

//		void _setNils()
//		{
//			_nil->left = _treeMin(_root);
//			_nil->right = _treeMax(_root);
//		}

		node_pointer _treeMin(node_pointer root) const
		{

			while (root &&  root->left != _nil)
				root = root->left;
			return root;
		}

		node_pointer _treeMax(node_pointer root) const
		{
			while (root && root->right != _nil)
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
			node_pointer right = node->right;
			node->right = right->left;

			if (node->left != _nil)
				right->left->parent = node;

			right->parent = node->parent;

			if (node->parent == _nil)
				_root = right;
			else if (node == node->parent->left)
				node->parent->left = right;
			else
				node->parent->right = right;

			right->left = node;
			node->parent = right;
		}

		void _rotateRight(node_pointer node)
		{
			node_pointer left = node->left;
			node->left = left->right;

			if (node->left != _nil)
				left->left->parent = node;

			left->parent = node->parent;

			if (node->parent == _nil)
				_root = left;
			else if (node == node->parent->left)
				node->parent->left = left;
			else
				node->parent->right = left;

			left->right = node;
			node->parent = left;
		}


		void _insertFixup(node_pointer newNode)
		{
			node_pointer uncle;
			if (newNode != _root && newNode->parent != _root)
			{
				while (newNode->parent->color == 'R')
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
			if (x->parent == _nil)
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

		void _delete(node_pointer node)
		{
			node_pointer x;
			node_pointer y = node;
			char col = y->color;
			if (node->left == _nil)
			{
				x = node->right;
				_rbTrpl(node, node->right);
			}
			else if (node->right == _nil)
			{
				x = node->left;
				_rbTrpl(node, node->left);
			}
			else
			{
				y = _treeMin(node->right);
				col = y->color;
				x = y->right;
				if (y->parent == node)
					x->parent = y;
				else
				{
					_rbTrpl(y, y->right);
					y->right = node->right;
					y->right->parent = y;
				}
				_rbTrpl(node, y);
				y->left = node->left;
				y->left->parent = y;
				y->color = node->color;
			}
			_deleteNode(node);
			--_size;
			if (col == 'B')
				_deleteFix(x);
			_nil->parent = _root;
			//_setNils();
		}


	public:

		node_pointer findNext(const value_type &val) const
		{
			node_pointer y;
			node_pointer tmp = _findKey(_root, val);
			node_pointer max = _treeMax(_root);
			if (tmp == _nil)
				return (max);
			if (tmp->right != _nil)
				return (_treeMin(tmp->right));
			y = tmp->parent;
			while (y != _nil && tmp == y->right)
			{
				tmp = y;
				y = y->parent;
			}
			return (y);
		}

		node_pointer findPrev(const value_type &val) const
		{
			node_pointer y;
			node_pointer tmp = _findKey(_root, val);
			node_pointer min = _treeMin(_root);
			if (tmp == _treeMax(tmp))
				return (tmp);
			if (tmp == _nil)
				return (min);
			if (tmp->left != _nil)
				return (_treeMax(tmp->left));
			y = tmp->parent;
			while (y != _nil && tmp == y->left)
			{
				tmp = y;
				y = y->parent;
			}
			return (y);
		}

		node_pointer insert(const value_type &val) //TODO return iterator?
		{
			node_pointer find;
			if ((find = _findKey(_root, val)) != _nil)
			{
				std::cout << "find it!" << std::endl;
				return (find);
			}
			node_pointer newNode = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(newNode, node(_makeValue(val)));
			newNode->left = _nil;
			newNode->right = _nil;
			newNode->parent = _nil;
			newNode->isNil = false;
			newNode->color = 'R';
			_insert(_root, newNode);
			_root->color = 'B';
			++_size;
			return (newNode);
		}


		node_pointer find(const value_type &key) const
		{
			node_pointer res = _findKey(_root, key);
			return (res == _nil ? _treeMax(res) : res);
		}

		void erase(const value_type &key)
		{
			node_pointer toDel = _findKey(_root, key);
			if (toDel != _nil)
				_delete(toDel);
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

		iterator begin()
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

		const_iterator cend() const
		{
			return (const_iterator(_nil));
		}

		reverse_iterator rbegin()
		{
			return (iterator(_treeMin(_root)));
		}

		const_reverse_iterator crbegin() const
		{
			return (const_iterator(_treeMin(_root)));
		}

		reverse_iterator rend()
		{
			return (iterator(_nil));
		}

		const_reverse_iterator crend() const
		{
			return (const_iterator(_nil));
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
			node_pointer prev = findPrev(x);
			std::cout << "lower " << prev->value->first << " " << prev->value->second << std::endl;
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

}

#endif //FT_CONTAINERS_RB_TREE_HPP
