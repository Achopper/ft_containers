/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achopper <achopper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:10:30 by achopper          #+#    #+#             */
/*   Updated: 2022/02/12 18:10:30 by achopper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "../utils/Utils.hpp"
#include "../vector/Vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:

		typedef Container 							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference const_reference;

	protected:

		container_type c;

	public:

		stack(const container_type& cont = container_type()) : c(cont) {}
		stack(const stack & obj) : c(obj.c) {}
		stack & operator=(const stack &obj)
		{
			if (this == &obj)
				return (*this);
			c = obj.c;
			return (*this);
		}

		bool empty() const
		{
			return c.empty();
		}
		size_type size()  const
		{
			return c.size();
		}
		reference top()
		{
			return c.back();
		}
		const_reference top() const
		{
			return c.back();
		}
		void push(const value_type& x)
		{
			c.push_back(x);
		}

		void pop()
		{
			c.pop_back();
		}

		template <class T1, class C1>
		friend bool operator== (const stack<T1, C1>& lhs, const stack<T1, C1>& rhs)
		{
			return (lhs.c == rhs.c);
		}

		template <class T1, class C1>
		friend bool operator<  (const stack<T1, C1>& lhs, const stack<T1, C1>& rhs)
		{
			return (lhs.c < rhs.c);
		}

	};

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs < rhs);
	}

}

#endif //FT_CONTAINERS_STACK_HPP