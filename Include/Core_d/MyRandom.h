#pragma once
#include "Singleton.hpp"
#include <random>

class MyRandom : public Singleton<MyRandom>
{
public:
	MyRandom() {} // : rnd( rd() ) { }
	virtual ~MyRandom() = default;

	int GetRandomInt( int _min, int _max )
	{
		std::random_device rd;
		std::mt19937_64 rnd( rd() );
		std::uniform_int_distribution<int> random( _min, _max );

		return random( rnd );
	}

	float GetRandomFloat( float _min, float _max )
	{
		std::random_device rd;
		std::mt19937_64 rnd( rd() );
		std::uniform_real_distribution<float> random( _min, _max );

		return random( rnd );
	}

private:
};

