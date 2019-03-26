#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�̹��� �� ���� �ε�
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//�ε�Ŭ���� ����
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	//�ε��Ϸ��� ȭ��(��)����
	if (_loading->loadingDone())
	{
		//SCENEMANAGER->loadScene("�ȼ��浹");
	}


}

void loadingScene::render(void)
{
	//�ε�Ŭ���� ����
	_loading->render();

	float num = _loading->getLoadItem().size();
	float cur = _loading->getCurrentGauge();
	float per = cur / num * 100;
	char str[128];
	sprintf(str, "%.f %%", per);
	TextOut(getMemDC(), 660, 430, str, strlen(str));


	if (_loading->getCurrentGauge() < _loading->getLoadItem().size())
	{
		char str[128];
		sprintf(str, "%s.bmp", _loading->getLoadItem()[_loading->getCurrentGauge()]->getImageResource().keyName.c_str());
		TextOut(getMemDC(), 120, 430, str, strlen(str));
	}
}

void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();
	//_loading->loadSound();
	//IMAGEMANAGER->addImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	_loading->loadImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("ball", "ball.bmp", 60, 60, true, RGB(255, 0, 255));
	//�ε��� �ʹ� ������ ����Ǽ� õõ�� ���ư����� �׽�Ʈ������ �����
	for (int i = 0; i < 500; i++)
	{
		char str[128];
		sprintf(str, "Image/TestImage_%d", i + 1);

		_loading->loadImage(str, WINSIZEX, WINSIZEY);
	}

	//winapi/image/test_0.bmp
	//winapi/image/test_1.bmp
	//winapi/image/test_2.bmp
	//...


}

void loadingScene::loadingSound()
{
}
