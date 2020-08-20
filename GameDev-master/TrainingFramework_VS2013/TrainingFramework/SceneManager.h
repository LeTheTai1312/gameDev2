#pragma once
#include "../Utilities/utilities.h"
#include "Object.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Animation2D.h"
#include <vector>
class Animation2D;
using namespace std;

class SceneManager
{
public:
	Objects* objects;
	Animation2D* anim;
	int objectNum;
	//int textureNum;
	//int cubeTextureNum;
	int animNum;
	void loadObjects(char *l);
	void draw();
	void update_animation(float);
	void free();
	SceneManager();
	~SceneManager();
	static SceneManager* GetInstance(float);
private:
	static SceneManager* s_Instance;
};

