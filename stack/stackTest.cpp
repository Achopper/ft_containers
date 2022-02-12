/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackTest.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achopper <achopper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:12:38 by achopper          #+#    #+#             */
/*   Updated: 2022/02/12 18:12:38 by achopper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include <stack>

int main ()
{
	std::stack<int, std::vector<int> > a(std::vector<int>(5, 100));
	std::stack<int, std::vector<int> > b(std::vector<int>(5, 100));
	if (a == b)
		std::cout << "is equal \n";
	ft::vector<int> cop(4, 100);
	ft::stack<int> c(cop);
	ft::stack<int> x(ft::vector<int>(5, 100));
	if (c != x)
		std::cout << "is equal \n";
}