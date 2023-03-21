/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaciri- <hnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:33:12 by hnaciri-          #+#    #+#             */
/*   Updated: 2023/01/14 14:43:13 by hnaciri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

# include <iostream>
# include "iterators_traits.hpp"
# include "iterator.hpp"
# include "reverse_iterator.hpp"
# include "tools.hpp"

namespace	ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector
    {
		public:
			//  ---------------------  Member types  --------------------
			typedef	T										value_type;
			typedef	Alloc									allocator_type;
			typedef	value_type&								reference;
			typedef	const value_type&						const_reference;
			typedef	value_type*								pointer;
			typedef	const value_type*						const_pointer;
			typedef ft::__wrap_iter<pointer>       			iterator;
			typedef ft::__wrap_iter<const_pointer>			const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef ptrdiff_t								difference_type;
			typedef size_t									size_type;

			
			//  -------------------  Constructor  ------------------------
			
			explicit vector (const allocator_type& alloc = allocator_type()): _allocator(alloc), _size(0), _capacity(0), _array(nullptr) {}
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _allocator(alloc), _size(n), _capacity(n), _array(_allocator.allocate(_size))
			{
				for (size_type i = 0; i < n; i++)
					_allocator.construct(_array + i, val);
			}
			template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : _allocator(alloc)
            {
				vector<value_type>	_vec;

				_size = distance(first, last, _vec);
				_capacity = _size;
				_array = _allocator.allocate(_capacity);
                for (size_type i = 0, j = 0; j < _vec.size(); i++, j++)
                    _allocator.construct(_array + i, _vec[j]);
            }
            vector (const vector & x)
            {
                _size = x.size();
                _capacity = _size;
                _allocator = x._allocator;
                _array = _allocator.allocate(_capacity);
                for (size_type i = 0; i < _size; i++)
                    _allocator.construct(_array + i, x[i]);
            }
			vector& operator= (const vector& x)
			{
				if (_array)
				{
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(_array + i);
					_allocator.deallocate(_array, _capacity);
				}
				_size = x.size();
				_capacity = x.capacity();
				_allocator = x._allocator;
				_array = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(_array + i, x[i]);
				return (*this);
			}
			~vector()
			{
				if (_array)
				{
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(_array + i);
					_allocator.deallocate(_array, _capacity);
				}
			}
			//  ----------------------- Member functions  --------------------------
			
			//  | ITERATOR |
			iterator				begin()
			{
				return (iterator(_array));
			}
			const_iterator			begin() const
			{
				return (iterator(_array));
			}
			iterator				end()
			{
				return (iterator(_array + _size));
			}
			const_iterator			end() const
			{
				return (iterator(_array + _size));
			}
			reverse_iterator		rbegin()
			{
				return (reverse_iterator(_array + _size));
			}
			const_reverse_iterator	rbegin() const
			{
				return (reverse_iterator(_array + _size));
			}
			reverse_iterator		rend()
			{
				return (reverse_iterator(_array));
			}
			const_reverse_iterator	rend() const
			{
				return (reverse_iterator(_array));
			}
			// | CAPACITY |
			size_type				size() const
			{
				return (_size);
			}
			size_type				max_size() const
			{
				if (PTRDIFF_MAX < _allocator.max_size())
					return (PTRDIFF_MAX);
				return (_allocator.max_size());
			}
			void					resize (size_type n, value_type val = value_type())
			{
				pointer	tmp;

				if (n > _allocator.max_size())
					std::__throw_length_error("vector");
				if (n < _size)
				{
					for (size_type i = n; i < _size; i++)
						_allocator.destroy(_array + i);
					_size = n;
				}
				else if (n > _capacity)
				{
					try
					{
						if (n > _capacity * 2)
							tmp = _allocator.allocate(n);
						else
							tmp = _allocator.allocate(_capacity * 2);
					}
					catch(const std::exception& e)
					{
						std::__throw_bad_alloc();
					}
					for (size_type i = 0; i < _size; i++)
					{
						_allocator.construct(tmp + i, _array[i]);
						_allocator.destroy(_array + i);
					}
					for (size_type i = _size; i < n; i++)
						_allocator.construct(tmp + i, val);
					if (_array)
						_allocator.deallocate(_array, _capacity);
					_array = tmp;
					_size = n;
					if (n > _capacity * 2)
						_capacity = n;
					else
						_capacity = _capacity * 2;
				}
				else
				{
					for (size_type i = _size; i < n; i++)
						_allocator.construct(_array + i, val);
					_size = n;
				}
			}
			size_type				capacity() const
			{
				return (_capacity);
			}
			bool					empty() const
			{
				if (_size)
					return (false);
				return (true);
			}
			void					reserve (size_type n)
			{
				pointer	tmp;

				if (n > _allocator.max_size())
					std::__throw_length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				if (n > _capacity)
				{
					try
					{
						tmp = _allocator.allocate(n);
					}
					catch(const std::exception& e)
					{
						std::__throw_bad_alloc();
					}
					for (size_type i = 0; i < _size; i++)
					{
						_allocator.construct(tmp + i, _array[i]);
						_allocator.destroy(_array + i);
					}
					if (_array)
						_allocator.deallocate(_array, _capacity);
					_array = tmp;
					_capacity = n;
				}
			}
			// | ELEMENT ACCESS |
			reference				operator[] (size_type n)
			{
				return (_array[n]);
			}
			const_reference			operator[] (size_type n) const
			{
				return (_array[n]);
			}
			reference				at (size_type n)
			{
				if (n >= _size)
					std::__throw_out_of_range("vector");
				return (_array[n]);
			}
			const_reference			at (size_type n) const
			{
				if (n >= _size)
					std::__throw_out_of_range("vector");
				return (_array[n]);
			}
			reference				front()
			{
				return (*_array);
			}
			const_reference			front() const
			{
				return (*_array);
			}
			reference				back()
			{
				return (_array[_size - 1]);
			}
			const_reference			back() const
			{
				return (_array[_size - 1]);
			}
			// | MODIFIERS |
			template <class InputIterator>
			void					assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
			{
				vector<value_type>	_vec;
				if (_array)
				{
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(_array + i);
					_allocator.deallocate(_array, _capacity);
				}
				_size = distance(first, last, _vec);
				if (_capacity < _size)
					_capacity = _size;
				_array = _allocator.allocate(_capacity);
				for (size_type i = 0, j = 0; j < _vec.size(); i++, j++)
                    _allocator.construct(_array + i, _vec[j]);
			}
			void					assign (size_type n, const value_type& val)
			{
				if (_array)
				{
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(_array + i);
					_allocator.deallocate(_array, _capacity);
				}
				_size = n;
				if (_capacity < _size)
					_capacity = _size;
				_array = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(_array + i, val);
			}
			void					push_back (const value_type& val)
			{
				pointer	tmp;
				if (_size == _capacity)
				{
					if (!_capacity)
						tmp = _allocator.allocate(1);
					else
						tmp = _allocator.allocate(_capacity * 2);
					for (size_type i = 0; i < _size; i++)
					{
						_allocator.construct(tmp + i, _array[i]);
						_allocator.destroy(_array + i);
					}
					if (_array)
						_allocator.deallocate(_array, _capacity);
					_array = tmp;
					if (!_capacity)
						_capacity = 1;
					else
						_capacity *= 2;
				}
				_allocator.construct(_array + _size++, val);
			}
			void					pop_back()
			{
				if (!_size)
					return ;
				--_size;
				_allocator.destroy(_array + _size);
			}
			iterator				insert (iterator position, const value_type& val)
			{
				size_type	pos;
				iterator	it;

				pos = position - begin();
				resize(_size + 1, val);
				for (size_type i = _size - 1; i > pos; i--)
					_array[i] = _array[i - 1];
				_array[pos] = val;
				return (begin() + pos);
			}
    		iterator				insert (iterator position, size_type n, const value_type& val)
			{
				size_type	pos;
				iterator	it;
				
				if (!n)
					return (position);
				pos = position - begin();
				resize(_size + n, val);
				for (size_type i = _size - 1; i >= pos + n; i--)
					_array[i] = _array[i - n];
				for (size_type i = pos; i < pos + n; i++)
					_array[i] = val;
				return (begin() + pos);
			}
			template <class InputIterator>
			iterator				insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
			{
				size_type			pos;
				iterator			it;
				vector<value_type>	_vec;
				size_type	n = distance(first, last, _vec);

				if (!n)
					return (position);
				pos = position - begin();
				resize(_size + n, T());
				for (size_type i = _size - 1; i >= pos + n; i--)
					_array[i] = _array[i - n];
				for (size_type i = pos, j = 0; i < pos + n; i++, j++)
				{
					_array[i] = _vec[j];
					first++;
				}
				return (begin() + pos);
			}
			iterator				erase (iterator position)
			{
				size_type	pos = position - begin();

				for (size_type i = pos; i < _size - 1; i++)
					_array[i] = _array[i + 1];
				pop_back();
				return(position);
			}
			iterator				erase (iterator first, iterator last)
			{
				size_type	pos = first - begin();
				size_type	n = last - first;
				for (size_type i = pos; i < _size - n; i++)
					_array[i] = _array[i + n];
				while (n--)
					pop_back();
				return(first);
			}
			void swap (vector& x)
            {
                size_type		tmp_size;
				pointer			tmp_ptr;
				allocator_type	tmp_alloc;

				tmp_alloc = _allocator;
				_allocator = x._allocator;
				x._allocator = tmp_alloc;
				tmp_ptr = _array;
				_array = x._array;
				x._array = tmp_ptr;
				tmp_size = _size;
				_size = x._size;
				x._size = tmp_size;
				tmp_size = _capacity;
				_capacity = x._capacity;
				x._capacity = tmp_size;
            }
			void					clear()
			{
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(_array + i);
				_size = 0;	
			}
			// | ALLOCATOR |
			allocator_type			get_allocator() const
			{
				return (_allocator);
			}
		private:
			allocator_type	_allocator;
            size_type		_size;
            size_type		_capacity;
            pointer			_array;
    };
	template <class InputIterator, class T>
	size_t							distance(InputIterator first, InputIterator last, ft::vector<T> &_vec)
	{
		size_t	ret = 0;

		while (first != last)
		{
			ret++;
			_vec.push_back(*first);
			first++;
		}
		return (ret);
	}
	template <class T, class Alloc>
	void							swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
	template <class T, class Alloc>
	bool							operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		for (typename vector<T,Alloc>::size_type i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return (false);
		return (true);
	}
	template <class T, class Alloc>
	bool							operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T, class Alloc>
	bool							operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		typename vector<T,Alloc>::size_type i = 0;
		for (; i < lhs.size() && i < rhs.size() && lhs[i] == rhs[i]; i++)
			;
		if (i == rhs.size())
			return (false);
		if (i == lhs.size())
			return (true);
		return (lhs[i] < rhs[i]);
	}
	template <class T, class Alloc>
	bool							operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool							operator<=  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs > rhs));
	}
	template <class T, class Alloc>
	bool							operator>=  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif
