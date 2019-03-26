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
	tagTile _tiles[TILEX * TILEY];  //�ΰ���ȭ�� �� 400�� Ÿ��

	RECT _player;					//�÷��̾�(�Ѹ�)
	RECT _colcheck[4];				//�÷��̾�(�Ѹ�) �浹Ȯ��
	POINT _playerpt;				//�÷��̾� ��ǥ
	STATE _state;					//�÷��̾�(�Ѹ�) ����
	bool _move;						//�÷��̾� �����̳�?

	RECT _Enemy[10];				//����
	POINT _enemypt[10];				//���� ��ǥ
	STATE _enemystate[10];			//���� ����
	bool _move2[10];				//���� �����̳�?
	int _movecount[10];				//���� ī����
	

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

