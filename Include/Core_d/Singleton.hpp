#pragma once

template< class Type > class Singleton
{
public:
	Singleton() = default;
	virtual ~Singleton() = default;

public:
	static Type* Get()
	{
		if ( instance == nullptr )
		{
			instance = new Type();
		}

		return instance;
	}

private:
	static Type* instance;
};

template<class Type> Type* Singleton<Type>::instance = nullptr;