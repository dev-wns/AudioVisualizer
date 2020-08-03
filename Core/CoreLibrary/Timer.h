#pragma once
#include "Singleton.hpp"

class Timer : public Singleton<Timer>
{
public:
	Timer();
    virtual ~Timer() = default;

public:
	float GetSPF() { return secondPerFrame; }
	DWORD GetFPS() { return framePerSecond; }
	float GetProgressTime() { return gameTimer; }

public:
	bool IsFixedFrameRate();
	const float GetFixedFrameRate() const { return fixedFrame; }
	// 원하는 프레임
	void SetFixedFrameRate( const DWORD& value );

public:
	void Init();
	void Frame();

private:
	friend class Singleton<Timer>;
	bool isFixedFrame;
	float fixedFrame;
	DWORD fixedFramePerSecond;
	float fixedFrameElapseTime;

	float secondPerFrame;
	float gameTimer;
	float frameTime;
	DWORD framePerSecond;
	LARGE_INTEGER frequency;
	LARGE_INTEGER beforeTick;
	LARGE_INTEGER currentTick;
	LONGLONG elapseTick;
};
