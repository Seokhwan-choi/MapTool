#include "stdafx.h"
#include "Packman.h"


HRESULT Packman::init(void)
{
	_state = STATE::LEFT;
	_playerpt = { 250, WINSIZEY / 2 };
	_player = RectMakeCenter(_playerpt.x, _playerpt.y, 28, 28);
	_colcheck[0] = RectMakeCenter(_playerpt.x + 14, _playerpt.y, 2, 20);	// 오른쪽
	_colcheck[1] = RectMakeCenter(_playerpt.x - 14, _playerpt.y, 2, 20);	// 왼쪽
	_colcheck[2] = RectMakeCenter(_playerpt.x, _playerpt.y - 14, 20, 2);	// 위
	_colcheck[3] = RectMakeCenter(_playerpt.x, _playerpt.y + 14, 20, 2);	// 아래

	for (int i = 0; i < 10; ++i)
	{
		_enemypt[i] = { 250, WINSIZEY/2 };
		_Enemy[i]= RectMakeCenter(_enemypt[i].x, _enemypt[i].y, 28, 28);
		_enemystate[i] = (STATE)RND->range(4);
		_move2[i] = true;
		_movecount[i] = 0;
	}

	_move = false;
	
	
	
	this->SetMap();
	return S_OK;
}

void Packman::release(void)
{

}

void Packman::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		_move = true;
		_state = STATE::LEFT;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		_move = true;
		_state = STATE::RIGHT;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		_move = true;
		_state = STATE::UP;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		_move = true;
		_state = STATE::DOWN;
	}

	RECT temp;
	for (int i = 0; i < 400; ++i) 
	{
		for (int j = 0; j < 4; j++) {
			if (IntersectRect(&temp, &_colcheck[j], &_tiles[i].rc) && _tiles[i].obj == OBJECT::OBJ_BLOCKS)
			{
				if (j == 0) { // 오른쪽
					_playerpt.x -= _colcheck[j].right - _tiles[i].rc.left;
				}
				else if (j == 1) { // 왼쪽
					_playerpt.x += _tiles[i].rc.right - _colcheck[j].left;
				}
				else if (j == 2) { // 위
					_playerpt.y += _tiles[i].rc.bottom - _colcheck[j].top;
				}
				else { // 아래
					_playerpt.y -= _colcheck[j].bottom  - _tiles[i].rc.top;
				}
				_move = false;
				break;
			}
		}
	}

	RECT temp2;
	for (int i = 0; i < 400; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (IntersectRect(&temp2, &_Enemy[j], &_tiles[i].rc) && _tiles[i].obj == OBJECT::OBJ_BLOCKS)
			{
				int tempwidth = temp2.right - temp2.left;
				int tempheight = temp2.bottom - temp2.top;

				// 위/아래 에서 박았을 때
				if (tempwidth > tempheight) {
					if (_tiles[i].rc.top == temp2.top)
					{
						_enemypt[j].y -= tempheight;
					}
					else if (_tiles[i].rc.bottom == temp2.bottom)
					{
						_enemypt[j].y += tempheight;
					}
				}
				else {
					if (_tiles[i].rc.left == temp2.left) // 오른쪽에서 박았을 때
					{
						_enemypt[j].x -= tempwidth;
					}
					else if (_tiles[i].rc.right == temp2.right) // 왼쪽에서 박았을 때
					{
						_enemypt[j].x += tempwidth;
					}
				}
				_move2[j] = false;
				_enemystate[j] = (STATE)RND->range(4);
				break;
			}
		}
	}
	for (int i = 0; i < 10; ++i) {
		if (!_move2[i])
		{
			_movecount[i]++;
			if (_movecount[i] % 5 == 0)
			{
				_move2[i] = true;
			}
		}
	}

	this->EnemyState();
	this->PlayerState();
	for (int i = 0; i < 10; ++i)
	{
		_Enemy[i] = RectMakeCenter(_enemypt[i].x, _enemypt[i].y, 28, 28);
	}
	_player = RectMakeCenter(_playerpt.x, _playerpt.y, 28, 28);
	_colcheck[0] = RectMakeCenter(_playerpt.x + 14, _playerpt.y, 2, 20);	// 오른쪽
	_colcheck[1] = RectMakeCenter(_playerpt.x - 14, _playerpt.y, 2, 20);	// 왼쪽
	_colcheck[2] = RectMakeCenter(_playerpt.x, _playerpt.y - 14, 20, 2);	// 위
	_colcheck[3] = RectMakeCenter(_playerpt.x, _playerpt.y + 14, 20, 2);	// 아래
}

void Packman::render(void)
{
	this->MapRender();

	for (int i = 0; i < 10; ++i)
	{
		Rectangle(getMemDC(), _Enemy[i]);
	}
	Rectangle(getMemDC(), _player);
	for (int i = 0; i < 4; ++i) {
		Rectangle(getMemDC(), _colcheck[i]);
	}
}

void Packman::SetMap()
{
	//타일맵 이미지 초기화
	IMAGEMANAGER->addFrameImage("tilemap", "타일.bmp", 64, 32, SAMPLETILEX, SAMPLETILEY);

	HANDLE file;
	DWORD read;

	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}

void Packman::MapRender()
{
	//for (int i = 0; i < TILEX * TILEY; i++)
//{
//	Rectangle(getMemDC(), _tiles[i].rc);
//}

//인게임화면 지형을 그린다
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}

	//인게임화면 오브젝트 그린다
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_NONE) continue;

		IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}
}

void Packman::PlayerState()
{
	if (_move) 
	{
		switch (_state)
		{
		case STATE::LEFT:
			_playerpt.x -= 1;
			break;
		case STATE::RIGHT:
			_playerpt.x += 1;
			break;
		case STATE::UP:
			_playerpt.y -= 1;
			break;
		case STATE::DOWN:
			_playerpt.y += 1;
			break;
		}
	}
}

void Packman::EnemyState()
{
	for (int i = 0; i < 10; ++i) 
	{
		if (_move2[i])
		{
			switch (_enemystate[i])
			{
			case STATE::LEFT:
				_enemypt[i].x -= 1;
				break;
			case STATE::RIGHT:
				_enemypt[i].x += 1;
				break;
			case STATE::UP:
				_enemypt[i].y -= 1;
				break;
			case STATE::DOWN:
				_enemypt[i].y += 1;
				break;
			}
		}
	}


}
