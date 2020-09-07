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
	void update_animation_move_boss(float);
	void turning(); // ca quay dau
	void bite();
	bool checkEvent(); //kiem tra event ca quay dau xong
	void initShape();
	void initCir();
	void disapear();
	void zoom();
	void follow();
	void avoid();
	void SetVectorh(float a, float b, float deltaTime);
	vector<float> frame; // vector kich thuoc hinh chu nhat
	Rectangl rect;
	Circle cir;
	model modela;
	double anim_cursor;
	int vb; //van toc ca bot
	int disapear_wait = 0;
	int size;
	int check;
	int countFrame;
	int curent_frame_indx;
	int curent_texture;
	int frames_count;
	int x_temp;
	int y_temp;
	int signal; // 1 = turn; 3 = bite;
	int c = 0;
	int frameNum;
	float m_hx, m_hy;
	float sx, sy, sz;
	float dtTm;
	float bite_wait = 0;
	float speed;

	vector<vector<float>> frames;
};
