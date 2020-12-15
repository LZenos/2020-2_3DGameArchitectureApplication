#pragma once

#include "ICleanUp.h"
#include "IUpdatable.h"
#include "Object_BoxCollider.h"

#include <vector>


class GameLogic : public ICleanUp
{
private:
	int _framePerSec;
	float _curSec;

	int _physicsFrame;
	float _physicsSec;

	std::vector<IUpdatable*> _updatableObjList;
	std::vector<BoxCollider*>* _colliderList;

	GameLogic();

public:
	static GameLogic& GetInstance();

	void SetFrameRate(int new_frame_rate);

	void AddUpdatableObj(IUpdatable* obj);

	void AddCollider(BoxCollider* collider);


	void InitScene();

	void UpdateScene();


	void CheckCollision();


	virtual void ReleaseMemory() override;
};