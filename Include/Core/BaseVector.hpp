#pragma once
#include <assert.h>
#include <math.h>

template < typename TYPE, int SIZE >
struct BaseVector
{
	const TYPE& operator [] ( int index )
	{
		assert( num >= 0 && num < SIZE );
		return reinterpret_cast< const TYPE* >( this )[index];
	}

	TYPE& operator [] ( int index )
	{
		assert( index >= 0 && index < SIZE );
		return reinterpret_cast< TYPE* >( this )[index];
	}

	bool operator == ( const BaseVector<TYPE, SIZE>& v )
	{
		for ( int count = 0; count < SIZE; ++count )
		{
			if ( v[count] != ( *this )[count] )
			{
				return false;
			}
		}
		return true;
	}

	bool operator != ( const BaseVector<TYPE, SIZE>& v )
	{
		for ( int count = 0; count < SIZE; ++i )
		{
			if ( v[count] != ( *this )[count] )
			{
				return true;
			}
		}
		return false;
	}
};