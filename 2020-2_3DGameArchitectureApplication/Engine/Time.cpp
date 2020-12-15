#include "Time.h"


Time::Time()
{
	_deltaTime = 0.0f;

	LARGE_INTEGER cur_count;
	QueryPerformanceCounter(&cur_count);
	_prevCount = cur_count;

	_frameLogic = 60;
	_frameRender = 144;
}

Time::~Time()
{

}


Time& Time::GetInstance()
{
	static Time instance;

	return instance;
}


void Time::Tick()
{
	LARGE_INTEGER per_count;
	LARGE_INTEGER total_count;
	
	QueryPerformanceFrequency(&per_count);
	QueryPerformanceCounter(&total_count);
	
	_deltaTime = (float)(total_count.QuadPart - _prevCount.QuadPart) / (float)per_count.QuadPart;
	_prevCount = total_count;
}


void Time::SetFixedFrameOfLogic(int frame_per_sec)
{
	_frameLogic = frame_per_sec;
}

void Time::SetFrameLimitOfRender(int frame_per_sec)
{
	_frameRender = frame_per_sec;
}


float Time::GetDeltaTime() const
{
	return _deltaTime;
}