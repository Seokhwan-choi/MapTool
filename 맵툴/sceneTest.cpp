#include "stdafx.h"
#include "sceneTest.h"


HRESULT sceneTest::init(void)
{
	//백그라운드 이미지 초기화
	IMAGEMANAGER->addImage("백그라운드", "background.bmp", WINSIZEX, WINSIZEY);

	//UFO 프레임 이미지 초기화
	IMAGEMANAGER->addFrameImage("ufo", "ufo.bmp", 530, 32, 10, 1);

	//총알 이미지
	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));


	//플레이어 클래스 생성및 초기화
	_player = new player;
	_player->init();

	//적매니져 클래스 생성 및 초기화
	_enemyManager = new enemyManager;
	_enemyManager->init();

	//상호참조용 포인터 링크하기
	_player->setEMLink(_enemyManager);
	_enemyManager->setPlayerLink(_player);

	return S_OK;
}

void sceneTest::release(void)
{
	//이미지 클래스를 나갈때까진 사용할 일 없다
	//동적할당 new를 사용했다면 이곳에서 SAFE_DELETE() 사용한다
	//_bgImage->release();
	//SAFE_DELETE(_bgImage);
	//이미지 매니져 사용시 매니져가 알아서 해제 해주니까
	//SAFE_DELETE() 도 사용할 필요가 없다

	//플레이어 클래스 해제
	_player->release();
	SAFE_DELETE(_player);

	//적매니져 클래스 해제
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);
}

void sceneTest::update(void)
{
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
	//간단하게 이곳에서 코딩한다고 생각하면 된다

	//플레이어 클래스 업데이트
	_player->update();

	//적매니져 클래스 업데이트
	_enemyManager->update();

	//충돌함수
	//this->collision();

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SCENEMANAGER->loadScene("픽셀충돌");
	}
}

void sceneTest::render(void)
{
	//이곳에서 WM_PAINT에서 했던것을 처리하면 된다

	//백그라운드 이미지 렌더
	IMAGEMANAGER->render("백그라운드", getMemDC());

	//플레이어 클래스 렌더
	_player->render();

	//적매니져 클래스 렌더
	_enemyManager->render();
}

void sceneTest::collision()
{
	//충돌처리
	//플레이어의 총알 & 적 => 충돌처리
	//플레이어에서 총알클래스 가져온다
	//총알클래스에서 총알벡터 가져온다
	//플레이어->미사일클래스->총알벡터[]
	//for (int i = 0; i < _player->getMissileM1()->getVBullet().size(); i++)
	//{
	//	
	//}

	//에너미클래스에서 총알클래스가 있을때
	//에너미매니져->에너미클래스->총알클래스->총알벡터
	//에너미매니져에서 총알클래스를 들고 있을때
	//에너미매니져->총알클래스->총알벡터

	//플레이어 총알 M1 vs 미니언 충돌처리
	for (int i = 0; i < _player->getMissileM1()->getVBullet().size(); i++) //플레이어가 쏜 총알
	{
		//미니언
		for (int j = 0; j < _enemyManager->getMinion().size(); j++)//적클래스
		{
			//충돌했냐?
			RECT rc;
			if (IntersectRect(&rc, &_player->getMissileM1()->getVBullet()[i].rc,
				&_enemyManager->getMinion()[j]->getRect()))
			{
				//플레이어 총알 삭제
				_player->removeMissileM1(i);
				//미니언 삭제
				_enemyManager->removeMinion(j);

				//씬변경
				//SCENEMANAGER->loadScene("키값");
				break;
			}
		}
	}

}