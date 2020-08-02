#include "StdAfx.hpp"
#include "Timer.h"

float Timer::secondPerFrame = 0.0f;
float Timer::gameTimer = 0.0f;
DWORD Timer::framePerSecond = 0;

void Timer::Init()
{
	QueryPerformanceFrequency( &frequency );
	QueryPerformanceCounter( &beforeTick );
}

void Timer::Frame()
{
	QueryPerformanceCounter( &currentTick );
	elapseTick = currentTick.QuadPart - beforeTick.QuadPart;
	secondPerFrame = ( float )elapseTick / ( float )frequency.QuadPart;
	gameTimer += secondPerFrame;
	frameTime += secondPerFrame;

	static DWORD fixedFrameRate( 0 );
	static float elapseTime( 0.0f );
	elapseTime += secondPerFrame;

	if ( frameTime > 1.0f )
	{
		// 전체 프레임
		std::string debug( "FPS : " + std::to_string( framePerSecond ) + "\n" );
		OutputDebugStringA( debug.c_str() );
		framePerSecond = 0;
		frameTime = 0.0f;

		// 고정 프레임
		std::string debug2( "Fixed Frame Rate : " + std::to_string( fixedFrameRate ) + "\n" );
		OutputDebugStringA( debug2.c_str() );
		fixedFrameRate = 0;
	}

	const static float fixedFrame( 1.0f / 240.f );
	if ( elapseTime >= fixedFrame )
	{
		++fixedFrameRate;
		elapseTime = 0.0f;
		isSetFrame = true;
	}
	else
	{
		isSetFrame = false;
	}

	++framePerSecond;

	beforeTick = currentTick;
}

bool Timer::IsFixedFrameRate()
{
	return isSetFrame;
}