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
#include "Rectangl.h"
#include"Cricle.h"
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
	void update_animation_move_player(int x, int y);
	void update_animation_move_boss();
	vector<float> frame; // vector kich thuoc hinh chu nhat
	Rectangl rect;
	Circle cir;
	model modela;
	double anim_cursor;
	int curent_frame_indx;
	int curent_texture;
	int frames_count;
	int x_temp;
	int y_temp;
	int signal;
	int frameNum;
	float dtTm;
	float frame_wait;
	float speed;

	vector<vector<float>> frames;
};
