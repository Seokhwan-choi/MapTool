#include "stdafx.h"
#include "iniTestScene.h"

HRESULT iniTestScene::init(void)
{
	return S_OK;
}

void iniTestScene::release(void)
{
}

void iniTestScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//섹션, 키, 밸류
		//[플밍12기]
		//동현=100
		//우현=90
		//지연=80
		//...

		INIDATA->addData("플밍12기", "동현", "100.5");
		INIDATA->addData("플밍12기", "우현", "90");
		INIDATA->addData("플밍12기", "지연", "80");

		//파일이름으로 세이브
		INIDATA->saveINI("플밍플밍");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		int num = INIDATA->loadDataInteger("플밍플밍", "플밍12기", "동현");
		//float num = INIDATA->loadDataFloat("플밍플밍", "플밍12기", "동현");
		cout << num << endl;
	}

}

void iniTestScene::render(void)
{
}
