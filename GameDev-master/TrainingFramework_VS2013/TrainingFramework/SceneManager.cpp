#include "stdafx.h"
#include "SceneManager.h"
#include "Singleton.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	for (int i = 0; i < objectNum; i++) {
		delete[] objects[i].texture;
		delete[] objects[i].cubeTexture;
		delete[] objects[i].shaders.m_texture;
	}
	for (int i = 0; i < animNum; i++) {
		delete[] anim[i].texture;
		delete[] anim[i].cubeTexture;
		delete[] anim[i].shaders.m_texture;
	}
	delete[] objects;
	delete[] anim;
	delete[] botFish;
	delete[] playerFish;
}

void SceneManager::loadObjects(char *l) {
	int ob, objectID, modelID, textureID, cubeTextureID, shaderID, textureNum, cubeTextureNum;
	float anim_speed;
	int animID;
	FILE *file;
	file = fopen(l, "r");
	fscanf(file, "#Objects: %d\n", &objectNum);
	objects = new Objects[objectNum];
	//anim = new Animation2D[objectNum];
	for(int i = 0; i < objectNum; i++){
		fscanf(file, "ID %d\n", &objectID);
		fscanf(file, "MODEL %d\n", &modelID);
		objects[objectID].models = modelID;

		fscanf(file, "TEXTURES %d\n", &textureNum);
		objects[objectID].texture = new int[textureNum];
		objects[objectID].textureNum = textureNum;
		for (int j = 0; j < textureNum; j++) {
			fscanf(file, "TEXTURE %d\n", &textureID);
			objects[objectID].texture[j] = textureID;
		}

		fscanf(file, "CUBETEXTURES %d\n", &cubeTextureNum);
		objects[objectID].cubeTexture = new int[cubeTextureNum];
		objects[objectID].cubeTextureNum = cubeTextureNum;
		for (int j = 0; j < cubeTextureNum; j++) {
			fscanf(file, "CUBETEX %d\n", &cubeTextureID);	
			objects[objectID].cubeTexture[j] = cubeTextureID;
		}

		fscanf(file, "SHADER %d\n", &shaderID);
		objects[objectID].shaders = Singleton<ResourceManager>::GetInstance()->shader[shaderID];
		int a = objects[objectID].textureNum;
		objects[objectID].shaders.m_texture = new int[a];
		fscanf(file, "POSITION %f, %f, %f\n", &objects[objectID].txw, &objects[objectID].tyw, &objects[objectID].tzw);
		fscanf(file, "ROTATION %f, %f, %f\n", &objects[objectID].rxw, &objects[objectID].ryw, &objects[objectID].rzw);
		fscanf(file, "SCALE %f, %f, %f\n", &objects[objectID].sxw, &objects[objectID].syw, &objects[objectID].szw);
	}

	fscanf(file, "#Animations: %d\n", &animNum);
	anim = new Animation2D[animNum];
	botFish = new BotFish[animNum];
	playerFish = new PlayerFish[1];
	for (int i = 1; i < animNum; i++) {
		if (i == 0) {
			fscanf(file, "ID %d\n", &animID);
			fscanf(file, "MODEL %d\n", &modelID);
			playerFish[animID].models = modelID;
			playerFish[animID].load_element("../Resources/sprites (1).txt");

			fscanf(file, "FRAME %d\n", &playerFish[animID].frameNum);
			playerFish[animID].frame = Singleton<ResourceManager>::GetInstance()->frames[playerFish[animID].frameNum];

			fscanf(file, "TEXTURES %d\n", &textureNum);
			playerFish[animID].texture = new int[textureNum];
			playerFish[animID].textureNum = textureNum;
			for (int j = 0; j < textureNum; j++) {
				fscanf(file, "TEXTURE %d\n", &textureID);
				playerFish[animID].texture[j] = textureID;
			}
			playerFish[animID].curent_texture = playerFish[animID].texture[0];
			playerFish[animID].play();

			fscanf(file, "CUBETEXTURES %d\n", &cubeTextureNum);
			for (int j = 0; j < cubeTextureNum; j++) {
				fscanf(file, "CUBETEX %d\n", &cubeTextureID);
			}

			fscanf(file, "SHADER %d\n", &shaderID);

			playerFish[animID].shaders = Singleton<ResourceManager>::GetInstance()->shader[shaderID];
			int a = botFish[animID].textureNum;
			playerFish[animID].shaders.m_texture = new int[a];
			fscanf(file, "SPEED %f\n", &playerFish[animID].speed);
			fscanf(file, "SIZE %d\n", &playerFish[animID].size);
			playerFish[animID].vb = 8 - playerFish[animID].size;
			fscanf(file, "POSITION %f, %f, %f\n", &playerFish[animID].txw, &playerFish[animID].tyw, &playerFish[animID].tzw);
			fscanf(file, "ROTATION %f, %f, %f\n", &playerFish[animID].rxw, &playerFish[animID].ryw, &playerFish[animID].rzw);
			fscanf(file, "SCALE %f, %f, %f\n", &playerFish[animID].sxw, &playerFish[animID].syw, &playerFish[animID].szw);
			playerFish[i].sx = playerFish[i].sxw;
			playerFish[i].sy = playerFish[i].syw;
			playerFish[i].sz = playerFish[i].szw;
		}
		else {
			fscanf(file, "ID %d\n", &animID);
			fscanf(file, "MODEL %d\n", &modelID);
			//anim[animID].models = modelID;
			botFish[animID].models = modelID;
			//anim[animID].load_element("../Resources/sprites (1).txt");
			botFish[animID].load_element("../Resources/sprites (1).txt");


			//fscanf(file, "FRAME %d\n", &anim[animID].frameNum);
			fscanf(file, "FRAME %d\n", &botFish[animID].frameNum);
			//anim[animID].frame = Singleton<ResourceManager>::GetInstance()->frames[anim[animID].frameNum];
			botFish[animID].frame = Singleton<ResourceManager>::GetInstance()->frames[botFish[animID].frameNum];

			fscanf(file, "TEXTURES %d\n", &textureNum);
			/*anim[animID].texture = new int[textureNum];
			anim[animID].textureNum = textureNum;*/
			botFish[animID].texture = new int[textureNum];
			botFish[animID].textureNum = textureNum;
			for (int j = 0; j < textureNum; j++) {
				fscanf(file, "TEXTURE %d\n", &textureID);
				//anim[animID].texture[j] = textureID;
				botFish[animID].texture[j] = textureID;
			}
			/*anim[animID].curent_texture = anim[animID].texture[0];
			anim[animID].play();*/
			botFish[animID].curent_texture = botFish[animID].texture[0];
			botFish[animID].play();

			fscanf(file, "CUBETEXTURES %d\n", &cubeTextureNum);
			for (int j = 0; j < cubeTextureNum; j++) {
				fscanf(file, "CUBETEX %d\n", &cubeTextureID);
			}

			fscanf(file, "SHADER %d\n", &shaderID);
			/*anim[animID].shaders = Singleton<ResourceManager>::GetInstance()->shader[shaderID];
			int a = anim[animID].textureNum;
			anim[animID].shaders.m_texture = new int[a];
			fscanf(file, "SPEED %f\n", &anim[animID].speed);
			fscanf(file, "SIZE %d\n", &anim[animID].size);
			anim[animID].vb = 8 - anim[animID].size;
			fscanf(file, "POSITION %f, %f, %f\n", &anim[animID].txw, &anim[animID].tyw, &anim[animID].tzw);
			fscanf(file, "ROTATION %f, %f, %f\n", &anim[animID].rxw, &anim[animID].ryw, &anim[animID].rzw);
			fscanf(file, "SCALE %f, %f, %f\n", &anim[animID].sxw, &anim[animID].syw, &anim[animID].szw);
			anim[i].sx = anim[i].sxw;
			anim[i].sy = anim[i].syw;
			anim[i].sz = anim[i].szw;*/

			botFish[animID].shaders = Singleton<ResourceManager>::GetInstance()->shader[shaderID];
			int a = botFish[animID].textureNum;
			botFish[animID].shaders.m_texture = new int[a];
			fscanf(file, "SPEED %f\n", &botFish[animID].speed);
			fscanf(file, "SIZE %d\n", &botFish[animID].size);
			botFish[animID].vb = 8 - botFish[animID].size;
			fscanf(file, "POSITION %f, %f, %f\n", &botFish[animID].txw, &botFish[animID].tyw, &botFish[animID].tzw);
			fscanf(file, "ROTATION %f, %f, %f\n", &botFish[animID].rxw, &botFish[animID].ryw, &botFish[animID].rzw);
			fscanf(file, "SCALE %f, %f, %f\n", &botFish[animID].sxw, &botFish[animID].syw, &botFish[animID].szw);
			botFish[i].sx = botFish[i].sxw;
			botFish[i].sy = botFish[i].syw;
			botFish[i].sz = botFish[i].szw;
		}
	}

	fscanf(file, "#CAMERA\nNEAR %f\nFAR %f\nFOV %f\nSPEED %f", &Singleton<Camera>::GetInstance()->nearPlane, &Singleton<Camera>::GetInstance()->farPlane,
		&Singleton<Camera>::GetInstance()->fov, &Singleton<Camera>::GetInstance()->speed);
	fclose(file);
	/*for (int i = 1; i < animNum; i++) {
		anim[i].tzw = anim[0].tzw - (i * 0.01);
	}*/
	for (int i = 1; i < animNum; i++) {
		botFish[i].tzw = botFish[0].tzw - (i * 0.01);
	}
}

