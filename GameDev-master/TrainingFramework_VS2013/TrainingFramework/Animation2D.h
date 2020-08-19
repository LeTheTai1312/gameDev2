#pragma once
#include "../Utilities/utilities.h"
#include "Texture.h"
#include "model.h"
#include "Shaders.h"
#include "Object.h"
#include "Camera.h"
#include "Singleton.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include <vector>

class Animation2D: public Objects
{
public:
	Animation2D();
	~Animation2D();

	void play();
	void set_animation_speed(float newSpeed);
	void draw_anim();
	void update(float);
	void load_element(const char* fileName);
	model model;
	double anim_cursor;
	int curent_frame_indx;
	int frames_count;
	float speed;

	vector<vector<float>> frames;
};
