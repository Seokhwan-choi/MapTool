#include "stdafx.h"
#include "gameNode.h"

//=============================================================
//	## �ʱ�ȭ ## init(void)
//=============================================================
HRESULT gameNode::init(void)
{
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		KEYMANAGER->init();					//Ű�Ŵ��� �ʱ�ȭ
		RND->init();						//������� �ʱ�ȭ
		IMAGEMANAGER->init();				//�̹��� �Ŵ��� �ʱ�ȭ
		SAVEDATA->init();					//���̺굥���� �ʱ�ȭ
		TXTDATA->init();					//�ؽ�Ʈ������ �ʱ�ȭ
		INIDATA->init();					//INI������ �ʱ�ȭ
		SCENEMANAGER->init();				//���Ŵ��� �ʱ�ȭ
		SOUNDMANAGER->init();				//����Ŵ��� �ʱ�ȭ
		TIMEMANAGER->init();				//Ÿ�ӸŴ��� �ʱ�ȭ
	}

	return S_OK;
}

//=============================================================
//	## ���� ## release(void)
//=============================================================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//Ű�Ŵ��� ����
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		//������� ����
		RND->release();
		RND->releaseSingleton();
		//�̹����Ŵ��� ����
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		//���̺굥���� ����
		SAVEDATA->release();
		SAVEDATA->releaseSingleton();
		//�ؽ�Ʈ������ ����
		TXTDATA->release();
		TXTDATA->releaseSingleton();
		//INI������ ����
		INIDATA->release();
		INIDATA->releaseSingleton();
		//���Ŵ��� ����
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		//����Ŵ��� ����
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		//Ÿ�ӸŴ��� �̱��� ����
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

	}
	
	//DC ����
	ReleaseDC(_hWnd, _hdc);
}

//=============================================================
//	## ������Ʈ ## update(void)
//=============================================================
void gameNode::update(void)
{
	//���ΰ�ħ (���߿� ���� Ÿ�̸Ӹ� ���� �Ŀ��� ������� �ʴ´�)
	//������۸� ���� ������� �ʴ´�(true => false);
	//InvalidateRect(_hWnd, NULL, FALSE);
}

//=============================================================
//	## ���� ## render(void)
//=============================================================
void gameNode::render(void)
{
}

//=============================================================
//	## MainProc ## �������ν���
//=============================================================
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:		
		switch (wParam)
		{
		case VK_ESCAPE:		
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:		
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
