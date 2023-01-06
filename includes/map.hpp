/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaciri- <hnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:16:32 by hnaciri-          #+#    #+#             */
/*   Updated: 2023/01/06 15:06:07 by hnaciri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MAP_HPP
# define MAP_HPP

#include "includes.hpp"

namespace	ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:
			//  ---------------------  Member types  --------------------
			typedef	Key																							key_type;
			typedef	T																							mapped_type;
			typedef	ft::pair<const key_type, mapped_type>														value_type;
			typedef	Compare																						key_compare;
			typedef class value_compare : std::binary_function<value_type, value_type, bool>
            {   
                friend class map;
                protected:
                    Compare comp;
                public:
                    value_compare (Compare c) : comp(c) {}
                    typedef bool result_type;
                    typedef value_type first_argument_type;
                    typedef value_type second_argument_type;
                    bool operator() (const value_type& x, const value_type& y) const
                    {
                        return comp(x.first, y.first);
                    }
            }																									value_compare;
			typedef	Alloc																						allocator_type;
			typedef	typename allocator_type::reference															reference;
			typedef	typename allocator_type::const_reference													const_reference;
			typedef	typename allocator_type::pointer															pointer;
			typedef	typename allocator_type::const_pointer														const_pointer;
			typedef ft::__red_black_iterator<value_type *, ft::Node<Key, T> *>									iterator;
			typedef ft::__red_black_iterator<const value_type *, ft::Node<Key, T> *>							const_iterator;
			typedef ft::reverse_iterator<iterator>																reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>														const_reverse_iterator;
			typedef ptrdiff_t																					difference_type;
			typedef size_t																						size_type;
		public :
			key_compare												c;
			allocator_type											a;
			ft::redblack_tree<Key, T, key_compare, allocator_type>	_map;
		public :
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : c(comp), a(alloc) {}
			template <class InputIterator> 
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : c(comp), a(alloc)
			{
				while (first != last)
				{
					_map.insert (*first);
					first++;
				}
			}
			map (const map& x)
			{
				a = x.a;
				c = x.c;
				for (iterator it = x.begin(); it != x.end(); it++)
					_map.insert (*it);
			}
			map& operator= (const map& x)
			{
				c = x.c;
				a = x.a;
				_map.clear ();
				for (iterator it = x.begin(); it != x.end(); it++)
					_map.insert (*it);
				return (*this);
			}
			mapped_type& at (const key_type& k)
			{
				iterator	it = find(k);
				if (it == end())
					throw std::out_of_range("map::at:  key not found");
				else
					return (it->second);
			}
			const mapped_type& at (const key_type& k) const
			{
				iterator	it = find(k);
				if (it == end())
					throw std::out_of_range("map::at:  key not found");
				else
					return (it->second);
			}
			ft::pair<iterator, bool>	insert (const value_type& val)
			{
				ft::pair<iterator, bool>	ret;
				bool						var;
			
				var = _map.insert (val);
				ret.first = iterator (_map.find_node (val.first));
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
					_map.insert (*first);
					first++;
				}
			}
			size_type erase (const key_type& k)
			{
				return (_map.erase(k));
			}
			void	print ()
			{
				_map.print (_map.get_root());
			}
			iterator	begin ()
			{
				Node<key_type, mapped_type>	*_min = _map.get_min();
				return (iterator (_min));
			}
			const_iterator	begin () const
			{
				Node<key_type, mapped_type>	*_min = _map.get_min();
				return (iterator (_min));
			}
			iterator	end ()
			{
				return (iterator());
			}
			const_iterator	end () const
			{
				return (iterator());
			}
			reverse_iterator	rbegin ()
			{
				Node<key_type, mapped_type>	*_max = _map.get_max();
				return (iterator (_max));
			}
			reverse_iterator	rend ()
			{
				return (iterator());
			}
			const_reverse_iterator	rbegin () const
			{
				Node<key_type, mapped_type>	*_max = _map.get_max();
				return (iterator (_max));
			}
			const_reverse_iterator	rend () const
			{
				return (iterator());
			}
			void				clear ()
			{
				_map.clear();
			}
			bool				empty() const
			{
				return (!!(size()));
			}
			size_type			count (const key_type& k) const
			{
				return (!!(_map.find_node(k)));
			}
			size_type			size() const
			{
				return (_map.size());
			}
			size_type			max_size() const
			{
				return (a.max_size());
			}
			mapped_type&		operator[] (const key_type& k)
			{
				return ((this->insert(ft::make_pair(k, mapped_type())).first)->second);
			}
			iterator find (const key_type& k)
			{
				return (_map.find_node(k));
			}
			const_iterator find (const key_type& k) const
			{
				return (_map.find_node(k));
			}
			allocator_type get_allocator() const
			{
				return (a);
			}
			key_compare key_comp() const
			{
				return (c);
			}
			value_compare value_comp() const
			{
				return (value_compare(key_comp()));
			}
			iterator lower_bound (const key_type& k)
			{
				return (_map.lower_bound(k));
			}
			const_iterator lower_bound (const key_type& k) const
			{
				return (_map.lower_bound(k));
			}
			iterator upper_bound (const key_type& k)
			{
				return (_map.upper_bound(k));
			}
			const_iterator upper_bound (const key_type& k) const
			{
				return (_map.upper_bound(k));
			}
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}
			pair<iterator,iterator>             equal_range (const key_type& k)
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}
			void swap (map& x)
			{
				map	a = x;
				x = *this;
				*this = a;
			}
			~map() {};
	};
	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y)
	{
		x.swap (y);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator == (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		for (typename map<Key, T, Compare, Alloc>::iterator it = lhs.begin(), it2 = rhs.begin(); it != lhs.end(); it++, it2++)
		{
			if (*it != *it2)
				return (false);
		}
		return (true);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator != (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator > (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		for (typename map<Key, T, Compare, Alloc>::iterator it = lhs.begin(), it2 = rhs.begin(); it != lhs.end() && it2 != rhs.end(); it++, it2++)
		{
			if (*it > *it2)
				return (true);
			if (*it != *it2)
				return (false);
		}
		return (lhs.size() > rhs.size());
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator < (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (rhs > lhs);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator <= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator >= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (lhs > rhs || lhs == rhs);
	}
}

#endif
