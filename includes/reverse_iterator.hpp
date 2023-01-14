/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaciri- <hnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:50:42 by hnaciri-          #+#    #+#             */
/*   Updated: 2023/01/14 14:45:08 by hnaciri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterators_traits.hpp"

namespace	ft
{
	template <class _Iter>
	class reverse_iterator
	{
	public:
		typedef _Iter															iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference			reference;
	private:
		iterator_type	__i;
	public:
		// Constructor & Destructor
	  	reverse_iterator() : __i() {}
		reverse_iterator(pointer ptr) : __i(ptr) {}
		reverse_iterator(iterator_type _it) : __i(_it) {}
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& it) : __i(it.base()) {}
		reverse_iterator(reverse_iterator const & src){*this = src;}
		virtual ~reverse_iterator() {}
		template <class Iter>
		reverse_iterator &operator=(reverse_iterator<Iter> const & it)
		{
			this->__i = it.base();
			return *this;
		}
		// Operators
		iterator_type	base() const
		{
			return (__i);
		}
		reference operator*()
		{
			iterator_type	temp = __i;
			temp--;
			return(*temp);
		}
		reference operator*() const
		{
			iterator_type	temp = __i;
			temp--;
			return(*temp);
		}
		reverse_iterator	&operator++() 
		{
			--__i;
			return (*this);
		}
		reverse_iterator	operator++(int)
		{
			reverse_iterator	tmp = *this;
			__i--;
			return (tmp); 
		}
		reverse_iterator& operator+=(difference_type __n)
		{
			__i -= __n;
			return (*this);
		}
		reverse_iterator  operator+ (difference_type __n) const
        {
			reverse_iterator __w(*this);
			__w.__i -= __n;
			return (__w);
		}
		reverse_iterator	&operator--()
		{
			++__i;
			return (*this);
		}
		reverse_iterator	operator--(int)
		{
			reverse_iterator	tmp = *this;
			__i++;
			return (tmp); 
		}
		reverse_iterator& operator-=(difference_type __n)
		{
			__i += __n;
			return (*this);
		}
		reverse_iterator  operator- (difference_type __n) const
        {
			reverse_iterator __w(*this);
			__w.__i += __n;
			return (__w);
		}
		pointer	operator->() const
		{
			return (&(operator*()));
		}
		reference	operator[] (difference_type __n) const
		{
			long long int	_n = -1 * __n;
			return (__i[_n - 1]);
		}
	};
	template <class _Iter1, class _Iter2>
	bool	operator == (const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
	{
		return (__x.base() == __y.base());
	}
	template <class _Iter1, class _Iter2>
	bool	operator != (const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
	{
		return (__x.base() != __y.base());
	}
	template <class _Iter1, class _Iter2>
	bool	operator < (const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
	{
		return (__y.base() < __x.base());
	}
    template <class _Iter1, class _Iter2>
	bool	operator <= (const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
	{
		return (__y.base() <= __x.base());
	}
    template <class _Iter1, class _Iter2>
	bool	operator > (const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
	{
		return (__y.base() > __x.base());
	}
	template <class _Iter1, class _Iter2>
	bool	operator >= (const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
	{
		return (__y.base() >= __x.base());
	}
	template <class Iterator>
  	reverse_iterator<Iterator> operator + (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	}
	template <class _Iter1, class _Iter2>
	size_t	operator - (const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
	{
		return (__y.base()) - (__x.base());
	}
	template <class Iterator>
  	typename reverse_iterator<Iterator>::difference_type operator - (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}
}

#endif
