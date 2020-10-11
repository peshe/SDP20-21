#pragma once

#include <exception>
#include <initializer_list>

#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))

namespace dsa{
template <typename T>
class dynamic_array
{
public:
	dynamic_array();
	dynamic_array( size_t capacity );
	dynamic_array( size_t capacity, const T& value );
	dynamic_array( std::initializer_list<T> ilist );
	dynamic_array( const dynamic_array<T>& other ); // copy constructor
	//dynamic_array& operator=( const dynamic_array<T>& other );
	dynamic_array& operator=( dynamic_array<T> other ); // copy and swap operator= // https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
	~dynamic_array();

public:
	class iterator
	{
	public:
		typedef iterator                  self_type;
		typedef T                         value_type;
		typedef T&                        reference;
		typedef T*                        pointer;
		typedef int                       difference_type;

		iterator( T* ptr = nullptr ) : m_ptr( ptr ), parent_container( nullptr ) {}
		iterator( dynamic_array<T>* parent, T* ptr = nullptr ): parent_container( parent ), m_ptr( ptr ) {}
		iterator& operator=( const iterator& other )
		{
			if ( this != &other )
			{
				m_ptr = other.m_ptr;
				parent_container = other.parent_container;
			}
			return *this;
		}
	public:
		/* access operators */
		reference operator*() { return *m_ptr; }
		pointer operator->() { return m_ptr; }
		reference operator[](size_t i) { return  *(m_ptr + i); }

		/* compare operators */
		bool operator==(const self_type& rhs) const { return m_ptr == rhs.m_ptr; }
		bool operator!=(const self_type& rhs) const { return !(rhs == *this); }
		bool operator<(const self_type& rhs) const { return m_ptr < rhs.m_ptr; } // compare the addresses
		bool operator>(const self_type& rhs) const { return (rhs < *this); }
		bool operator<=(const self_type& rhs) const { return !(*this > rhs); }
		bool operator>=(const self_type& rhs) const { return !(*this < rhs); }

		/* modifier operators */
		self_type& operator++() { // prefix ++

			++m_ptr;
			return *this;
		}

		self_type operator++(int) { // postfix ++

			self_type res(*this);
			++(*this);
			return res;
		}

		self_type& operator--() { // prefix --

			--m_ptr;
			return *this;
		}

		self_type operator--( int ) { //postfix --

			self_type res(*this);
			--(*this);
			return res;
		}

		void Verify_offset( const difference_type& offset ) const
		{
			assertm(offset == 0 || m_ptr, "cannot offset to be 0");
			if (offset < 0) {
				assertm( offset >= parent_container->begin().m_ptr - m_ptr, "cannot seek vector iterator before begin");
			}

			if (offset > 0) {
				assertm( offset <= parent_container->end().m_ptr - m_ptr, "cannot seek vector iterator after end");
			}
		}

		self_type& operator+=( difference_type offset ) {

			Verify_offset(offset);
			m_ptr += offset;
			return *this;
		}

		self_type operator+( difference_type offset ) const {

			self_type res(*this);
			return res += offset;
		}

		self_type& operator-=( difference_type offset ) {

			return *this+=(-offset);
		}

		self_type operator-( difference_type offset ) const {

			self_type res(*this);
			return res -= offset;
		}

		/// calculates difference between two iterators
		difference_type operator-(const self_type& rhs) const {
			return m_ptr - rhs.m_ptr;
		}

	private:
		T* m_ptr;
		dynamic_array<T>* parent_container;
	};


public:
	/** Get iterator to the beginning of the array */
	iterator begin() { return iterator( this, m_data ); }
	//const iterator cbegin() { return iterator ( this, m_data ); } // this should be using const_iterator, it's not so simple :(

	/** Get iterator to the end of the array */
	iterator end() { return iterator( this, m_data + m_size ); }
	//const iterator cend() { return iterator ( this, m_data + m_size ); } // // this should be using const_iterator, it's not so simple :(

public: // Element access
	T& at( size_t pos );
	const T& at( size_t pos ) const;
	
	T& operator[]( size_t pos );
	const T& operator[]( size_t pos ) const;


	T& front()
	{
		if ( this->empty() )
		{
			throw std::logic_error( "No elements in the array" );
		}
		return m_data[ 0 ];
	}
	const T& front() const
	{
		if ( this->empty() )
		{
			throw std::logic_error( "No elements in the array" );
		}
		return m_data[ 0 ];
	}

