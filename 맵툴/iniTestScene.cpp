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
		//����, Ű, ���
		//[�ù�12��]
		//����=100
		//����=90
		//����=80
		//...

		INIDATA->addData("�ù�12��", "����", "100.5");
		INIDATA->addData("�ù�12��", "����", "90");
		INIDATA->addData("�ù�12��", "����", "80");

		//�����̸����� ���̺�
		INIDATA->saveINI("�ù��ù�");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		int num = INIDATA->loadDataInteger("�ù��ù�", "�ù�12��", "����");
		//float num = INIDATA->loadDataFloat("�ù��ù�", "�ù�12��", "����");
		cout << num << endl;
	}

}

void iniTestScene::render(void)
{
}
