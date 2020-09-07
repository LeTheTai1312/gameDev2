#pragma once
#include "../Utilities/utilities.h"
#include "Object.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "physic.h"
#include "PlayerFish.h"
#include "BotFish.h"
#include <vector>
class Animation2D;
class PlayerFish;
class BotFish;

using namespace std;

class SceneManager
{
public:
	Objects* objects;
	Animation2D* anim;
	PlayerFish* playerFish;
	BotFish* botFish;
	int objectNum;
	//int textureNum;
	//int cubeTextureNum;
	int animNum;
	void loadObjects(char *l);
	void draw();
	void update_animation(float);
	void mouse_animation_move(int x, int y);
	void free();
	bool checkEvent();
	SceneManager();
	~SceneManager();
	bool checkCoRec(Rectangl rec, Circle cir);
	bool checkCoCirCir();
	bool checkColRecRec();
	static SceneManager* GetInstance(float);
private:
	static SceneManager* s_Instance;
};

