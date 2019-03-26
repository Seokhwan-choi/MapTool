#include "stdafx.h"
#include "gameNode.h"

//=============================================================
//	## 초기화 ## init(void)
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
		KEYMANAGER->init();					//키매니져 초기화
		RND->init();						//랜덤펑션 초기화
		IMAGEMANAGER->init();				//이미지 매니져 초기화
		SAVEDATA->init();					//세이브데이터 초기화
		TXTDATA->init();					//텍스트데이터 초기화
		INIDATA->init();					//INI데이터 초기화
		SCENEMANAGER->init();				//씬매니져 초기화
		SOUNDMANAGER->init();				//사운드매니져 초기화
		TIMEMANAGER->init();				//타임매니져 초기화
	}

	return S_OK;
}

//=============================================================
//	## 해제 ## release(void)
//=============================================================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//키매니져 해제
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		//랜덤펑션 해제
		RND->release();
		RND->releaseSingleton();
		//이미지매니져 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		//세이브데이터 해제
		SAVEDATA->release();
		SAVEDATA->releaseSingleton();
		//텍스트데이터 해제
		TXTDATA->release();
		TXTDATA->releaseSingleton();
		//INI데이터 해제
		INIDATA->release();
		INIDATA->releaseSingleton();
		//씬매니져 해제
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		//사운드매니져 해제
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		//타임매니져 싱글톤 해제
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

	}
	
	//DC 해제
	ReleaseDC(_hWnd, _hdc);
}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void gameNode::update(void)
{
	//새로고침 (나중에 고성능 타이머를 만든 후에는 사용하지 않는다)
	//더블버퍼링 이후 사용하지 않는다(true => false);
	//InvalidateRect(_hWnd, NULL, FALSE);
}

//=============================================================
//	## 렌더 ## render(void)
//=============================================================
void gameNode::render(void)
{
}

//=============================================================
//	## MainProc ## 메인프로시져
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
