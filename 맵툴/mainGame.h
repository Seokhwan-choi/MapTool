#pragma once
#include "gameNode.h"
/*�����δ� ������ ������ ������ϸ� ���ΰ��ӿ� �߰��صд�*/
#include "sceneTest.h"
#include "pixelCollisionScene.h"
#include "iniTestScene.h"
#include "loadingScene.h"
#include "soundTestScene.h"
#include "maptoolScene.h"
#include "Packman.h"
#include "MapTool.h"

class mainGame : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mainGame() {}
	~mainGame() {}
};

