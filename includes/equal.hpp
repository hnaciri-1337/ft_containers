/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaciri- <hnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:11:59 by hnaciri-          #+#    #+#             */
/*   Updated: 2023/01/16 11:29:18 by hnaciri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EQUAL_HPP
# define EQUAL_HPP


namespace	ft
{
	template <class InputIterator1, class InputIterator2>
	bool	equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		for (; first1 != last1; first1++, first2++)
			if (*first1 != *first2)
				return (false);
		return (true);
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool	equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		for (; first1 != last1; first1++, first2++)
			if (!pred(*first1, *first2))
				return (false);
		return (true);
	}

	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		for (; first1 != last1; first1++, first2++)
		{
			if (*first1 < *first2)
				return (true);
			else if (first2 == last2 || first1 > first2)
				return (false);
		}
		return (first2 != last2);
	}
}

# endif
