#pragma once
class Camera : public singletonBase<Camera>
{
private:
	RECT _CameraRc;			// ī�޶� RECT
	POINT _CameraPos;		// ī�޶� ��ǥ
public:

	void SetCamemra(POINT pt);
	RECT GetCamemra();
	RECT Relative(RECT rc);

	Camera() {}
	~Camera() {}
};

#define CAMERA Camera::getSingleton()

