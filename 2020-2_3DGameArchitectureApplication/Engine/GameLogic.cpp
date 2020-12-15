#include "GameLogic.h"

#include "Time.h"


GameLogic::GameLogic()
{
	_framePerSec = 60;
	_curSec = 0.0f;

	_physicsFrame = 15;
	_physicsSec = 0.0f;

	_colliderList = new std::vector<BoxCollider*>();
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

void GameLogic::AddCollider(BoxCollider* collider)
{
	_colliderList->push_back(collider);
}


void GameLogic::InitScene()
{
	for (int i = 0; i < _updatableObjList.size(); i++)
	{
		_updatableObjList[i]->Init();
	}
}

void GameLogic::UpdateScene()
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

	if (_physicsSec < (1.0f / (float)_physicsFrame))
	{
		_physicsSec += Time::GetInstance().GetDeltaTime();
	}
	else
	{
		_physicsSec = 0.0f;

		CheckCollision();
	}
}


void GameLogic::CheckCollision()
{
	for (size_t i = 0; i < _colliderList->size(); i++)
	{
		for (size_t j = 0; j < _colliderList->size(); j++)
		{
			if (i == j)
			{
				break;
			}

			glm::vec3 base_pos = (*_colliderList)[i]->GetObjectWorldLocation();
			glm::vec3 cur_pos = (*_colliderList)[j]->GetObjectWorldLocation();

			if (cur_pos.x + (*_colliderList)[j]->GetBoxExtent().x >= base_pos.x - (*_colliderList)[i]->GetBoxExtent().x &&
				cur_pos.x - (*_colliderList)[j]->GetBoxExtent().x <= base_pos.x + (*_colliderList)[i]->GetBoxExtent().x)
			{
				if (cur_pos.y + (*_colliderList)[j]->GetBoxExtent().y >= base_pos.y - (*_colliderList)[i]->GetBoxExtent().y &&
					cur_pos.y - (*_colliderList)[j]->GetBoxExtent().y <= base_pos.y + (*_colliderList)[i]->GetBoxExtent().y)
				{
					if (cur_pos.z + (*_colliderList)[j]->GetBoxExtent().z >= base_pos.z - (*_colliderList)[i]->GetBoxExtent().z &&
						cur_pos.z - (*_colliderList)[j]->GetBoxExtent().z <= base_pos.z + (*_colliderList)[i]->GetBoxExtent().z)
					{
						(*_colliderList)[i]->ReportCollision((*_colliderList)[j]);
						(*_colliderList)[j]->ReportCollision((*_colliderList)[i]);
					}
				}
			}
		}
	}
}


void GameLogic::ReleaseMemory()
{
	_updatableObjList.clear();

	_colliderList->clear();
	delete _colliderList;
}