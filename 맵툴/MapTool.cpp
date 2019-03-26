#include "stdafx.h"
#include "MapTool.h"


HRESULT MapTool::init()
{
	// x사이즈 64, y사이즈 64
	IMAGEMANAGER->addFrameImage("sample", "sample.bmp", 512, 576, 32, 36, true, RGB(81, 92, 160));
	IMAGEMANAGER->addFrameImage("cave", "cave.bmp", 2048, 2304, 32, 36, true, RGB(81, 92, 160));
	IMAGEMANAGER->addImage("팔렛", "팔렛.bmp", 538, 649, true, RGB(255, 0, 255));
	_CameraPos = { WINSIZEX / 2 ,WINSIZEY / 2 };

	_Hold = false;
	_Show = false;
	_DeBug = false;
	_Drag = false;
	_Start = _End = { 0, 0 };

	_TilePalette = RectMake(WINSIZEX, 300, 538, 649);
	return S_OK;
}

void MapTool::update()
{
	this->SetTile();					// 타일 셋팅하기
	this->ShowPalette();				// 팔렛 보여주기
	this->KeyHandling();				// 키 입력 처리
	this->MouseSelect();				// 마우스 선택 처리
	CAMERA->SetCamemra(_CameraPos);		// 자유 시점 카메라 셋팅
}

void MapTool::render()
{
	this->ShowTile();
	this->DeBug();
}

void MapTool::release()
{
}

// ===============================================
// ############ 마우스 카메라 이동 함수 ############
// ===============================================
void MapTool::MouseMoveCamera()
{
	if (_ptMouse.x < 450 && _ptMouse.y < 450)
	{
		_CameraPos.x -= SPEED;
		_CameraPos.y -= SPEED;
	}

	if (_ptMouse.x > WINSIZEX - 450 && _ptMouse.y < 450)
	{
		_CameraPos.x += SPEED;
		_CameraPos.y -= SPEED;
	}

	if (_ptMouse.x < 450 && _ptMouse.y  > WINSIZEY - 450)
	{
		_CameraPos.x -= SPEED;
		_CameraPos.y += SPEED;
	}

	if (_ptMouse.x > WINSIZEX - 450 && _ptMouse.y > WINSIZEY - 450)
	{
		_CameraPos.x += SPEED;
		_CameraPos.y += SPEED;
	}
}

// ===============================================
// ############ 키보드 카메라 이동 함수 ############
// ===============================================
void MapTool::KeyBoardMoveCamera()
{

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && CAMERA->GetCamemra().left > 0) 
	{
		_CameraPos.x -= SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && CAMERA->GetCamemra().right < 2048)
	{
		_CameraPos.x += SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && CAMERA->GetCamemra().top > 0 )
	{
		_CameraPos.y -= SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && CAMERA->GetCamemra().bottom < 2304)
	{
		_CameraPos.y += SPEED;
	}
}

// ===============================================
// ############# 키 입력 처리 함수 ################
// ===============================================
void MapTool::KeyHandling()
{
	if (!_Hold)
	{
		//this->MouseMoveCamera();
		this->KeyBoardMoveCamera();
	}

	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		_Hold = !_Hold;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_Show = !_Show;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) 
	{
		_DeBug = !_DeBug;
	}
}

// ===============================================
// ########### 마우스 타일 선택 함수 ###############
// ===============================================
void MapTool::MouseSelect()
{
	// Sample 타일 위에서 드래그 & 드롭
	// 시작 좌표(Start), 끝 좌표(End) 결정
	for (int i = 0; i < SAMPLENUMY; ++i) {
		for (int j = 0; j < SAMPLENUMX; ++j) {
			if (PtInRect(&_Sample[j][i].rc, _ptMouse) && _Show) 
			{
				if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && !_Drag)
				{
					_Start = _ptMouse;
					_Drag = true;
				}

				if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
				{
					_End = _ptMouse;
					_Drag = false;
				}
			}
		}
	}
}

// ===============================================
// ##############  타일 셋팅 함수 #################
// ===============================================
void MapTool::SetTile()
{
	for (int i = 0; i < YNUM; ++i)
	{
		for (int j = 0; j < XNUM; ++j)
		{
			_Tile[j][i].rc = RectMake(j * SIZE, i * SIZE, SIZE, SIZE);
		}
	}

	for (int i = 0; i < SAMPLENUMY; ++i) {
		for (int j = 0; j < SAMPLENUMX; ++j) {
			_Sample[j][i].rc = RectMake((WINSIZEX - 538) + j * SAMPLESIZE, 300 + i * SAMPLESIZE, SAMPLESIZE, SAMPLESIZE);
		}
	}
}

// ===============================================
// ############ 팔렛 보여주기 함수 ################
// ===============================================
void MapTool::ShowPalette()
{
	if (_Show && _TilePalette.left > WINSIZEX - 538)
	{
		_TilePalette.left -= 35;
		_TilePalette.right -= 35;
		if (_TilePalette.left < WINSIZEX - 538)
		{
			_TilePalette.left = WINSIZEX - 538;
			_TilePalette.right = WINSIZEX;
		}
	}
	if (!_Show)
	{
		_TilePalette.left += 35;
		_TilePalette.right += 35;
		if (_TilePalette.left > WINSIZEX)
		{
			_TilePalette.left = WINSIZEX;
			_TilePalette.right = WINSIZEX + 538;
		}
	}
}

// ===============================================
// ############ 타일 보여주기 함수 ################
// ===============================================
void MapTool::ShowTile()
{
	for (int i = 0; i < YNUM; ++i) {
		for (int j = 0; j < XNUM; ++j) {
			Rectangle(getMemDC(), CAMERA->Relative(_Tile[j][i].rc));
		}
	}
	if (_Show) {
		IMAGEMANAGER->findImage("팔렛")->render(getMemDC()
			, _TilePalette.left, _TilePalette.top);
		IMAGEMANAGER->findImage("sample")->render(getMemDC()
			, _TilePalette.left + 10, _TilePalette.top + 35);
	}
}
// ===============================================
// ############ 디버그 확인용 함수 ################
// ===============================================
void MapTool::DeBug()
{
	if (_DeBug)
	{
		Rectangle(getMemDC(), _TilePalette);
		for (int i = 0; i < SAMPLENUMY; ++i) {
			for (int j = 0; j < SAMPLENUMX; ++j) {
				Rectangle(getMemDC(), _Sample[j][i].rc);
			}
		}
	}

	char str[256];
	sprintf(str, "시작 좌표 : %d, %d, 끝 좌표 : %d, %d",
		_Start.x, _Start.y, _End.x, _End.y);
	TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y, str, strlen(str));
}