void SceneManager::draw() {
	Singleton<Camera>::GetInstance()->set_CamVP();
	objects[0].draw();
	for (int i = animNum - 1; i >= 0; i--) {
		if (i = 0) playerFish[i].draw();
		else botFish->draw();
		//anim[i].draw_anim();
	}
	for (int i = objectNum - 1; i >= 0; i--) {
		objects[i].draw();
	}
}
float time = 0;
void SceneManager::update_animation(float deltaTime) {
	for (int i = 0; i < animNum; i++) {
		if (i = 0) playerFish[i].update(deltaTime);
		else botFish->update(deltaTime);
		//anim[i].update(deltaTime);
	}
	if (time > 0.03) {
		time = 0;
		for (int i = 1; i < animNum; i++) {
			botFish[i].update_animation_move_boss(deltaTime);
			//anim[i].update_animation_move_boss(deltaTime);
		}
	}
	else {
		time += deltaTime;
	}
	checkColRecRec();
}

void SceneManager::mouse_animation_move(int x, int y)
{
	playerFish[0].update_animation_move_player(x, y);
	//anim[0].update_animation_move_player(x, y);
}

void SceneManager::free() {
}

bool SceneManager::checkEvent()
{	
	for (int i = 0; i < animNum; i++) {
		if (anim[i].checkEvent()) return true;
	}
	return false;
}

