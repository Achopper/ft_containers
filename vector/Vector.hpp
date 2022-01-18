#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <vector>
#include <iostream>



namespace ft {
	template <class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		typedef	std::size_t													size_type;
		typedef std::ptrdiff_t												difference_type;
		typedef typename std::allocator_traits<Allocator>::const_pointer	const_pointer;
		typedef typename std::allocator_traits<Allocator>::pointer			pointer;
		typedef Allocator													allocator_type;
		typedef T															value_type;
		typedef	value_type&													reference;
		typedef const value_type& 											const_reference;
		typedef typename std::vector<value_type>::iterator					iterator;
		typedef typename std::vector<value_type>::const_iterator			const_iterator;
		typedef std::reverse_iterator<iterator>								reverse_iterator;
		typedef std::reverse_iterator<const_iterator>						const_reverse_iterator;

	private:
		size_type															_size;
		size_type															_capacity;
		pointer																_data;
		allocator_type														_allocator;

		//CONSTRUCTORS--------------------------------------------------------------------------------------------------
	public:
		explicit vector(const allocator_type& allocator = allocator_type())
			: _size(0),
			  _capacity(0),
			  _data(0),
			  _allocator(allocator)
		{};


		explicit vector(size_type n, const value_type& val = value_type(),
						const allocator_type& allocator = allocator_type())
			:	_size(n),
				_capacity(n),
				_allocator(allocator)
		{
			try
			{
				_data = _allocator.allocate(n);
			} catch (std::bad_alloc &ex)
			{
				std::cout << ex.what();
			}
			for (size_type i = 0; i < n; ++i)
				_allocator.construct(_data + i, val);
		}

//		template <class InputIterator>
//		vector (InputIterator first, InputIterator last,
//				const allocator_type& alloc = allocator_type()) : _allocator(alloc)
//		{
//				SFINAE
//		}

		vector(const vector& obj)
		{
			*this = obj;
		}
		//DESTRUCTOR----------------------------------------------------------------------------------------------------
		~vector()
		{
			for (size_type i = 0; i <= _size; ++i)
				_allocator.destroy(_data + i);
			if (_capacity)
				_allocator.deallocate(_data, _capacity);
		}
		//OPERATORS-----------------------------------------------------------------------------------------------------
		vector & operator=(const vector& obj)
		{
			if (this == &obj)
				return (*this);
			for (size_type i = 0; i < _size; ++i)
				_allocator.destroy(_data + i);
			_size = obj._size;
			if (_capacity != 0)
			{
				_allocator.deallocate(_data, _capacity);
				try
				{
					_data = _allocator.allocate(obj._capacity);
				} catch (std::bad_alloc &ex)
				{
					std::cout << ex.what();
				}
			}
			_capacity = _size;
			for (size_type i = 0; i < _size; ++i)
				_allocator.construct(_data + i, obj._data[i]);
			return (*this);
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

		void resize (size_type n, value_type val = value_type())
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
						reserve(_capacity * 2 > n ? _capacity * 2 : n);
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

		//MODIFIERS-----------------------------------------------------------------------------------------------------

		void push_back (const value_type& val)
		{
			if (_size >= _capacity)
			{
				try
				{
					reserve(_capacity < 1 ? ++_capacity * 2 : _capacity * 2);
				} catch (std::exception &ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			_allocator.construct(_data + _size, val);
			_size++;
		}

		void swap(vector& obj)
		{
			std::swap(_allocator, obj._allocator);
			std::swap(_capacity, obj._capacity);
			std::swap(_size, obj._size);
			std::swap(_data, obj._data);
		}

		pointer testPrint(size_type idx) const
		{
			if (idx > _size)
				return NULL;
			return &_data[idx];
		}
	};
}


template<class T, class Allocator>
void swap(ft::vector<T, Allocator> &lhs, ft::vector<T, Allocator> &rhs)
{
	lhs.swap(rhs);
}


#endif