#pragma once
#include "gameNode.h"
#include "tileNode.h"

enum class STATE : int
{
	LEFT, RIGHT, UP, DOWN
};

class Packman : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];  //인게임화면 총 400개 타일

	RECT _player;					//플레이어(팩맨)
	RECT _colcheck[4];				//플레이어(팩맨) 충돌확인
	POINT _playerpt;				//플레이어 좌표
	STATE _state;					//플레이어(팩맨) 상태
	bool _move;						//플레이어 움직이냐?

	RECT _Enemy[10];				//몬스터
	POINT _enemypt[10];				//몬스터 좌표
	STATE _enemystate[10];			//몬스터 상태
	bool _move2[10];				//몬스터 움직이냐?
	int _movecount[10];				//몬스터 카운터
	

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void SetMap();
	void MapRender();
	void PlayerState();
	void EnemyState();

	Packman() {}
	~Packman() {}
};

