#include <memory>
#include <vector>

namespace ft {
	template <class T, class Allocator = std::allocator<T>>
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
		pointer																_arr;
		allocator_type														_allocator;

		//contructors
	public:
		explicit vector(const allocator_type& allocator = allocator_type())
			: _size(0),
			  _capacity(0),
			  _arr(0),
			  _allocator(allocator)
		{};

		explicit vector(size_type n, const value_type& val = value_type(),
						const allocator_type& allocator = allocator_type())
			:	_size(n),
				_capacity(n),
				_allocator(allocator)
		{
			_arr = _allocator.allocate(n);
			for (int i = 0; i < n; ++i)
				_allocator.construct(_arr + i, val);
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

		~vector()
		{
			for (int i = 0; i < _size; ++i)
				_allocator.destroy(_arr + i);
			_allocator.deallocate(_arr, _capacity);
		}

		vector & operator=(const vector& obj)
		{
			if (this == &obj)
				return (*this);
			for (int i = 0; i < _size; ++i)
				_allocator.destroy(_arr + i);
			_size = obj._size;
			if (_capacity != 0)
			{
				_allocator.deallocate(_arr, _capacity);
				_arr = _allocator.allocate(obj._capacity);
			}
			_capacity = _size;
			for (int i = 0; i < _size; ++i)
				_allocator.construct(_arr + i, obj._arr[i]);
			return (*this);
		}

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
	};
}
