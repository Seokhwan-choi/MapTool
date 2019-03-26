#include "stdafx.h"
#include "MapTool.h"


HRESULT MapTool::init()
{
	// x������ 64, y������ 64
	IMAGEMANAGER->addFrameImage("sample", "sample.bmp", 512, 576, 32, 36, true, RGB(81, 92, 160));
	IMAGEMANAGER->addFrameImage("cave", "cave.bmp", 2048, 2304, 32, 36, true, RGB(81, 92, 160));
	IMAGEMANAGER->addImage("�ȷ�", "�ȷ�.bmp", 538, 649, true, RGB(255, 0, 255));
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
	this->SetTile();					// Ÿ�� �����ϱ�
	this->ShowPalette();				// �ȷ� �����ֱ�
	this->KeyHandling();				// Ű �Է� ó��
	this->MouseSelect();				// ���콺 ���� ó��
	CAMERA->SetCamemra(_CameraPos);		// ���� ���� ī�޶� ����
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
// ############ ���콺 ī�޶� �̵� �Լ� ############
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
// ############ Ű���� ī�޶� �̵� �Լ� ############
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
// ############# Ű �Է� ó�� �Լ� ################
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
// ########### ���콺 Ÿ�� ���� �Լ� ###############
// ===============================================
void MapTool::MouseSelect()
{
	// Sample Ÿ�� ������ �巡�� & ���
	// ���� ��ǥ(Start), �� ��ǥ(End) ����
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
// ##############  Ÿ�� ���� �Լ� #################
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
// ############ �ȷ� �����ֱ� �Լ� ################
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
// ############ Ÿ�� �����ֱ� �Լ� ################
// ===============================================
void MapTool::ShowTile()
{
	for (int i = 0; i < YNUM; ++i) {
		for (int j = 0; j < XNUM; ++j) {
			Rectangle(getMemDC(), CAMERA->Relative(_Tile[j][i].rc));
		}
	}
	if (_Show) {
		IMAGEMANAGER->findImage("�ȷ�")->render(getMemDC()
			, _TilePalette.left, _TilePalette.top);
		IMAGEMANAGER->findImage("sample")->render(getMemDC()
			, _TilePalette.left + 10, _TilePalette.top + 35);
	}
}
// ===============================================
// ############ ����� Ȯ�ο� �Լ� ################
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
	sprintf(str, "���� ��ǥ : %d, %d, �� ��ǥ : %d, %d",
		_Start.x, _Start.y, _End.x, _End.y);
	TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y, str, strlen(str));
}