	T& back()
	{
		if ( this->empty() )
		{
			throw std::logic_error( "No elements in the array" );
		}
		return m_data[ m_size - 1 ];
	}
	const T& back() const
	{
		if ( this->empty() )
		{
			throw std::logic_error( "No elements in the array" );
		}
		return m_data[ m_size - 1 ];
	}

	T* data() // since C++ 11 in std::vector
	{
		return m_data;
	}
	const T* data() const
	{
		return m_data;
	}

public: // Capacity

	bool empty() const
	{
		return m_size == 0;
	}

	size_t size() const
	{
		return m_size;
	}

	size_t capacity() const
	{
		return m_capacity;
	}

	void shrink_to_fit();

public: // Modifiers

	void clear();

	iterator insert( const iterator& pos, const T& value );

	iterator erase( const iterator& pos, bool keepOrder = true );
	iterator erase( const iterator& first, const iterator& last );

	iterator find( const T& element ) const;

	void push_back( const T& value );
	void pop_back();

	void resize( size_t new_cap );

	void swap_with( dynamic_array<T>& other );

public:
	void printInfo( std::ostream& os ) const;
	void printElements( std::ostream& os ) const;

private:
	void copy_from( const dynamic_array<T>& rhs );

private:
	T* m_data;
	size_t m_size;
	size_t m_capacity;
	iterator m_it;
};

template<typename T>
inline dynamic_array<T>::dynamic_array()
	: m_data( nullptr ), m_size( 0 ), m_capacity( 0 ), m_it( this )
{
}

template<typename T>
inline dynamic_array<T>::dynamic_array( size_t capacity )
	: m_data( new T[ capacity ] ), m_size( 0 ), m_capacity( capacity ), m_it( this ) // throw bad_alloc
{
}

template<typename T>
inline dynamic_array<T>::dynamic_array( size_t capacity, const T& value )
	: m_data( new T[ capacity ] ), m_size( capacity ), m_capacity( capacity ), m_it( this ) // throw bad_alloc
{
	for ( size_t i = 0; i < capacity; ++i )
		m_data[ i ] = value;
}

template<typename T>
inline dynamic_array<T>::dynamic_array( std::initializer_list<T> ilist )	// this is initializer list
	: dynamic_array( ilist.size() )											// this is initialization list
{
	for ( const T& el: ilist )
		m_data[ m_size++ ] = el;	// T::operator= can fail to copy data and throw exception, 
							// so we need to count readed elements if we want our array to be initialize with the first readed elements
}

template<typename T>
inline dynamic_array<T>::dynamic_array( const dynamic_array<T>& other )
{
	this->copy_from( other );
}

//template<typename T>
//inline dynamic_array<T>& dynamic_array<T>::operator=( const dynamic_array<T>& other )
//{
//	if ( this != &other )
//	{
//		this->clear();
//		this->copy_from( other );
//	}
//	return *this;
//}

template<typename T>
inline dynamic_array<T>& dynamic_array<T>::operator=( dynamic_array<T> other )
{
	this->swap_with( other );

	return *this;
}

template<typename T>
inline dynamic_array<T>::~dynamic_array()
{
	this->clear();
}



template<typename T>
inline T& dynamic_array<T>::at( size_t pos )
{
	if ( pos >= m_capacity )
	{
		throw std::out_of_range( "Invalid index" );
	}
	return m_data[ pos ];
}

template<typename T>
inline const T& dynamic_array<T>::at( size_t pos ) const
{
	if ( pos >= m_capacity )
	{
		throw std::out_of_range( "Invalid index" );
	}
	return m_data[ pos ];
}

template<typename T>
inline T& dynamic_array<T>::operator[]( size_t pos )
{
	return this->at( pos );
}

template<typename T>
inline const T& dynamic_array<T>::operator[]( size_t pos ) const
{
	return this->at( pos );
}

template<typename T>
inline void dynamic_array<T>::shrink_to_fit()
{
	T* new_data = new T[ m_size ];

	for ( size_t i = 0; i < m_size; ++i )
	{
		new_data[ i ] = m_data[ i ];
	}

	delete[] m_data;
	m_data = new_data;
	m_capacity = m_size;
}

template<typename T>
inline void dynamic_array<T>::clear()
{
	if ( m_data )
	{
		delete[] m_data;
		m_data = nullptr;
		m_size = 0;
		m_capacity = 0;
	}
}

template<typename T>
typename dynamic_array<T>::iterator dynamic_array<T>::insert( const iterator& pos, const T& value )
{
	this->push_back( value ); // if has not enough memory this method should take care

	size_t index = pos - m_data;
	for ( size_t i = m_size - 1; i > index; --i )
		std::swap( m_data[ i ], m_data[ i - 1 ] );

	return iterator( this, m_data + index );
}

template<typename T>
typename dynamic_array<T>::iterator dynamic_array<T>::erase( const iterator& pos, bool keepOrder )
{
	if ( pos >= end() || m_size == 1 )
	{
		this->pop_back();
		return iterator( this, m_data + m_size - 1 );
	}

	size_t index = pos - iterator( this, m_data );
	if ( keepOrder )
	{
		for ( size_t i = index; i < m_size - 1; i++ )
			m_data[ i ] = m_data[ i + 1 ];

		this->pop_back();
		return iterator( this, m_data + index );
	}
	else
	{
		std::swap( m_data[ m_size - 1 ], m_data[ index ] );
		this->pop_back();
		return iterator( this, m_data + index );
	}
}

template<typename T>
typename dynamic_array<T>::iterator dynamic_array<T>::erase( const iterator& first, const iterator& last )
{
	if ( m_size == 0 || first >= end() || last >= end() || last < first )
	{
		return iterator();
	}
	iterator result;
	result = last;

	typename iterator::difference_type diff = (last - first);
	for ( iterator iter = first; iter != last; ++iter )
		*iter = *( iter + diff );

	m_size -= diff;
	return result;
}

template<typename T>
inline typename dynamic_array<T>::iterator dynamic_array<T>::find( const T& element ) const
{
	for ( size_t index = 0; index < m_size; ++index )
	{
		if ( m_data[ index ] == element )
		{
			return iterator( this, m_data + index );
		}
	}
}

template<typename T>
inline void dynamic_array<T>::push_back( const T& value )
{
	// is a reallocation needed
	if ( m_size >= m_capacity )
	{
		size_t new_cap = ( m_capacity == 0 ? 2 : m_capacity * 2 );
		this->resize( new_cap );
	}

	m_data[ m_size++ ] = value;
}

template<typename T>
inline void dynamic_array<T>::pop_back()
{
	if ( m_size )
		m_size--;
	else
		throw std::logic_error( "already empty dynamic array" );

	// optional, downsizing sometimes only slows down 
	if ( m_size * 2 <= m_capacity )
	{
		size_t new_cap = ( ( m_size == 0 ) ? 0 : m_capacity / 2 );
		this->resize( new_cap );
	}
}

template<typename T>
inline void dynamic_array<T>::resize( size_t new_cap )
{
	T* temp = new T[new_cap];

	size_t minSize = std::min( new_cap, m_size );
	for (size_t i = 0; i < minSize; i++)
		temp[i] = m_data[i];

	delete[] m_data;
	m_data = temp;

	m_capacity = new_cap;

}

template<typename T>
inline void dynamic_array<T>::swap_with( dynamic_array<T>& other )
{
	std::swap( m_data, other.m_data );
	std::swap( m_size, other.m_size );
	std::swap( m_capacity, other.m_capacity );
}

template<typename T>
inline void dynamic_array<T>::printInfo( std::ostream& os ) const
{
	os  <<	"Obj at : 0x" << this <<
			"\nBuffer on address 0x" << m_data <<
			"\nSize: " << m_size <<
			"\nCapacity: " << m_capacity <<
			"\nParent container on address 0x" << &m_it << std::endl;
}

template<typename T>
inline void dynamic_array<T>::printElements( std::ostream& os ) const
{
	if ( m_size == 0 )
	{
		os << "[]" << std::endl;
		return;
	}

	if ( m_size == 1 )
	{
		os << '[' << m_data[ 0 ] << ']' << std::endl;
		return;
	}

	os << "[ ";
	for ( size_t i = 0; i < m_size - 1; i++ )
		os << m_data[ i ] << ", ";
	os << m_data[ m_size - 1 ] << " ]" << std::endl;
}

template<typename T>
inline void dynamic_array<T>::copy_from( const dynamic_array<T>& other )
{
	m_data = new T[ other.m_capacity ];
	for ( size_t i = 0; i < other.m_size; ++i )
	{
		m_data[ i ] = other.m_data[ i ];
	}
	m_it = other.m_it;
	m_size = other.m_size;
	m_capacity = other.m_capacity;
}

}