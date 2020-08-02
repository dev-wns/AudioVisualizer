#pragma once
#include "Window.h"
#include "Timer.h"
#include "Input.h"

class Core : public Window
{
public:
	Core() = default;
	virtual ~Core() = default;

public:
	virtual void Init() {}
	virtual void Frame() {}
	virtual void Render() {}
	virtual void Release() {}
public:
	void GameInit() override;
	void GameFrame() override;
	void GameRender() override;
	void GameRelease() override;
	//void ResizeClient( UINT width, UINT height ) override;

	float time;
};