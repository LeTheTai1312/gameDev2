#pragma once
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include <vector>
#include <math.h>

class Matran {
public:
	Matrix scaleMatrix, rotationMatrix, translationMatrix, Rx, Ry, Rz, scale_view, rotation_view, translation_view,
		Rx_v, Ry_v, Rz_v;
	Matrix wMatrix, vMatrix, pMatrix, wvpMatrix;
	void set_matrix();
	void set_world(float s, float rx, float ry, float rz, float tx, float ty, float tz);
	void set_view(float rx, float ry, float rz, float tx, float ty, float tz);
	void set_perspective();
	void set_wvp();
	Matran();
	~Matran();
};
