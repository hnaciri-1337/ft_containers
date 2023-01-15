/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaciri- <hnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:16:32 by hnaciri-          #+#    #+#             */
/*   Updated: 2023/01/15 16:07:16 by hnaciri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SET_HPP
# define SET_HPP

#include "set_red_black.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "map_iterator.hpp"

namespace	ft
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		public:
			//  ---------------------  Member types  --------------------
			typedef	T																							key_type;
			typedef	T																							value_type;
			typedef	Compare																						key_compare;
			typedef	Compare																						value_compare;
			typedef	Alloc																						allocator_type;
			typedef	typename allocator_type::reference															reference;
			typedef	typename allocator_type::const_reference													const_reference;
			typedef	typename allocator_type::pointer															pointer;
			typedef	typename allocator_type::const_pointer														const_pointer;
			typedef ft::__red_black_iterator<value_type *, ft::set_Node<T, allocator_type> *>					iterator;
			typedef ft::__red_black_iterator<const value_type *, ft::set_Node<T, allocator_type> *>				const_iterator;
			typedef ft::reverse_iterator<iterator>																reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>														const_reverse_iterator;
			typedef ptrdiff_t																					difference_type;
			typedef size_t																						size_type;
		private :
			key_compare												c;
			allocator_type											a;
			ft::set_redblack_tree<T, key_compare, allocator_type>	_set;
			void	print ()
			{
				_set.print (_set.get_root());
			}
		public :
			explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : c(comp), a(alloc) {}
			template <class InputIterator>
			set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : c(comp), a(alloc)
			{
				while (first != last)
				{
					_set.insert (*first);
					first++;
				}
			}
			set (const set& x)
			{
				a = x.a;
				c = x.c;
				for (iterator it = x.begin(); it != x.end(); it++)
					_set.insert (*it);
			}
			set& operator= (const set& x)
			{
				c = x.c;
				a = x.a;
				_set.clear ();
				for (iterator it = x.begin(); it != x.end(); it++)
					_set.insert (*it);
				return (*this);
			}
			iterator	begin ()
			{
				set_Node<key_type, allocator_type>	*_min = _set.get_min();
				return (iterator (_min, _set.get_root()));
			}
			const_iterator	begin () const
			{
				set_Node<key_type, allocator_type>	*_min = _set.get_min();
				return (iterator (_min, _set.get_root()));
			}
			iterator	end ()
			{
				return (iterator(nullptr, _set.get_root()));
			}
			const_iterator	end () const
			{
				return (iterator(nullptr, _set.get_root()));
			}
			reverse_iterator	rbegin ()
			{
				set_Node<key_type, allocator_type>	*_max = _set.get_max();
				iterator __a = iterator(_max, _set.get_root());
				__a++;
				return (__a);
			}
			reverse_iterator	rend ()
			{
				set_Node<key_type, allocator_type>	*_min = _set.get_min();
				return (iterator(_min, _set.get_root()));
			}
			reverse_iterator	rbegin () const
			{
				set_Node<key_type, allocator_type>	*_max = _set.get_max();
				iterator __a = iterator(_max, _set.get_root());
				__a++;
				return (__a);
			}
			reverse_iterator	rend () const
			{
				set_Node<key_type, allocator_type>	*_min = _set.get_min();
				return (iterator(_min, _set.get_root()));
			}
			bool				empty() const
			{
				return (!size());
			}
			size_type			size() const
			{
				return (_set.size());
			}
			size_type			max_size() const
			{
				return (a.max_size());
			}
			ft::pair<iterator, bool>	insert (const value_type& val)
			{
				ft::pair<iterator, bool>	ret;
				bool						var;
			
				var = _set.insert (val);
				ret.first = iterator (_set.find_node (val), _set.get_root());
				ret.second = var;
				return (ret);
			}
			iterator		insert (iterator position, const value_type& val)
			{
				(void) position ;
 				return (insert (val).first);
			}
			template <class InputIterator> 
			void			insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					_set.insert (*first);
					first++;
				}
			}
			size_type		erase (const key_type &k)
			{
				return (_set.erase (k));
			}
			void erase (iterator position)
			{
				if (position != end())
					_set.erase (*position);
			}
			void erase (iterator first, iterator last)
			{
				while (first != last)
				{
					iterator	temp = first;
					temp++;
					_set.erase(*first);
					first = temp;
				}
			}
			void				clear ()
			{
				_set.clear();
			}
			size_type			count (const key_type& k) const
			{
				return (!!(_set.find_node(k)));
			}
			key_compare key_comp() const
			{
				return (c);
			}
			value_compare value_comp() const
			{
				return (value_compare(key_comp()));
			}
			iterator find (const key_type& k) const
			{
				return (iterator(_set.find_node(k), _set.get_root()));
			}
			allocator_type get_allocator() const
			{
				return (a);
			}		
			iterator lower_bound (const key_type& k) const
			{
				return (iterator(_set.lower_bound(k), _set.get_root()));
			}
			iterator upper_bound (const key_type& k) const
			{
				return (iterator(_set.upper_bound(k), _set.get_root()));
			}
			pair<iterator,iterator>             equal_range (const key_type& k) const
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}
			void swap (set& x)
			{
				key_compare												_c = this->c;
				allocator_type											_a = this->a;
				this->c = x.c;
				this->a = x.a;
				x.c = _c;
				x.a = _a;
				ft::set_Node<key_type, allocator_type> *a = *x._set.get_root();
				x._set.set_root(*this->_set.get_root());
				this->_set.set_root(a);
				size_type	s = this->_set.size();
				this->_set.set_size(x._set.size());
				x._set.set_size(s);
			}
			~set() {};
	};
	template <class T, class Compare, class Alloc>
	void swap (set<T, Compare, Alloc>& x, set<T, Compare, Alloc>& y)
	{
		x.swap (y);
	}
	template <class T, class Compare, class Alloc>
	bool operator == (const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		for (typename set<T, Compare, Alloc>::iterator it = lhs.begin(), it2 = rhs.begin(); it != lhs.end(); it++, it2++)
		{
			if (*it != *it2)
				return (false);
		}
		return (true);
	}
	template <class T, class Compare, class Alloc>
	bool operator != (const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T, class Compare, class Alloc>
	bool operator > (const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		for (typename set<T, Compare, Alloc>::iterator it = lhs.begin(), it2 = rhs.begin(); it != lhs.end() && it2 != rhs.end(); it++, it2++)
		{
			if (*it > *it2)
				return (true);
			if (*it != *it2)
				return (false);
		}
		return (lhs.size() > rhs.size());
	}
	template <class T, class Compare, class Alloc>
	bool operator < (const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		return (rhs > lhs);
	}
	template <class T, class Compare, class Alloc>
	bool operator <= (const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}
	template <class T, class Compare, class Alloc>
	bool operator >= (const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{
		return (lhs > rhs || lhs == rhs);
	}
}

#endif
