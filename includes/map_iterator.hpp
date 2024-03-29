/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaciri- <hnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:54:56 by hnaciri-          #+#    #+#             */
/*   Updated: 2023/01/14 16:28:36 by hnaciri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR
#define MAP_ITERATOR

#include "red_black.hpp"

namespace	ft
{
	template <class _pair, class node>
	class __red_black_iterator
	{
	public:
		typedef _pair																							iterator_type;
		typedef typename ft::iterator_traits<iterator_type, std::bidirectional_iterator_tag>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<iterator_type, std::bidirectional_iterator_tag>::value_type		value_type;
		typedef typename ft::iterator_traits<iterator_type, std::bidirectional_iterator_tag>::difference_type	difference_type;
		typedef typename ft::iterator_traits<iterator_type, std::bidirectional_iterator_tag>::pointer			pointer;
		typedef typename ft::iterator_traits<iterator_type, std::bidirectional_iterator_tag>::reference			reference;
	private:
		node			__i;
		node const		*__root;
		node	predecessor(node _node)
		{
			node	cur = _node->left;
			if (cur)
			{
				while(cur->right != NULL)
					cur = cur->right;
				return (cur);
			}
			node	parent = _node->parent;
			while (parent != nullptr && _node == parent->left)
			{
				_node = parent;
				parent = parent->parent;
			}
			return (parent);
		}
		node	successor(node _node)
		{
			node	cur = _node->right;
			if (cur)
			{
				while(cur->left != NULL)
					cur = cur->left;
				return (cur);
			}
			node	parent = _node->parent;
			while (parent != nullptr && _node == parent->right)
			{
				_node = parent;
				parent = parent->parent;
			}
			return (parent);
		}
		node	base() const
		{
			return (this->__i);
		}
	public:
		// Constructor & Destructor
	  	__red_black_iterator() : __i(nullptr), __root(nullptr) {}
		__red_black_iterator(node ptr, node const*_root) : __i(ptr), __root(_root) {}
		template <class a, class _node>
		__red_black_iterator (const __red_black_iterator<a, _node>& it) : __i(it.__i), __root(&(*it.__root)) {}
		__red_black_iterator(__red_black_iterator const &src){*this = src;}
		virtual ~__red_black_iterator() {}
		template <class a, class _node>
		__red_black_iterator &operator=(__red_black_iterator<a, _node> const &it)
		{
			this->__i = it.__i;
			this->__root = &(*it.__root);
			return (*this);
		}

		// Operators
		reference operator*() const
		{
			return(*(__i->value));
		}
		reference operator*()
		{
			return(*(__i->value));
		}
		__red_black_iterator	&operator++()
		{
			if (__i == nullptr)
			{
				__i = *__root;
				while (__i->left)
					__i = __i->left;	
			}
			__i = successor(__i);
			return (*this);
		}
		__red_black_iterator	operator++(int)
		{
			__red_black_iterator	tmp = *this;
			++(*this);
			return (tmp); 
		}
		__red_black_iterator	&operator--()
		{
			if (__i == nullptr)
			{
				__i = *__root;
				while (__i->right)
					__i = __i->right;	
			}
			else
				__i = predecessor(__i);
			return (*this);
		}
		__red_black_iterator	operator--(int)
		{
			__red_black_iterator	tmp = *this;
			--(*this);
			return (tmp); 
		}
		pointer	operator->()
		{
			return (&(operator*()));
		}
		pointer	operator->()  const
		{
			return (&(operator*()));
		}
		template <class __pair, class _node>
		friend class __red_black_iterator;
		template <class a, class node1, class b, class node2>
		friend bool	operator != (const __red_black_iterator<a, node1>& __x, const __red_black_iterator<b, node2>& __y);
		template <class a, class node1, class b, class node2>
		friend bool	operator == (const __red_black_iterator<a, node1>& __x, const __red_black_iterator<b, node2>& __y);
	};
	template <class a, class node1, class b, class node2>
	bool	operator == (const __red_black_iterator<a, node1>& __x, const __red_black_iterator<b, node2>& __y)
	{
		return (__x.base() == __y.base());
	}
	template <class a, class node1, class b, class node2>
	bool	operator != (const __red_black_iterator<a, node1>& __x, const __red_black_iterator<b, node2>& __y)
	{
		return (__x.base() != __y.base());
	}
}

#endif

