#include <memory>
#include <vector>


namespace ft {
	template <class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		typedef	std::size_t													size_type;
		std::ptrdiff_t														difference_type;
		typedef typename std::allocator_traits<Allocator>::const_pointer	const_pointer;
		typedef typename std::allocator_traits<Allocator>::pointer			pointer;
		typedef Allocator													allocator_type;
		typedef T															value_type;
		typedef	value_type&													reference;
		typedef const value_type& 											const_reference;
		//typedef typename std::vector<value_type>::iterator					iterator;
		//typedef typename std::vector<const value_type>::const_iterator		const_iterator;
		//typedef std::reverse_iterator<iterator>								reverse_iterator;
		//typedef std::reverse_iterator<const_iterator>						const_reverse_iterator;
	
	private:
		size_type															_size;
		size_type															_capacity;
		pointer																_first;
		allocator_type														_allocator;

		//contructors
	public:
		explicit vector(const allocator_type& allocator = allocator_type()) 
			:	_size(0),
				_capasity(0),
				_first(0),
				_allocator(allocator)
		{};

		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& allocator = allocator_type())
			:	_size(n),
				_capacity(n),
				_allocator(allocator)
		{
			_first = _allocator.allocate(n)
				for (int i = 0; i < n; ++i)
					_allocator.construct(_first + i, val);
		}


		

	};
}
