#include "GameLogic.h"

#include "Time.h"


GameLogic::GameLogic()
{
	_framePerSec = 60;
	_curSec = 0.0f;
}

GameLogic::~GameLogic()
{
	_updatableObjList.clear();
}


GameLogic& GameLogic::GetInstance()
{
	static GameLogic instance;

	return instance;
}


void GameLogic::SetFrameRate(int new_frame_rate)
{
	_framePerSec = new_frame_rate;
}

void GameLogic::AddUpdatableObj(IUpdatable* obj)
{
	_updatableObjList.push_back(obj);
}

void GameLogic::Update()
{
	if (_curSec < (1.0f / (float)_framePerSec))
	{
		_curSec += Time::GetInstance().GetDeltaTime();
	}
	else
	{
		_curSec = 0.0f;

		for (int i = 0; i < _updatableObjList.size(); i++)
		{
			_updatableObjList[i]->Update();
		}
	}
}

void GameLogic::ReleaseMemory()
{
	_updatableObjList.clear();
}