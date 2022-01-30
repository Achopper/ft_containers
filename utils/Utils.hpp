/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achopper <achopper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:49:22 by achopper          #+#    #+#             */
/*   Updated: 2022/01/30 17:49:22 by achopper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_UTILS_H
#define FT_CONTAINERS_UTILS_H

#include <memory>
#include <vector>
#include <iostream>

namespace ft {

	template <bool cond, class T = void>
	struct enable_if { };

	template <class T>
	struct enable_if<true, T>
	{ typedef T type; };
}

#endif
