#pragma once
#include "gameNode.h"

class pixelCollisionScene : public gameNode
{
private:
	image* _mountain;		//��׶��� �̹���
	image* _ball;			//���̹���
	RECT _rc;				//�� ��Ʈ

	float _x, _y;			//��ġ��ǥ
	int _probeY;			//�ȼ��浹 Ž���� Y��

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	pixelCollisionScene() {}
	~pixelCollisionScene() {}
};

