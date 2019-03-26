#include "stdafx.h"
#include "Camera.h"


void Camera::SetCamemra(POINT pt)
{
	_CameraPos = pt;
	_CameraRc = RectMakeCenter(_CameraPos.x, _CameraPos.y, WINSIZEX, WINSIZEY);

	if (_CameraRc.left < 0) 
	{
		_CameraPos.x -= _CameraRc.left;
	}

	if (_CameraRc.right > 2048) 
	{
		_CameraPos.x -= _CameraRc.right - 2048;
	}

	if (_CameraRc.top < 0) 
	{
		_CameraPos.y -= _CameraRc.top;
	}

	if (_CameraRc.bottom > 2304)
	{
		_CameraPos.y -= _CameraRc.bottom - 2304;
	}

	_CameraRc = RectMakeCenter(_CameraPos.x, _CameraPos.y, WINSIZEX, WINSIZEY);
}

RECT Camera::GetCamemra()
{
	return RECT(_CameraRc);
}

RECT Camera::Relative(RECT rc)
{
	rc.left -= _CameraRc.left;
	rc.top -= _CameraRc.top;
	rc.right -= _CameraRc.left;
	rc.bottom -= _CameraRc.top;
	return RECT(rc);
}