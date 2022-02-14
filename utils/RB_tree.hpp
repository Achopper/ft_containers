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
	:	value(val),
		left(l),
		right(r),
		parent(p),
		color(col)
	{}

	Node(const Node& obj)
	:	value(obj.val),
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

template <class T, class Compare, class Allocator>
class RBTree
{

};

#endif //FT_CONTAINERS_RB_TREE_HPP
