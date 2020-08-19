#include "stdafx.h"
#include "Camera.h"
#include <iostream>
#define PI 3.141592653589

Camera::Camera()
{
	set_CamVP();
}

Camera::~Camera()
{
}

void Camera::set_camera(float rx, float ry, float rz, float tx, float ty, float tz) {
}

void Camera::init() {
}

void Camera::movementL(float deltaTime) {
	Vector3 deltamove;
	deltamove = -xaxis*deltaTime*speed;
	camera_pos += deltamove;
	camera_target += deltamove;
	zaxis = (camera_pos - camera_target).Normalize();
	xaxis = (up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();
}

void Camera::movementR(float deltaTime) {
	Vector3 deltamove;
	deltamove = xaxis*deltaTime*speed;
	camera_pos += deltamove;
	camera_target += deltamove;
}

void Camera::movementU(float deltaTime) {
	Vector3 deltamove;
	deltamove = yaxis*deltaTime*speed;
	camera_pos += deltamove;
	camera_target += deltamove;
}

void Camera::movementD(float deltaTime) {
	Vector3 deltamove;
	deltamove = -yaxis*deltaTime*speed;
	camera_pos += deltamove;
	camera_target += deltamove;
}

void Camera::movementF(float deltaTime) {
	Vector3 deltamove;
	deltamove = -zaxis*deltaTime*speed;
	camera_pos += deltamove;
	camera_target += deltamove;
}

void Camera::movementB(float deltaTime) {
	Vector3 deltamove;
	deltamove = zaxis*deltaTime*speed;
	camera_pos += deltamove;
	camera_target += deltamove;
}

void Camera::rotationsL(float deltaTime){
	Matrix a;
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(camera_pos - camera_target).Length(), 1.0f);
	Vector4 localNewTarget = localTarget * a.SetRotationY(deltaTime * speed);
	Vector4 worldNewTarget = localNewTarget * camera_mWorld;

	camera_target.x = worldNewTarget.x;
	camera_target.y = worldNewTarget.y;
	camera_target.z = worldNewTarget.z;

	zaxis = (camera_pos - camera_target).Normalize();
	xaxis = (up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();
}
void Camera::rotationsR(float deltaTime){
	Matrix a;
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(camera_pos - camera_target).Length(), 1.0f);
	Vector4 localNewTarget = localTarget * a.SetRotationY(-deltaTime * speed);
	Vector4 worldNewTarget = localNewTarget * camera_mWorld;

	camera_target.x = worldNewTarget.x;
	camera_target.y = worldNewTarget.y;
	camera_target.z = worldNewTarget.z;

	zaxis = (camera_pos - camera_target).Normalize();
	xaxis = (up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();
}

void Camera::rotationsD(float deltaTime) {
	Matrix a;
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(camera_pos - camera_target).Length(), 1.0f);
	Vector4 localNewTarget = localTarget * a.SetRotationX(-deltaTime * speed);
	Vector4 worldNewTarget = localNewTarget * camera_mWorld;

	camera_target.x = worldNewTarget.x;
	camera_target.y = worldNewTarget.y;
	camera_target.z = worldNewTarget.z;

	zaxis = (camera_pos - camera_target).Normalize();
	xaxis = (up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();
}

void Camera::rotationsU(float deltaTime) {
	Matrix a;
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(camera_pos - camera_target).Length(), 1.0f);
	Vector4 localNewTarget = localTarget * a.SetRotationX(deltaTime * speed);
	Vector4 worldNewTarget = localNewTarget * camera_mWorld;

	camera_target.x = worldNewTarget.x;
	camera_target.y = worldNewTarget.y;
	camera_target.z = worldNewTarget.z;

	zaxis = (camera_pos - camera_target).Normalize();
	xaxis = (up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();
}

void Camera::cal_world_matrix() {
	camera_mScale.SetIdentity();
	//camera_rx.SetRotationX(rx * (PI / 180) * 0);
	//camera_ry.SetRotationY(ry * (PI / 180) * 0);
	//camera_rz.SetRotationZ(rz * (PI / 180) * 0);
	//camera_mRotation = camera_rx * camera_ry * camera_rz;
	set_mRotationB();
	set_mtranslationB();
	camera_mWorld = camera_mScale * camera_mRotationB * camera_mtranslationB;
}

void Camera::cal_view_matrix() {
	
	//camera_rxView.SetRotationX(-rx * (PI / 180) * 0);
	//camera_ryView.SetRotationY(-ry * (PI / 180) * 0);
	//camera_rzView.SetRotationZ(-rz * (PI / 180) * 0);
	//camera_mRotationView = camera_rxView * camera_ryView * camera_rzView;
	set_mRotationViewB();
	set_mTranslationViewB();
	//camera_mTranslationView.SetTranslation(-tx, -ty, -tz);
	camera_mView = camera_mTranslationViewB * camera_mRotationViewB;
}

void Camera::cal_perspective_matrix() {
	//camera_mPerspective.SetPerspective(fov, aspect, nearPlane, farPlane);
	SetPerspective2D();
	camera_mPerspective = M;
}

void Camera::set_mRotationB() {
	camera_mRotationB.m[0][0] = xaxis.x; camera_mRotationB.m[0][1] = xaxis.y; camera_mRotationB.m[0][2] = xaxis.z; camera_mRotationB.m[0][3] = 0;
	camera_mRotationB.m[1][0] = yaxis.x; camera_mRotationB.m[1][1] = yaxis.y; camera_mRotationB.m[1][2] = yaxis.z; camera_mRotationB.m[1][3] = 0;
	camera_mRotationB.m[2][0] = zaxis.x; camera_mRotationB.m[2][1] = zaxis.y; camera_mRotationB.m[2][2] = zaxis.z; camera_mRotationB.m[2][3] = 0;
	camera_mRotationB.m[3][0] = 0; camera_mRotationB.m[3][1] = 0; camera_mRotationB.m[3][2] = 0; camera_mRotationB.m[3][3] = 1;
}

void Camera::set_mRotationViewB() {
	camera_mRotationViewB.m[0][0] = xaxis.x; camera_mRotationViewB.m[1][0] = xaxis.y; camera_mRotationViewB.m[2][0] = xaxis.z; camera_mRotationViewB.m[3][0] = 0;
	camera_mRotationViewB.m[0][1] = yaxis.x; camera_mRotationViewB.m[1][1] = yaxis.y; camera_mRotationViewB.m[2][1] = yaxis.z; camera_mRotationViewB.m[3][1] = 0;
	camera_mRotationViewB.m[0][2] = zaxis.x; camera_mRotationViewB.m[1][2] = zaxis.y; camera_mRotationViewB.m[2][2] = zaxis.z; camera_mRotationViewB.m[3][2] = 0;
	camera_mRotationViewB.m[0][3] = 0; camera_mRotationViewB.m[1][3] = 0; camera_mRotationViewB.m[2][3] = 0; camera_mRotationViewB.m[3][3] = 1;
}

void Camera::set_mtranslationB() {
	camera_mtranslationB.SetTranslation(camera_pos.x, camera_pos.y, camera_pos.z);
}

void Camera::set_mTranslationViewB() {
	camera_mTranslationViewB.SetTranslation(-camera_pos.x, -camera_pos.y, -camera_pos.z);
}

void Camera::set_CamVP() {
	cal_view_matrix();
	cal_perspective_matrix();
	cal_world_matrix();
	camera_VP = camera_mView * camera_mPerspective;
}

void Camera::SetPerspective2D(){
	const float angleOfView = 90;
	float b, t, l, r, n, f;
	/*float scale = tan(90.0 * 0.5 * PI / 180) * nearPlane;
	r = aspect * scale, l = -r;
	t = scale, b = -t;*/
	r = 1.5; l = -1.5; b = -1.5; t = 1.5; n = -10.0; f = 10.0;

	M.m[0][0] = 2 / (r - l); //1/r;
	M.m[1][0] = 0;
	M.m[2][0] = 0;
	M.m[3][0] = 0;

	M.m[0][1] = 0;
	M.m[1][1] = 2 / (t - b) /*1/t*/;
	M.m[2][1] = 0;
	M.m[3][1] = 0;

	M.m[0][3] = -(r + l) / (r - l);
	M.m[1][3] = -(t + b) / (t - b);
	M.m[2][3] = -(f + n) / (f - n)/*-2 / (f - n)*/;
	M.m[3][3] = 1 /*0*/ ;

	M.m[0][2] = 0;
	M.m[1][2] = 0;
	M.m[2][2] = -2/ (f - n)/*-(f + n) / (f - n)*/;
	M.m[3][2] = 0;
}