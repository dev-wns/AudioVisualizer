//#include "..\\Standard.hpp"
#include "MyRandom.h"

int MyRandom::GetRandomInt( int _min, int _max )
{
	std::random_device rd;
	std::mt19937_64 rnd( rd() );
	std::uniform_int_distribution<int> random( _min, _max );

	return random( rnd );
}

float MyRandom::GetRandomFloat( float _min, float _max )
{
	std::random_device rd;
	std::mt19937_64 rnd( rd() );
	std::uniform_real_distribution<float> random( _min, _max );

	return random( rnd );
}