bool SceneManager::checkCoRec(Rectangl rec, Circle cir)
{	
	for (int i = 1; i < animNum; i++) {
	}
	return false;
}

bool SceneManager::checkCoCirCir()
{
	/*for (int i = 0; i < animNum; i++) {
		for (int j = 0; j < animNum; j++)
			if (Singleton<Physic>::GetInstance()->checkCoCirCir(anim[i].cir, anim[j].cir) && i != j)
				if (anim[i].size > anim[j].size) {
					anim[j].signal = 4;
				}
				else if (anim[j].size > anim[i].size) {
				}
				return true;
	}*/
	return false;
}

bool SceneManager::checkColRecRec()
{
	/*for (int i = 0; i < animNum; i++) {
		for (int j = 0; j < animNum; j++) {
			if (Singleton<Physic>::GetInstance()->checkColRecRec(anim[i].rect, anim[j].rect) && i != j) {
				if (anim[i].size > anim[j].size) {
					anim[i].signal = 3;
					anim[j].disapear_wait = 1;
				}
				else if (anim[j].size > anim[i].size) {
					anim[j].signal = 3;
					anim[i].disapear_wait = 1;
				}
			}
		}
	}*/

	for (int i = 1; i < animNum; i++) {
		if (Singleton<Physic>::GetInstance()->checkColRecRec(playerFish[i].rect, botFish[i].rect)) {
			if (playerFish[0].size > botFish[i].size) {
				playerFish[0].signal = 3;
				botFish[i].disapear_wait = 1;
			}
			else if (playerFish[0].size < botFish[i].size) {
				botFish[i].signal = 3;
				playerFish[0].disapear_wait = 1;
			}
		}
	}

	for (int i = 1; i < animNum; i++) {
		for (int j = 1; j < animNum; j++) {
			if (Singleton<Physic>::GetInstance()->checkColRecRec(botFish[i].rect, botFish[j].rect) && i != j) {
				if (botFish[i].size > anim[j].size) {
					botFish[i].signal = 3;
					botFish[j].disapear_wait = 1;
				}
				else if (botFish[j].size > botFish[i].size) {
					botFish[j].signal = 3;
					botFish[i].disapear_wait = 1;
				}
			}
		}
	}
	return true;
}
