#define _USE_MATH_DEFINES
#include "stdafx.h"
#include "Matran.h"
#include <cmath>

#define PI 3.141592653589

Matran::Matran()
{
}

Matran::~Matran()
{
}

void Matran::set_matrix() {

	set_world(0.75, 0, 90, 0, 0, -0.5, 0);
	set_view(60, 60, 0, 0, 0, 0);
	set_perspective();
	set_wvp();
}

void Matran::set_world(float s, float rx, float ry, float rz, float tx, float ty, float tz) {
	scaleMatrix.SetScale(s);
	Rx.SetRotationX(rx * (PI / 180));
	Ry.SetRotationY(ry * (PI / 180));
	Rz.SetRotationZ(rz * (PI / 180));
	rotationMatrix = Rz * Rx * Ry;
	translationMatrix.SetTranslation(tx, ty, tz);
	wMatrix = scaleMatrix * rotationMatrix * translationMatrix;
}

void Matran::set_view(float rx, float ry, float rz, float tx, float ty, float tz) {
	scale_view.SetIdentity();
	Rx_v.SetRotationX(-rx * (PI / 180));
	Ry_v.SetRotationY(-ry * (PI / 180));
	Rz_v.SetRotationZ(-rz * (PI / 180));
	rotation_view = Ry_v * Rx_v * Rz_v;
	translation_view.SetTranslation(-tx, -ty, -tz);
	vMatrix = translation_view * rotation_view;
}

void Matran::set_perspective() {
	pMatrix.SetIdentity();
}

void Matran::set_wvp() {
	wvpMatrix = wMatrix * vMatrix*  pMatrix;
}