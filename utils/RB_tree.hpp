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

template<class Data>
struct Node
{
	typedef Data 			value_type;
	value_type 				value;
	Node					*left;
	Node					*right;
	Node					*parent;
	char					color;

	Node() : color(0) {}
	Node(Node *l, Node *r, Node *p, char col, const value_type &val)
	:
	    value(val),
		left(l),
		right(r),
		parent(p),
		color(col)
	{}

	Node(const Node& obj)
	:
	    value(obj.value),
		left(obj.left),
		right(obj.right),
		parent(obj.parent),
		color(obj.color)

	{}

	Node operator=(const Node& obj)
	{
		if (this == &obj)
			return (this);
		value = obj.val;
		left = obj.left;
		right = obj.right;
		parent = obj.parent;
		color = obj.color;
	}

	~Node() {}

};

template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
class RBTree
{
public:
	typedef T														value_type;
	typedef Compare													value_compare;
	typedef Node<T>													node;
	typedef typename Allocator::template rebind<node>::other		allocator_type;
	typedef typename allocator_type::pointer 						pointer;
	typedef typename allocator_type::const_pointer 					const_pointer;
	typedef std::size_t												size_type;

	//TODO iterators

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

	//copy
	//assign
	~RBTree()
	{
		_clear_node(_root);
		_allocator.destroy(_nil);
		_allocator.deallocate(_nil, 1);
	}
	//operator=()

private:

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
		return (newNode);
	}

	void _clear_node(pointer root)
	{
		if (root == _nil)
			return ;
		_clear_node(root->left);
		_clear_node(root->right);
		_allocator.destroy(root);
		_allocator.deallocate(root, 1);
		--_size;
		root = _nil;
	}

	pointer _findVal(pointer root, const value_type &val)
	{
		if (root == _nil)
			return (_nil);
		if (_comp(root->value, val))
				return _findVal(root->right, val);
		else if (_comp(val, root->value))
				return _findVal(root->left, val);
		else
			return (root);
	}

public:

	void insert(const value_type &val) //TODO return iterator
	{
		if (_findVal(_root, val) != _nil)
		{
			std::cout << "find it!" << std::endl;
			return;
		}
		pointer newNode = _allocator.allocate(1);
		_allocator.construct(newNode, node(_nil,_nil,_nil, 'R', val));
		_insert(_root, newNode);
		++_size;
		_root->color = 'B';
	}

	size_type size()
	{
		return (_size);
	}



	void print_tree()
	{
		inorderHelper(_root);
	}

	void inorderHelper(pointer root)
	{
		if (root == _nil)
			return;

		inorderHelper(root->left);
		root->color == 'B' ? std::cout << GREENCOL : std::cout << REDCOL;
		std::cout << root->value.second << "  " << RESCOL;
		inorderHelper(root->right);
	}
};

#endif //FT_CONTAINERS_RB_TREE_HPP
