#include "StdAfx.hpp"
#include "Timer.h"

Timer::Timer() : 
	bFixedFrame( false ), fixedFrame( 1.0f / 10000.0f ), fixedFramePerSecond( 0 ), fixedFrameElapseTime( 0.0f ),
	secondPerFrame( 0.0f ), gameTimer( 0.0f ), frameTime( 0.0f ), framePerSecond( 0 ) { }

void Timer::Init()
{
	::QueryPerformanceFrequency( &frequency );
	::QueryPerformanceCounter( &beforeTick );
}

void Timer::Frame()
{
	::QueryPerformanceCounter( &currentTick );
	elapseTick = currentTick.QuadPart - beforeTick.QuadPart;
	secondPerFrame = static_cast< float >( elapseTick ) / static_cast< float >( frequency.QuadPart );
	gameTimer += secondPerFrame;
	frameTime += secondPerFrame;
	fixedFrameElapseTime += secondPerFrame;

	if ( frameTime > 1.0f )
	{
		// 전체 프레임
		std::string debug( "FPS : " + std::to_string( framePerSecond ) + "\n" );
		::OutputDebugStringA( debug.c_str() );
		framePerSecond = 0;
		frameTime = 0.0f;

		// 고정 프레임
		std::string debug2( "Fixed Frame Rate : " + std::to_string( fixedFramePerSecond ) + "\n" );
		::OutputDebugStringA( debug2.c_str() );
		fixedFramePerSecond = 0;
	}

	if ( fixedFrameElapseTime >= fixedFrame )
	{
		++fixedFramePerSecond;
		fixedFrameElapseTime = 0.0f;
		bFixedFrame = true;
	}
	else
	{
		bFixedFrame = false;
	}

	++framePerSecond;

	beforeTick = currentTick;
}

void Timer::SetFixedFrameRate( const DWORD& value )
{
	if ( value <= 0 ) 
		throw LogicError( __FUNCTION__" - value must be greater than zero.\n" );
	fixedFrame = 1.0f / static_cast<float>( value );
};

bool Timer::IsFixedFrameRate()
{
	return bFixedFrame;
}