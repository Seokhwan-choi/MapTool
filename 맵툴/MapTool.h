#pragma once
#include "gameNode.h"

#define SPEED 8

#define SIZE 64
#define XNUM 50 
#define YNUM 50

#define SAMPLESIZE 16
#define SAMPLENUMX 32
#define SAMPLENUMY 36


struct TagTile 
{
	RECT rc;				// Ÿ�� RECT
	int framex;				// Ÿ�� ������ X			
	int framey;				// Ÿ�� ������ Y
	bool show;				
};

class MapTool : public gameNode
{
private:
	POINT _CameraPos;							// ī�޶� ���� ��ǥ
	bool _Hold;									// ī�޶� ����
	TagTile _Tile[XNUM][YNUM];					// Ÿ�� 
	TagTile _Sample[SAMPLENUMX][SAMPLENUMY];	// Sample Tile

	RECT _TilePalette;							// Ÿ�� Palette�� RECT
	bool _Show;									// Ÿ�� ���� ������

	bool _Drag;									// �巡�� & ��� ����
	RECT _MouseRect;							// �巡�� & ��� RECT
	POINT _Start;								// �巡�� & ��� ���� ��ǥ
	POINT _End;									// �巡�� & ��� �� ��ǥ





	bool _DeBug;								// Ȯ�ο� 
	
public:

	HRESULT init();
	void update();
	void render();
	void release();

	void MouseMoveCamera();						// ���콺 ī�޶� �̵� �Լ� 
	void KeyBoardMoveCamera();					// Ű���� ī�޶� �̵� �Լ�
	void KeyHandling();							// Ű �Է� ó��
	void MouseSelect();							// ���콺 �巡�� ����
	void SetTile();								// Ÿ�� �����ϱ�
	void ShowPalette();							// �ȷ� �����ֱ�
	void ShowTile();							// Ÿ�� �����ֱ�
	void DeBug();								// ����� Ȯ�ο�

	MapTool() {}
	~MapTool() {}
};

