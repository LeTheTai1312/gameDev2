#include "stdafx.h"
#include "SceneManager.h"
#include "Singleton.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	/*for (int i = 0; i < objectNum; i++) {
		delete[] objects[i].texture;
		delete[] objects[i].cubeTexture;
		delete[] objects[i].shaders.m_texture;
	}*/
	for (int i = 0; i < animNum; i++) {
		delete[] anim[i].texture;
		delete[] anim[i].cubeTexture;
		delete[] anim[i].shaders.m_texture;
	}
	//delete[] objects;
	delete[] anim;
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
	for (int i = 0; i < animNum; i++) {
		fscanf(file, "ID %d\n", &animID);
		fscanf(file, "MODEL %d\n", &modelID);
		anim[animID].models = modelID;
		anim[animID].load_element("../Resources/sprites (1).txt");

		fscanf(file, "FRAME %d\n", &anim[animID].frameNum);
		anim[animID].frame = Singleton<ResourceManager>::GetInstance()->frames[anim[animID].frameNum];

		fscanf(file, "TEXTURES %d\n", &textureNum);
		anim[animID].texture = new int[textureNum];
		anim[animID].textureNum = textureNum;
		for (int j = 0; j < textureNum; j++) {
			fscanf(file, "TEXTURE %d\n", &textureID);
			anim[animID].texture[j] = textureID;
		}
		anim[animID].curent_texture = anim[animID].texture[0];
		anim[animID].play();
		//anim[animID].load_element("../Resources/sprites (1).txt");

		fscanf(file, "CUBETEXTURES %d\n", &cubeTextureNum);
		//anim[animID].cubeTexture = new int[cubeTextureNum];
		//anim[animID].cubeTextureNum = cubeTextureNum;
		for (int j = 0; j < cubeTextureNum; j++) {
			fscanf(file, "CUBETEX %d\n", &cubeTextureID);
			//anim[animID].cubeTexture[j] = cubeTextureID;
		}

		fscanf(file, "SHADER %d\n", &shaderID);
		anim[animID].shaders = Singleton<ResourceManager>::GetInstance()->shader[shaderID];
		int a = anim[animID].textureNum;
		anim[animID].shaders.m_texture = new int[a];
		fscanf(file, "SPEED %f\n", &anim[animID].speed);
		fscanf(file, "POSITION %f, %f, %f\n", &anim[animID].txw, &anim[animID].tyw, &anim[animID].tzw);
		fscanf(file, "ROTATION %f, %f, %f\n", &anim[animID].rxw, &anim[animID].ryw, &anim[animID].rzw);
		fscanf(file, "SCALE %f, %f, %f\n", &anim[animID].sxw, &anim[animID].syw, &anim[animID].szw);
	}

	fscanf(file, "#CAMERA\nNEAR %f\nFAR %f\nFOV %f\nSPEED %f", &Singleton<Camera>::GetInstance()->nearPlane, &Singleton<Camera>::GetInstance()->farPlane,
		&Singleton<Camera>::GetInstance()->fov, &Singleton<Camera>::GetInstance()->speed);
	fclose(file);

}

void SceneManager::draw() {
	Singleton<Camera>::GetInstance()->set_CamVP();
	for (int i = 0; i < animNum; i++) {
		anim[i].draw_anim();
	}
	for (int i = 0; i < objectNum; i++) {
		objects[i].draw();
	}
}

void SceneManager::update_animation(float deltaTime) {
	for (int i = 0; i < animNum; i++) {
		anim[i].update(deltaTime);
	}
}

void SceneManager::mouse_animation_move(int x, int y)
{
	for (int i = 0; i < animNum; i++) {
		anim[0].update_animation_move_player(x, y);
	}
}

void SceneManager::free() {
}
