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

void separator(std::string sep)
{
	std::cout << std::endl << GREENCOL << "########################################################################" << sep <<
	"########################################################################" <<  RESCOL << std::endl << std::endl;
}


int main ()
{
	separator("COPY AND COMPARE TESTS");
	ft::stack<int, ft::vector<int> > c(ft::vector<int>(4, 100));
	ft::stack<int, ft::vector<int> > x(ft::vector<int>(5, 100));
	if (c != x) std::cout << "is not equal \n";
	std::cout << "pop last elem\n";
	x.pop();
	if (c == x) std::cout << "now equal\n";
	std::cout << "push elem\n";
	x.push(200);
	if (c < x) std::cout << "firs less than second\n";
	for (size_t i = 0; i < 10; ++i)
		c.push(i);

	std::cout << c.size() << std::endl;

	x = c;

	for (size_t i = 0; !x.empty(); ++i)
	{
		std::cout << x.top()  << " ";
		x.pop();
	}

	std::cout << std::endl;

	for (size_t i = 0; !c.empty(); ++i)
		c.pop();

	std::cout << c.size() << std::endl;

	if (c.empty())
		std::cout << "stack now empty\n";
	else
		std::cout << "not empty yet\n";

}