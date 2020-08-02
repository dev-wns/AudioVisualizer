#pragma once


template<typename TYPE>
struct Vector3 : public BaseVector<TYPE, 3>
{
	// 멤버 변수
	float x, y, z;

	// 생성자
	Vector3() : x( 0 ), y( 0 ) {}
	Vector3( const TYPE& vx, const TYPE& vy ) : x( vx ), y( vy ) {}
	Vector3( const TYPE v[] ) : x( v[0] ), y( v[1] ) {}
	Vector3( const Vector3& v ) : x( v.x ), y( v.y ) {}

	// 연산자 재정의
	Vector3 operator + () const
	{
		return *this;
	}

	Vector3 operator - () const
	{
		return Vector3( -x, -y, -z );
	}

	Vector3 operator + ( const Vector3& v ) const
	{
		return Vector3( x + v.x, y + v.y, z + v.z );
	}

	Vector3 operator - ( const Vector3& v ) const
	{
		return Vector3( x - v.x, y - v.y, z - v.z );
	}

	Vector3 operator * ( const Vector3& v ) const
	{
		return Vector3( x * v.x, y * v.y, z * v.z );
	}

	Vector3 operator * ( const TYPE& type ) const
	{
		return Vector3( x * type, y * type, z * type );
	}

	Vector3 operator / ( const Vector3& v ) const
	{
		assert( ( v[0] != 0 ) && ( v[1] != 0 ) && v[2] != 0);
		return Vector3( x / v[0], y / v[1], z / v[2] );
	}

	Vector3 operator / ( const TYPE& type ) const
	{
		assert( s != 0 );
		TYPE is = 1 / type;
		return Vector3( x * is, y * is, z * is );
	}

	Vector3& operator += ( const Vector3& v )
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector3& operator -= ( const Vector3& v )
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vector3& operator *= ( const Vector3& v )
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	Vector3& operator *= ( const TYPE& type )
	{
		x *= type;
		y *= type;
		z *= type;
		return *this;
	}

	Vector3& operator /= ( const Vector3& v )
	{
		assert( ( v[0] != 0 ) && ( v[1] != 0 ) && ( v[2] != 0 ) );
		x /= v[0];
		y /= v[1];
		z /= v[2];
		return *this;
	}

	Vector3& operator /= ( const TYPE& type )
	{
		assert( s != 0 );
		TYPE is = 1 / type;
		x *= is;
		y *= is;
		z *= is;
		return *this;
	}

	Vector3& operator = ( const Vector3& v )
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	// 함수
	TYPE Normalize()
	{
		TYPE s = x * x + y * y + z * z;
		TYPE square = sqrt( s );
		if ( ( s != 0 ) == true )
		{
			s = 1.0f / square;
			x *= s;
			y *= s;
			z *= s;
		}
		return square;
	}

	void SetVector( const TYPE& type )
	{
		x = type;
		y = type;
		z = type;
	}

	void SetVector( const TYPE& tx, const TYPE& ty, const TYPE& tz )
	{
		x = tx;
		y = ty;
		z = tz;
	}

	bool IsZero()
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	bool IsSame( const Vector3& type, const TYPE& diff )
	{
		TYPE dx = Math::Maximum( x, type.x ) - Math::Minimum( x, type.x );
		TYPE dy = Math::Maximum( y, type.y ) - Math::Minimum( y, type.y );
		TYPE dz = Math::Maximum( z, type.z ) - Math::Minimum( z, type.z );

		if ( dx > diff || dx < -diff ) return false;
		if ( dy > diff || dy < -diff ) return false;
		if ( dz > diff || dz < -diff ) return false;

		return true;
	}
};

template <typename T>
inline T LengthSquared( const Vector3<T>& v )
{
	return v.x*v.x + v.y*v.y + v.z*v.z;
}

template <typename T>
inline T Length( const Vector3<T>& v )
{
	//#1941 제곱근 커스터마이징.
	return Math::Sqrt( v.x*v.x + v.y*v.y + v.z*v.z );
}

template <typename T>
inline T DotProduct( const Vector3<T>& a, const Vector3<T>& b )
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T>
inline Vector3<T> CrossProduct( const Vector3<T>& a, const Vector3<T>& b )
{
	return Vector3<T>(
		( a.y * b.z ) - ( a.z * b.y ),
		( a.z * b.x ) - ( a.x * b.z ),
		( a.x * b.y ) - ( a.y * b.x ) );
}

template <typename T>
inline Vector3<T> Normalize( const Vector3<T>& v )
{
	T s = v.x*v.x + v.y*v.y + v.z*v.z;
	if ( s == 0 )
		return v;

	//#1941 제곱근 커스터마이징.		
	s = 1 / Math::Sqrt( s );
	return Vector3<T>( v.x * s, v.y * s, v.z * s );
}

template <typename T>
inline Vector3<T> Reflect( const Vector3<T>& v, const Vector3<T>& normal )
{
	T s = DotProduct( v, normal ) * 2;
	return Vector3<T>(
		v.x + normal.x * s,
		v.y + normal.y * s,
		v.z + normal.z * s );
}

template <typename T>
inline Vector3<T> Lerp( const Vector3<T>& a, const Vector3<T>& b, const T& time )
{
	return Vector3<T>(
		a.x + ( b.x - a.x ) * time,
		a.y + ( b.y - a.y ) * time,
		a.z + ( b.z - a.z ) * time );
}
template <typename T>
inline T GetAngle( const Vector3<T>& lhs, const Vector3<T>& rhs )
{
	T value = DotProduct( lhs, rhs ) / ( Length( lhs ) * Length( rhs ) );
	if ( value > static_cast< T >( 1 ) )
	{
		return 0;
	}
	else if ( value < static_cast< T >( -1 ) )
	{
		return pi;
	}
	else
	{
		return acos( value );
	}
}

template <typename T>
inline Vector3<T> operator * ( const T& s, const Vector3<T>& v )
{
	return Vector3<T>( s * v.x, s * v.y, s * v.z );
}

template< typename T >
inline bool CompareEquals( const Vector3< T >& lhs, const Vector3< T >& rhs, const T& precision )
{
	if ( lhs.x < rhs.x - precision ) return false;
	if ( lhs.x > rhs.x + precision ) return false;

	if ( lhs.y < rhs.y - precision ) return false;
	if ( lhs.y > rhs.y + precision ) return false;

	if ( lhs.z < rhs.z - precision ) return false;
	if ( lhs.z > rhs.z + precision ) return false;

	return true;
}

typedef Vector3<float> float3;
typedef Vector3<double> float3s64;
typedef Vector3<int> int3;
typedef Vector3<unsigned int> int3u32;
typedef Vector3<long long> int3s64;
typedef Vector3<unsigned long long> int3u64;
