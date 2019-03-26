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
	RECT rc;				// 타일 RECT
	int framex;				// 타일 프레임 X			
	int framey;				// 타일 프레임 Y
	bool show;				
};

class MapTool : public gameNode
{
private:
	POINT _CameraPos;							// 카메라 중점 좌표
	bool _Hold;									// 카메라 중지
	TagTile _Tile[XNUM][YNUM];					// 타일 
	TagTile _Sample[SAMPLENUMX][SAMPLENUMY];	// Sample Tile

	RECT _TilePalette;							// 타일 Palette용 RECT
	bool _Show;									// 타일 샘플 보여줌

	bool _Drag;									// 드래그 & 드롭 시작
	RECT _MouseRect;							// 드래그 & 드롭 RECT
	POINT _Start;								// 드래그 & 드롭 시작 좌표
	POINT _End;									// 드래그 & 드롭 끝 좌표





	bool _DeBug;								// 확인용 
	
public:

	HRESULT init();
	void update();
	void render();
	void release();

	void MouseMoveCamera();						// 마우스 카메라 이동 함수 
	void KeyBoardMoveCamera();					// 키보드 카메라 이동 함수
	void KeyHandling();							// 키 입력 처리
	void MouseSelect();							// 마우스 드래그 선택
	void SetTile();								// 타일 세팅하기
	void ShowPalette();							// 팔렛 보여주기
	void ShowTile();							// 타일 보여주기
	void DeBug();								// 디버그 확인용

	MapTool() {}
	~MapTool() {}
};

