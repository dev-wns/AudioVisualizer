#pragma once
#include "Singleton.hpp"
#include <random>

class MyRandom : public Singleton<MyRandom>
{
public:
	MyRandom() {} // : rnd( rd() ) { }
	virtual ~MyRandom() = default;

	int GetRandomInt( int _min, int _max );
	float GetRandomFloat( float _min, float _max );
};

