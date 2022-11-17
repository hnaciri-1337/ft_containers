/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators_traits.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaciri- <hnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:44:56 by hnaciri-          #+#    #+#             */
/*   Updated: 2022/11/03 18:06:37 by hnaciri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef ITERATORS_TRAITS_HPP
# define ITERATORS_TRAITS_HPP

# include <iostream>
# include <iterator>

namespace	ft
{
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};
	
	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};
	
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};
}

# endif
