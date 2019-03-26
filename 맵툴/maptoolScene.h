#pragma once
#include "gameNode.h"
#include "tileNode.h"


class maptoolScene : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];  //�ΰ���ȭ�� �� 400�� Ÿ��
	tagSampleTile _sampleTile[SAMPLETILEX * SAMPLETILEY]; //����Ÿ�� �� 160��
	tagCurrentTile _currentTile;	//����Ÿ��

	RECT _rcSave;		//���̺�
	RECT _rcLoad;		//�ε�
	RECT _rcTerrain;	//����
	RECT _rcObject;		//������Ʈ
	RECT _rcEraser;		//���찳(������Ʈ�� �����, ������ ������ ����)
	
	CTRL _ctrlSelect;	//���� � ��Ʈ�� ��������

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//��������
	void maptoolSetup();
	void setMap();
	void save();
	void load();

	//����, ������Ʈ ����
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

	maptoolScene() {}
	~maptoolScene() {}
};

