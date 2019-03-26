#pragma once
#include "singletonBase.h"

class saveData : public singletonBase<saveData>
{
private:
	int _hp;
	POINT _pos;

public:
	HRESULT init(void);
	void release(void);

	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; }
	POINT getPos() { return _pos; }
	void setPos(POINT pos) { _pos = pos; }

	saveData() {}
	~saveData() {}
};

