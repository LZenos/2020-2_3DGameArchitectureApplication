#pragma once

#include "ICleanUp.h"
#include "IUpdatable.h"

#include <vector>


class GameLogic : public ICleanUp
{
private:
	int _framePerSec;
	float _curSec;

	std::vector<IUpdatable*> _updatableObjList;

	GameLogic();

public:
	~GameLogic();

	static GameLogic& GetInstance();

	void SetFrameRate(int new_frame_rate);

	void AddUpdatableObj(IUpdatable* obj);


	void Init();

	void Update();


	virtual void ReleaseMemory() override;
};