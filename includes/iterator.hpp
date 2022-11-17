/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaciri- <hnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:50:42 by hnaciri-          #+#    #+#             */
/*   Updated: 2022/11/17 15:54:55 by hnaciri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "iterators_traits.hpp"

namespace	ft
{
	template <class _Iter>
	class __wrap_iter
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
	  	__wrap_iter() : __i(nullptr) {}
		__wrap_iter(pointer ptr) : __i(ptr) {}
		template <class Iter>
		__wrap_iter (const __wrap_iter<Iter>& it) : __i(it.base()) {}
		__wrap_iter(__wrap_iter const & src){*this = src;}
		virtual ~__wrap_iter() {}
		template <class Iter>
		__wrap_iter &operator=(__wrap_iter<Iter> const & it)
		{
			this->__i = it.base();
			return *this;
		}
		// Operators
		iterator_type	base() const
		{
			return (this->__i);
		}
		reference operator*() const
		{
			return( *(this->__i));
		}
		__wrap_iter	&operator++() 
		{
			++this->__i;
			return (*this);
		}
		__wrap_iter	operator++(int)
		{
			__wrap_iter	tmp = *this;
			this->__i++;
			return (tmp); 
		}
		__wrap_iter& operator+=(difference_type __n)
		{
			this->__i += __n;
			return (*this);
		}
		__wrap_iter  operator+ (difference_type __n) const
        {
			__wrap_iter __w(*this);
			__w += __n;
			return (__w);
		}
		__wrap_iter	&operator--()
		{
			--this->__i;
			return (*this);
		}
		__wrap_iter	operator--(int)
		{
			__wrap_iter	tmp = *this;
			this->__i--;
			return (tmp); 
		}
		__wrap_iter& operator-=(difference_type __n)
		{
			this->__i -= __n;
			return (*this);
		}
		__wrap_iter  operator- (difference_type __n) const
        {
			__wrap_iter __w(*this);
			__w -= __n;
			return (__w);
		}
		pointer	operator->() const
		{
			return (&(operator*()));
		}
		reference	operator[] (difference_type __n) const
		{
			return (this->__i[__n]);
		}
	};
	template <class _Iter1, class _Iter2>
	bool	operator == (const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
	{
		return (__x.base() == __y.base());
	}
	template <class _Iter1, class _Iter2>
	bool	operator != (const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
	{
		return (__x.base() != __y.base());
	}
	template <class _Iter1, class _Iter2>
	bool	operator < (const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
	{
		return (__x.base() < __y.base());
	}
    template <class _Iter1, class _Iter2>
	bool	operator <= (const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
	{
		return (__x.base() <= __y.base());
	}
    template <class _Iter1, class _Iter2>
	bool	operator > (const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
	{
		return (__x.base() > __y.base());
	}
	template <class _Iter1, class _Iter2>
	bool	operator >= (const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
	{
		return (__x.base() >= __y.base());
	}
	template <class Iterator>
  	__wrap_iter<Iterator> operator + (typename __wrap_iter<Iterator>::difference_type n, const __wrap_iter<Iterator>& rev_it)
	{
		return (rev_it + n);
	}
	template <class _Iter1, class _Iter2>
	size_t	operator - (const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
	{
		return (__x.base()) - (__y.base());
	}
}

#endif
