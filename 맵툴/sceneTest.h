#pragma once
#include "gameNode.h"
#include "player.h" //플레이어 클래스 사용하기 위해
#include "enemyManager.h" //적매니져 클래스 사용하기 위해

class sceneTest : public gameNode
{
private:
	player* _player;				//플레이어 클래스 선언
	enemyManager* _enemyManager;	//적매니져 클래스 선언

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	//충돌함수
	void collision();

	sceneTest() {}
	~sceneTest() {}
};

