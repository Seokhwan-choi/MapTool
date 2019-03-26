#pragma once
class Camera : public singletonBase<Camera>
{
private:
	RECT _CameraRc;			// 카메라 RECT
	POINT _CameraPos;		// 카메라 좌표
public:

	void SetCamemra(POINT pt);
	RECT GetCamemra();
	RECT Relative(RECT rc);

	Camera() {}
	~Camera() {}
};

#define CAMERA Camera::getSingleton()

