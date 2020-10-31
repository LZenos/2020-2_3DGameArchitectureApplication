#pragma once

#include <Windows.h>


class Time
{
private:
	float _deltaTime;
	LARGE_INTEGER _prevCount;

	int _frameLogic;
	int _frameRender;
	
	Time();

public:
	~Time();

	static Time& GetInstance();

	void Tick();

	void SetFixedFrameOfLogic(int frame_per_sec);
	void SetFrameLimitOfRender(int frame_per_sec);

	float GetDeltaTime() const;
};