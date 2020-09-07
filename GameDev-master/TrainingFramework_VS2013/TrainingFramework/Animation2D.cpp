#include "stdafx.h"
#include "Animation2D.h"
#include <string>
#include <time.h>

Animation2D::Animation2D(){
	m_hx = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100))) - 50.0;
	m_hy = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100))) - 50.0;
}

Animation2D::~Animation2D()
{
}

void Animation2D::play()
{
	vector<float> frame = Singleton<ResourceManager>::GetInstance()->frames[frameNum];
	//nomalization
	frame[0] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].width;
	frame[1] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].height;
	frame[2] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].width;
	frame[3] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].height;

	modela.vertices[0].uv.x = frame[0] + frame[2]; modela.vertices[0].uv.y = frame[1];
	modela.vertices[1].uv.x = frame[0] + frame[2]; modela.vertices[1].uv.y =  (frame[1] + frame[3]) ;
	modela.vertices[2].uv.x = frame[0]; modela.vertices[2].uv.y =  (frame[1] + frame[3]);
	modela.vertices[3].uv.x = frame[0]; modela.vertices[3].uv.y =  frame[1];

	
	//glGenBuffers(1, &modela->vboId);
	glBindBuffer(GL_ARRAY_BUFFER, modela.vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, modela.vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*glGenBuffers(1, &model.iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6, model.indices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
}	


void Animation2D::set_animation_speed(float newSpeed)
{
	speed = newSpeed;
}

void Animation2D::draw_anim()
{
	//camera.set_CamVP();
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//play();
	set_matrix(Singleton<Camera>::GetInstance()->camera_VP);
	glUseProgram(shaders.program);
	glUniformMatrix4fv(shaders.WVP, 1, GL_FALSE, &wvpMatrix.m[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, modela.vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modela.iboId);

	glBindTexture(GL_TEXTURE_2D, Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].textureID);
	glUniform1i(glGetUniformLocation(shaders.program, "u_texture"), 0);

	if (shaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(shaders.positionAttribute);
		glVertexAttribPointer(shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (shaders.uvAttribute != -1)
	{
		glEnableVertexAttribArray(shaders.uvAttribute);
		glVertexAttribPointer(shaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3)
			+ sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3));
	}

	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDepthMask(GL_TRUE);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Animation2D::update(float deltaTime)
{
	initShape();
	anim_cursor += deltaTime;
	dtTm = deltaTime;
	//frame_wait += deltaTime;
	
	if (anim_cursor > speed) {
		//curent_frame_indx = (curent_frame_indx + 1) % frames_count;
		anim_cursor = 0;
		//vector<float> frame = frames[curent_frame_indx];
		vector<float> frame = Singleton<ResourceManager>::GetInstance()->frames[frameNum];
		//nomalization
		frame[0] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].width;
		frame[1] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].height;
		frame[2] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].width;
		frame[3] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].height;

		modela.vertices[0].uv.x = (modela.vertices[0].uv.x + frame[2]); modela.vertices[0].uv.y = frame[1];
		modela.vertices[1].uv.x = (modela.vertices[1].uv.x + frame[2]); modela.vertices[1].uv.y = (frame[1] + frame[3]);
		modela.vertices[2].uv.x = (modela.vertices[2].uv.x + frame[2]); modela.vertices[2].uv.y = (frame[1] + frame[3]);
		modela.vertices[3].uv.x = (modela.vertices[3].uv.x + frame[2]); modela.vertices[3].uv.y = frame[1];

		countFrame ++;
		//cout << countFrame;

		glBindBuffer(GL_ARRAY_BUFFER, modela.vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, modela.vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void Animation2D::load_element(const char* fileName){
	int index;
	anim_cursor = 0;
	curent_frame_indx = 0;
	signal = 0;
	countFrame = 0;

	/*srand(time(NULL));
	int res = (float)rand();*/

	cout << m_hx << "-" << m_hy << endl;
	modela.init("../Resources/Models/animation.nfg");
}
void Animation2D::update_animation_move_player(int x, int y)
{
	int v = 3.5;//vận tốc tính theo pixel ban đầu mặc định
	float a = (txw + 1.5) * Globals::screenWidth / 3;
	float b = (1.5 - tyw) * Globals::screenHeight / 3;//toa do vi tri cua player hien tai tinh theo pixel

	float j = x - a;//vector chi huong chuyen dong 
	float k = y - b;
	float cc = v * (float)j / sqrt(j * j + k * k);
	float d = v * (float)k / sqrt(j * j + k * k);

	this->x_temp = cc;
	this->y_temp = d;

	a += cc;//vị trí sau khi di chuyển
	b += d;

	txw = ((float)a / Globals::screenWidth) * 3.0 - 1.5;
	tyw = -(((float)b / Globals::screenHeight) * 3.0 - 1.5);
	if (j <= -2 && c == 0) { // bat su kien ca quay dau
		countFrame = 0;
		c = 1;
		signal = 1;
	}
	else if (j > 2 && c == 1) {
		countFrame = 0;
		signal = 1;
		c = 0;
	}
	turning();
	bite();
	zoom();
	if (countFrame == 5 && c == 1) {
		curent_texture = texture[1];
		play();
		countFrame = 0;
		signal = 0;
		bite_wait = 0;
		disapear_wait = 0;
	}
	else if (countFrame == 5 && c == 0) {
		curent_texture = texture[0];
		play();
		countFrame = 0;
		signal = 0;
		bite_wait = 0;
		disapear_wait = 0;
	}


}

void Animation2D::update_animation_move_boss(float deltaTime)
{
	//int vb = 2;//vận tốc tính theo pixel ban đầu mặc định
	float a = (txw + 1.5) * Globals::screenWidth / 3;
	float b = (1.5 - tyw) * Globals::screenHeight / 3;//toa do vi tri cua player hien tai tinh theo pixel
	SetVectorh(a, b, deltaTime);
	float j = m_hx;//vector chi huong chuyen dong
	float k = m_hy;
	float cc = vb * (float)j / sqrt(j * j + k * k);
	float d = vb * (float)k / sqrt(j * j + k * k);

	a += cc;//vị trí sau khi di chuyển
	b += d;

	txw = ((float)a / Globals::screenWidth) * 3.0 - 1.5;
	tyw = -(((float)b / Globals::screenHeight) * 3.0 - 1.5);	
	if (j <= 0 && c == 0) { // bat su kien ca quay dau
		countFrame = 0;
		c = 1;
		signal = 1;
	}
	else if (j > 0 && c == 1) {
		countFrame = 0;
		signal = 1;
		c = 0;
	}
	turning();
	zoom();
	bite();
	if (countFrame == 5 && c == 1) {
		curent_texture = texture[1];
		play();
		countFrame = 0;
		signal = 0;
		bite_wait = 0;
		disapear_wait = 0;
	}
	else if (countFrame == 5 && c == 0) {
		curent_texture = texture[0];
		play();
		countFrame = 0;
		signal = 0;
		bite_wait = 0;
		disapear_wait = 0;
	}
}

void Animation2D::turning()
{
	if (signal == 1 && c == 0) {
		curent_texture = texture[3];
		play();
		countFrame = 0;
		signal = 0;
	}
	else if (signal == 1 && c == 1)
	{
		curent_texture = texture[2];
		play();
		countFrame = 0;
		signal = 0;
	}
}

void Animation2D::bite()
{
	if (signal == 3 && c == 0 && bite_wait == 0) {
		curent_texture = texture[4];
		play();
		//countFrame = 0;
		signal = 0;
		bite_wait = 1;
	}
	else if (signal == 3 && c == 1 && bite_wait == 0) {
		curent_texture = texture[5];
		play();
		//countFrame = 0;
		signal = 0;
		bite_wait = 1;
	}
}

void Animation2D::disapear()
{
	sxw = sx;
	syw = sy;
	szw = sz;
	int res = rand() % (4 - 1 + 1) + 1;
	if (res == 1) {
		srand(time(NULL));
		txw = -(rand() % (320 - 300 + 1) + 300) / 100;
		tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100;
	}
	else if (res == 2) {
		txw = (rand() % (320 - 300 + 1) + 300) / 100;
		tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100;
	}
	else if (res == 3) {
		txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100;
		tyw = (rand() % (640 - 300 + 1) + 300) / 100;
	}
	else if (res == 4) {
		txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100;
		tyw = -(rand() % (640 - 300 + 1) + 300) / 100;
	}
	
}

void Animation2D::zoom() {
	if ((sxw >= (sx / 2) || syw >= (sx / 2) || szw >= (sx / 2)) && disapear_wait == 1) {
		sxw -= (sx / 2);
		syw -= (sy / 2);
		szw -= (sz / 2);
	}
	if (sxw < (sx / 2) && disapear_wait == 0) {
		disapear();
	}
}

void Animation2D::follow()
{
}

void Animation2D::avoid()
{
}

float pp = 0;//tinh time doi chuyen dong
void Animation2D::SetVectorh(float a, float b, float deltatime)
{
	if (pp < 5)
	{
		pp += deltatime;
	}
	else {
		pp = 0;
		m_hx = (float)(rand() % 50 - 25);
		m_hy = (float)(rand() % 50 - 25);
	}

	int t;
	if (a < 0) {
		t = 3;
		//cout << 3;
	}
	else if (a > 1360)
	{
		t = 4;
		//cout << 4;
	}
	else if (b > 1170)
	{
		t = 2;
		//cout << 4;
	}
	else if (b < 0)
	{
		t = 1;
		//cout << 1;
	}
	else {
		t = 0;
	}

	switch (t)
	{
	case 1:
	{
		//m_hx = 0;
		m_hy = 1;
		break;
	}
	case 2:
	{
		//m_hx = 0;
		m_hy = -1;
		break;
	}
	case 3:
	{
		m_hx = 1;
		m_hy = 0;
		break;
	}
	case 4:
	{
		m_hx = -1;
		m_hy = 0;
		break;
	}
	default:
		break;
	}
}


bool Animation2D::checkEvent() {
	if (check == 1) {
		check = 0;
		return true;
	}
	return false;
}

void Animation2D::initShape() {
	rect.m_iWidth = frame[4];
	rect.m_iHeight = frame[5];
	rect.m_iX = ((txw + 1.5) * Globals::screenWidth / 3) - (rect.m_iWidth / 2);
	rect.m_iY = ((1.5 - tyw) * Globals::screenHeight / 3) - (rect.m_iHeight / 2);
	cir.m_iX = (txw + 1.5) * Globals::screenWidth / 3;
	cir.m_iY = (1.5 - tyw) * Globals::screenHeight / 3;
	cir.m_iRadius = frame[6];
}

void Animation2D::initCir()
{
	cir.m_iX = (txw + 1.5) * Globals::screenWidth / 3;
	cir.m_iY = (1.5 - tyw) * Globals::screenHeight / 3;
	cir.m_iRadius = 50;
}


