/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaciri- <hnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:35:14 by hnaciri-          #+#    #+#             */
/*   Updated: 2023/01/14 16:27:53 by hnaciri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace	ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public :
			typedef	T							value_type;
			typedef	Container					container_type;
			typedef	size_t						size_type;
			typedef	typename Container::reference		reference;
			typedef	typename Container::const_reference	const_reference;
		explicit	stack (const container_type& ctnr = container_type()) : c (ctnr){}
		bool		empty() const
		{
			return (c.empty());
		}
		size_type	size() const
		{
			return (c.size());
		}
		value_type&	top()
		{
			return (c[c.size() - 1]);
		}
		const value_type& top() const
		{
			return (c[c.size() - 1]);
		}
		void	push (const value_type& val)
		{
			c.push_back (val);
		}
		void	pop()
		{
			c.pop_back();
		}
		template <class _T, class _Container>
		friend bool operator== (const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs);
		template <class _T, class _Container>
		friend bool operator!= (const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs);
		template <class _T, class _Container>
		friend bool operator< (const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs);
		template <class _T, class _Container>
		friend bool operator<= (const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs);
		template <class _T, class _Container>
		friend bool operator> (const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs);
		template <class _T, class _Container>
		friend bool operator>= (const stack<_T,_Container>& lhs, const stack<_T,_Container>& rhs);
		protected :
			container_type	c;
	};
	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (rhs.c == lhs.c);
	}
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (rhs.c != lhs.c);
	}
	template <class T, class Container>
	bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c <= rhs.c);
	}
	template <class T, class Container>
	bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c > rhs.c);
	}
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c >= rhs.c);
	}
}

#endif
