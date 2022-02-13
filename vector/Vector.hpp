/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achopper <achopper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 20:15:13 by achopper          #+#    #+#             */
/*   Updated: 2022/02/09 20:15:13 by achopper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "../utils/Utils.hpp"
#include "../iterators/RandomAccessIterator.hpp"
#include <iterator>
#include "../iterators/ReverseIterator.hpp"


namespace ft
{
	template<class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef 									std::size_t size_type;
		typedef 									std::ptrdiff_t difference_type;
		typedef typename Allocator::const_pointer 	const_pointer;
		typedef typename Allocator::pointer 		pointer;
		typedef Allocator 							allocator_type;
		typedef T 									value_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef  random_access_iterator<value_type> iterator;
		typedef  random_access_iterator<value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> 		reverse_iterator; //TODO make rev_it
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		size_type 							_size;
		size_type 							_capacity;
		pointer 							_data;
		allocator_type 						_allocator;

		//CONSTRUCTORS--------------------------------------------------------------------------------------------------
	public:
		 vector(const allocator_type &allocator = allocator_type())
				: _size(0),
				  _capacity(0),
				  _data(0),
				  _allocator(allocator)
		{}


		 vector(size_type n, const value_type &val = value_type(),
						const allocator_type &allocator = allocator_type())
				: _size(n),
				  _capacity(n),
				  _allocator(allocator)
		{
			try
			{
				if (_capacity)
					_data = _allocator.allocate(n);
			} catch (std::bad_alloc &ex)
			{
				std::cout << ex.what();
			}
			for (size_type i = 0; i < n; ++i)
				_allocator.construct(_data + i, val);
		}

		template <class InputIterator>
		vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type()
						,typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) : _allocator(alloc)
		{
			if (first > last)
				throw (std::length_error("Vector"));
			_size = ft::distance(first, last);
			_data = _allocator.allocate(_size);
			_capacity = _size;
			for (size_type i = 0; i < _size; ++i)
				_allocator.construct(_data + i, *(first + i));
		}

		vector(const vector &obj) : _size(0), _capacity(0)
		{
			*this = obj;
		}

		//DESTRUCTOR----------------------------------------------------------------------------------------------------
		~vector()
		{
			clear();
			if (_capacity)
				_allocator.deallocate(_data, _capacity);
		}

		//OPERATORS-----------------------------------------------------------------------------------------------------
		vector &operator=(const vector &obj)
		{
			if (this == &obj)
				return (*this);
			clear();
			_size = obj._size;
			if (_capacity < _size)
			{
				if (_capacity != 0)
					_allocator.deallocate(_data, _capacity);
				_capacity = _size;
				try
				{
					_data = _allocator.allocate(obj._capacity);
				} catch (std::bad_alloc &ex)
				{
					std::cout << ex.what();
				}
			}
			for (size_type i = 0; i < _size; ++i)
				_allocator.construct(_data + i, obj._data[i]);
			return (*this);
		}
		//ITERATOR------------------------------------------------------------------------------------------------------
		iterator begin()
		{
			return (iterator(_data));
		}

		const_iterator begin() const
		{
			return (const_iterator(_data));
		}

		iterator end()
		{
			return (iterator(_data + _size));
		}

		const_iterator end() const
		{
			return (const_iterator(_data + _size));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(end()));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(end()));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(begin()));
		}

		//CAPACITY------------------------------------------------------------------------------------------------------
		size_type capacity() const
		{
			return (_capacity);
		}

		size_type size() const
		{
			return (_size);
		}

		size_type max_size() const
		{
			return (_allocator.max_size());
		}

		bool empty() const
		{
			return (_size == 0);
		}

		void reserve(size_type n)
		{
			if (_capacity <= n)
			{
				if (n > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				vector<value_type> tmp(0);
				try
				{
					tmp._data = tmp._allocator.allocate(n);
				} catch (std::bad_alloc &ex)
				{
					std::cout << ex.what();
				}
				tmp._capacity = n;
				for (size_type i = 0; i < _size; ++i)
					_allocator.construct(tmp._data + i, _data[i]);
				tmp._size = _size;
				swap(tmp);
			}
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n > max_size() || n < 0)
				throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds not supported size");
			if (n < _size)
			{
				for (size_type i = 0; i < n; ++i)
					_allocator.destroy(_data + i);
				_size = n;
			}
			else if (n > _size)
			{
				if (n > _capacity)
				{
					try
					{
						reserve(_capacity << 2 > n ? _capacity << 2 : n);
					} catch (std::exception &ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				for (size_type i = _size; i < n; ++i)
				{
					_allocator.construct(_data + i, val);
					_size++;
				}
			}
		}

		//ELEMENT ACCESS------------------------------------------------------------------------------------------------

		reference operator[](size_type n)
		{
			return (_data[n]);
		}

		const_reference operator[](size_type n) const
		{
			return (_data[n]);
		}

		reference front()
		{
			return (_data[0]);
		}

		const_reference front() const
		{
			return (_data[0]);
		}

		reference back()
		{
			return (_data[_size - 1]);
		}

		const_reference back() const
		{
			return (_data[_size - 1]);
		}

		reference at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("Out of rang in at()");
			return (_data[n]);
		}

		const_reference at(size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("Out of rang in at()");
			return (_data[n]);
		}

		//MODIFIERS-----------------------------------------------------------------------------------------------------

		void push_back(const value_type &val)
		{
			if (_size >= _capacity)
			{
				try
				{
					reserve(_capacity < 1 ? ++_capacity << 1 : _capacity << 1);
				} catch (std::exception &ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			_allocator.construct(_data + _size, val);
			_size++;
		}

		void pop_back()
		{
			_allocator.destroy(_data + (_size - 1));
			--_size;
		}

		void clear()
		{
			for (size_type i = 0; i < _size; ++i)
				_allocator.destroy(_data + i);
			_size = 0;
		}

		void swap(vector &obj)
		{
			std::swap(_allocator, obj._allocator);
			std::swap(_capacity, obj._capacity);
			std::swap(_size, obj._size);
			std::swap(_data, obj._data);
		}

		iterator insert (iterator position, const value_type& val)
		{
			if (position < begin() || position > end())
				throw std::logic_error("Vector: in insert");
			insert(position, 1, val);
			return (position);
		}

		void insert(iterator position, size_type n, const value_type& val)
		{
			if (n > max_size())
				throw std::length_error("Vector: in insert");
			if (position < begin() || position > end())
				throw std::logic_error("Vector: in insert");
			difference_type start = position - begin();
			if (n == 0)
				;
			else if ((_size + n) > _capacity)
			{
				difference_type i = 0;
				pointer newPtr;
				size_type new_cap = (_capacity << 1) > _size + n ? _capacity << 1 : _size + n;
				try
				{
					newPtr = _allocator.allocate(new_cap);
				}
				catch (std::bad_alloc &ex)
				{
					std::cout << ex.what();
				}
				for (; i < start; ++i)
					_allocator.construct(newPtr + i, _data[i]);
				for (; i < (start + static_cast<difference_type>(n)); ++i)
					_allocator.construct(newPtr + i, val);
				for (; i < static_cast<difference_type>(_size + n); ++i)
					_allocator.construct(newPtr + i, _data[i - n]);
				for (size_type i = 0; i < _size; ++i)
					_allocator.destroy(_data + i);
				_allocator.deallocate(_data, _capacity);
				_capacity = new_cap;
				_size += n;
				_data = newPtr;
			}
			else
			{
				for (difference_type i = _size + n; i >= static_cast<difference_type>(start + n); --i)
					_allocator.construct(_data + i, _data[i - n]);
				for (difference_type i = start; i < start + static_cast<difference_type>(n); ++i)
					_allocator.destroy(_data + i);
				for (difference_type i = start; i < start + static_cast<difference_type>(n); ++i)
					_allocator.construct(_data + i, val);
				_size += n;
			}
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
					 typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			if (position < begin() || position > end() || first > last || last < first)
				throw std::logic_error("Vector: in range insert");
			difference_type count = ft::distance(first, last);
			difference_type start = ft::distance(position, begin());
			if (first == last)
				return ;
			else if (_size + count > _capacity)
			{
				size_type newCap = (_capacity << 1) > _size + count ? _capacity << 1 : _size + count;;
				pointer newArr;
				try
				{
					newArr = _allocator.allocate(newCap);
				}
				catch (std::bad_alloc &ex)
				{
					std::cout << ex.what();
				}
				for (difference_type i = 0; i < start; ++i)
					_allocator.construct(newArr + i, _data[i]);
				for (difference_type i = start; i <= (start + count); ++i, first++)
					_allocator.construct(newArr + i, *first);
				for (difference_type i = start + count; i < static_cast<difference_type>(_size) + count; ++i)
					_allocator.construct(newArr + i, _data[i - count]);
				for (size_type i = 0; i < _size; ++i)
					_allocator.destroy(_data + i);
				_size +=  count;
				_allocator.deallocate(_data, _capacity);
				_capacity = newCap;
				_data = newArr;
			}
			else
			{
				for (difference_type i = static_cast<difference_type>(_size) + count; i >= start + count; --i)
					_allocator.construct(_data + i, _data[i - count]);
				for (difference_type i = start; i < count; ++i)
					_allocator.destroy(_data + i);
				for (difference_type i = start; i < count; ++i, first++)
					_allocator.construct(_data + i, *first);
				_size += count;
			}
		}

		void assign (size_type n, const value_type& val)
		{
			if (n > _capacity)
			{
				clear();
				_allocator.deallocate(_data, _capacity);
				_data =_allocator.allocate(n);
				_size = n;
				_capacity = n;
				for (size_type i = 0; i < _size; ++i)
					_allocator.construct(_data + i, val);
			}
			else
			{
				clear();
				_size = n;
				for (size_type i = 0; i < _size; ++i)
					_allocator.construct(_data + i, val);
			}

		}

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last,
					 typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			if (first > last || last < first)
				throw std::logic_error("Vector: in range insert");
			difference_type count = ft::distance(first, last);
			if (count >  static_cast<difference_type>(_size))
			{
				clear();
				_allocator.deallocate(_data, _capacity);
				try
				{
					_data = _allocator.allocate(count);
				}
				catch (std::bad_alloc &ex)
				{
					std::cout << ex.what() << std::endl;
				}
				_size = count;
				_capacity = count;
				for (size_type i = 0; i < _size; ++i, first++)
					_allocator.construct(_data + i, *first);
			}
			else
			{
				clear();
				_size = count;
				for (size_type i = 0; i < _size; ++i, first++)
					_allocator.construct(_data + i, *first);
			}
		}

		iterator erase (iterator position)
		{
			difference_type pos = ft::distance(begin(), position);
			if (position >= end() || position < begin())
				throw std::logic_error("Vector: in single erase");
			if (position == end() - 1)
			{
				pop_back();
			}
			else
			{
				_allocator.destroy(_data + pos);
				for (size_type i = static_cast<size_type>(pos); i < _size; ++i)
				{
					_allocator.construct(_data + i, _data[i + 1]);
					_allocator.destroy(_data + (i + 1));
				}
				--_size;
			}
			return (position);
		}

		iterator erase (iterator first, iterator last)
		{
			if (first > last || last < first || last >= end())
				throw std::logic_error("Vector: in range insert");
			if (first == last)
				return (first);
			difference_type count = ft::distance(first, last);
			difference_type start = ft::distance(begin(), first);
			for (difference_type i = start; i < count; ++i)
				_allocator.destroy(_data + i);
			for (difference_type i = start; i < static_cast<difference_type>(_size) - count; ++i)
				_allocator.construct(_data + i, _data[count + i]);
			_size -= count;
			return (first);
		}

		allocator_type getAllocator()
		{
			return (_allocator);
		}
	};

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size() || !ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
			return (false);
		return (true);
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (!lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
			return (false);
		return (true);
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template<class T, class Allocator>
	void swap(ft::vector<T, Allocator> &lhs, ft::vector<T, Allocator> &rhs)
	{
		lhs.swap(rhs);
	}
}
#endif