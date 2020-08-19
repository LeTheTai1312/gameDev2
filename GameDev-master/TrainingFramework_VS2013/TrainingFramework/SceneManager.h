#pragma once
#include "../Utilities/utilities.h"
#include "Object.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Animation2D.h"
#include <vector>

using namespace std;

class SceneManager
{
public:
	Animation2D* anim;
	int objectNum;
	int textureNum;
	int cubeTextureNum;
	int animNum;
	void loadObjects(char *l);
	void draw();
	void free();
	SceneManager();
	~SceneManager();
	static SceneManager* GetInstance();
private:
	static SceneManager* s_Instance;
};

