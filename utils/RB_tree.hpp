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



template <class T, class Compare = std::less<T>,  class Allocator = std::allocator<T> >
class RBTree
{
public:
	typedef T														value_type;
	typedef Compare													value_compare;
	typedef Allocator												allocator_type;
	typedef ft::Node<value_type>									node;
	typedef typename allocator_type::pointer 						pointer;
	typedef typename allocator_type::const_pointer 					const_pointer;
	typedef std::size_t												size_type;
	typedef ft::TreeIterator<value_type>							iterator;
	typedef ft::TreeIterator<const value_type>						const_iterator;


private:

	pointer															_root;
	pointer 														_nil;
	allocator_type 													_allocator;
	value_compare 													_comp;
	size_type 														_size;

public:


	RBTree(const value_compare & comp = value_compare()) : _comp(comp), _size(0)
	{
		_nil  = _allocator.allocate(1);
		_allocator.construct(_nil, node(NULL, NULL, NULL, 'B', value_type()));
		_nil->color = 'B';
		_root = _nil;
	}

	RBTree(const RBTree & obj)
	{
		*this = obj;
	}

	//assign

	~RBTree()
	{
		_clearTree(_root);
		_allocator.destroy(_nil);
		_allocator.deallocate(_nil, 1);
	}
	//operator=()

private:

	pointer _findNext(const value_type &val) const
	{
		pointer y;
		pointer tmp = _findKey(_root, val);
		if (tmp == _nil)
			return (_nil->right);
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

	pointer _findPrev(const value_type &val) const
	{
		pointer y;
		pointer tmp = _findKey(_root, val);
		if (tmp == _nil->right || tmp == _nil->left)
			return (tmp);
		if (tmp == _nil )
			return (_nil->left);
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


	pointer _treeMin(pointer root) const
	{

		while (root->left != _nil)
			root = root->left;
		return root;
	}

	pointer _treeMax(pointer root) const
	{
		while (root->right != _nil)
			root = root->right;
		return root;
	}

	void _insertFixup(pointer newNode)
	{
		pointer uncle;
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

	pointer _insert(pointer root, pointer newNode)
	{
		if (_root == _nil)
		{
			_root = newNode;
			return newNode;
		}
		if(_comp(root->value, newNode->value))
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
		_setNils();
		return (newNode);
	}

	void _rotateLeft(pointer node)
	{
		pointer right = node->right;
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

	void _rotateRight(pointer node)
	{
		pointer left = node->left;
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

	void _clearTree(pointer root)
	{
		if (root == _nil)
			return ;
		_clearTree(root->left);
		_clearTree(root->right);
		_allocator.destroy(root);
		_allocator.deallocate(root, 1);
		--_size;
		root = _nil;
	}

	pointer _findKey(pointer root, const value_type &val) const
	{
		if (root == _nil)
			return (_nil);
		if (root->value.first == val.first)
			return (root);
		if (_comp(val, root->value))
			return _findKey(root->left, val);
		else if (_comp(root->value, val))
			return _findKey(root->right, val);
		return (root);
	}

	void _rbTrpl(pointer x, pointer y)
	{
		if (x->parent == _nil)
			_root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->parent = x->parent;
	}

	void _setNils()
	{
		_nil->left = _treeMin(_root);
		_nil->right = _treeMax(_root);
	}

	void _deleteFix(pointer node)
	{
		pointer bro;
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

	void _delete(pointer node)
	{
		pointer x;
		pointer y = node;
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
		_allocator.destroy(node);
		_allocator.deallocate(node, 1);
		--_size;
		if (col == 'B')
			_deleteFix(x);
		_setNils();
	}


public:

	pointer find(const value_type &key) const
	{
		pointer res = _findKey(_root, key);
		return (res == _nil ? _nil->right : res);
	}

	void erase(const value_type key)
	{
		pointer toDel = _findKey(_root, key);
		if (toDel != _nil)
			_delete(toDel);
	}

	void insert(const value_type &val) //TODO return iterator?
	{
		if (_findKey(_root, val) != _nil)
		{
			std::cout << "find it!" << std::endl;
			return;
		}
		pointer newNode = _allocator.allocate(1);
		_allocator.construct(newNode, node(_nil,_nil,_nil, 'R', val));
		_insert(_root, newNode);
		++_size;
	}


	size_type size() const
	{
		return (_size);
	}

	bool empty() const
	{
		return (_size == 0);
	}

	size_type max_size()
	{
		return (_allocator.max_size());
	}

	iterator begin()
	{
		return (iterator(_nil->left->value));
	}
	

	//TODO del
	void print_tree()
	{
		inorderPrint(_root);
		std::cout << std::endl;
		//std::cout << "min " << _treeMin(_root)->value.first << " | max " << _treeMax(_root)->value.first << std::endl;
		std::cout << "min " << _nil->left->value.first << " | max " << _nil->right->value.first << std::endl;
		std::cout << "size is " << size() << std::endl;
		std::cout << "max size is " << max_size() << std::endl;
		ft::pair<int, int > x = ft::make_pair(1,1);
		pointer prev = _findPrev(x);
		std::cout << "lower " << prev->value.first << " " << prev->value.second << std::endl;
		pointer next = _findNext(x);
		std::cout << "upper " <<  next->value.first << " " << next->value.second << std::endl;

		//std::cout << *begin().first << std::endl;
	}

	void inorderPrint(pointer root)
	{
		if (root == _nil)
			return;

		inorderPrint(root->left);
		root->color == 'B' ? std::cout << GREENCOL : std::cout << REDCOL;
		std::cout << "<" << root->value.first <<  " " << root->value.second << ">" << " " << RESCOL;
		inorderPrint(root->right);

	}
};

#endif //FT_CONTAINERS_RB_TREE_HPP
