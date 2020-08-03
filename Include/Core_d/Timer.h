#pragma once
#include "Singleton.hpp"


class Timer : public Singleton<Timer>
{
private:		 Timer() = default;
public: virtual ~Timer() = default;

public:
	static float SPF() { return secondPerFrame; }
	static DWORD FPS() { return framePerSecond; }
	static float GameTimer() { return gameTimer; }

public:
	void Init();
	void Frame();

private:
	friend class Singleton<Timer>;
	static float secondPerFrame;
	static float gameTimer;
	static DWORD framePerSecond;
	float frameTime;
	LARGE_INTEGER frequency;
	LARGE_INTEGER beforeTick;
	LARGE_INTEGER currentTick;
	LONGLONG elapseTick;
};