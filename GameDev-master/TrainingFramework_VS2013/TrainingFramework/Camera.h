#pragma once
#include "../Utilities/utilities.h"
#include "Matran.h"
#include<math.h>
#include "Globals.h"


class Camera
{
public:
	float speed = 2.0;
	void set_camera(float rx, float ry, float rz, float tx, float ty, float tz);
	Vector3 camera_pos = Vector3(0.0, 0.0, 2.5);
	Vector3 camera_target = Vector3(0.0, 0.0, 0.0);
	Vector3 up = Vector3(0.0, 1.0, 0.0);
	Vector3 zaxis = (camera_pos - camera_target).Normalize();
	Vector3 xaxis = (up.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();

	float nearPlane;
	float farPlane;
	float aspect = 1.0*Globals::screenWidth / Globals::screenHeight;
	float fov;

	Matrix camera_mRotationB, camera_mRotationViewB, camera_mtranslationB, camera_mTranslationViewB;


	Matrix camera_mWorld, camera_mView, camera_mPerspective, camera_rx, camera_ry, camera_rz, camera_VP,
		camera_mScale, camera_mRotation, camera_mTranslation,
		camera_mScaleView, camera_mRotationView, camera_mTranslationView, camera_rxView, camera_ryView, camera_rzView;
	Matrix M;
	void init();
	void movementL(float deltaTime);
	void movementR(float deltaTime);
	void movementF(float deltaTime);
	void movementB(float deltaTime);
	void rotationsL(float deltaTime);
	void rotationsR(float deltaTime);
	void rotationsU(float deltaTime);
	void rotationsD(float deltaTime);
	void movementU(float deltaTime);
	void movementD(float deltaTime);
	void cal_perspective_matrix();
	void cal_world_matrix();
	void cal_view_matrix();
	void set_mRotationB();
	void set_mRotationViewB();
	void set_mtranslationB();
	void set_mTranslationViewB();
	void set_CamVP();
	void SetPerspective2D();

	Camera();
	~Camera();

private:

};
