/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaciri- <hnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:28:04 by hnaciri-          #+#    #+#             */
/*   Updated: 2023/01/06 11:20:52 by hnaciri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PAIR_HPP
# define PAIR_HPP

#include <iostream>

namespace	ft
{
	template <class T1, class T2>
	struct	pair
	{
		//  ---------------------  Member types  --------------------
		typedef	T1	first_type;
		typedef	T2	second_type;
		//  ---------------------  Member variables  ----------------
		first_type	first;
		second_type	second;
		//  ---------------------  Member functions  ----------------
		pair () : first(first_type()), second(second_type()) {}
		template<class U, class V>
		pair (const pair<U,V>& pr) : first (pr.first), second (pr.second) {}
		pair (const first_type& a, const second_type& b) : first(a), second(b) {}
		pair& operator= (const pair& pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}
	};
	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		if ((lhs.first < rhs.first) || (lhs.first == rhs.first && lhs.second < rhs.second))
			return (true);
		return (false);	
	}
	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}
	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs > rhs || lhs == rhs);
	}
	template <class T1, class T2>
	pair<T1, T2> make_pair (T1 x, T2 y)
	{
		return (pair<T1, T2> (x, y));
	}
}

# endif
