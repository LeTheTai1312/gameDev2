#include "stdafx.h"
#include "Sprite2D.h"
#include "Singleton.h"

//Sprite2D::Sprite2D()
//{
//	//texture.loadTexture2D("../Resources/Textures/spritesheet.png");
//	texture.loadTexture("../Resources/Textures/spritesheet.tga");
//	txw = 0.0; tyw = 0.0; tzw = 0.0;
//	rxw = 0.0; ryw = 0.0; rzw = 0.0;
//	sxw = 1.0; syw = 1.0; szw = 1.0;
//}
//
//Sprite2D::~Sprite2D()
//{
//	glDeleteBuffers(1, &anim->model.vboId);
//	glDeleteBuffers(1, &anim->model.vboId);
//	glDeleteTextures(1, &texture.textureID);
//}
//
//void Sprite2D::Add_animation(const char* fileName)
//{
//	anim = new Animation2D();
//	anim->load_element(fileName);
//	anim->play(texture);
//}
//
//void Sprite2D::Draw() {
//	/*if (anim) {
//		anim->play(texture);
//	}*/
//	camera.set_CamVP();
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	set_matrix(camera.camera_VP);
//	glUseProgram(anim->anim_shader.program);
//	glUniformMatrix4fv(anim->anim_shader.WVP, 1, GL_FALSE, &wvpMatrix.m[0][0]);
//
//	glBindBuffer(GL_ARRAY_BUFFER, anim->model.vboId);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, anim->model.iboId);
//
//	glBindTexture(GL_TEXTURE_2D, texture.textureID);
//	glUniform1i(glGetUniformLocation(anim->anim_shader.program, "u_texture"), 0);
//
//	if (anim->anim_shader.positionAttribute != -1)
//	{
//		glEnableVertexAttribArray(anim->anim_shader.positionAttribute);
//		glVertexAttribPointer(anim->anim_shader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
//	}
//	if (anim->anim_shader.uvAttribute != -1)
//	{
//		glEnableVertexAttribArray(anim->anim_shader.uvAttribute);
//		glVertexAttribPointer(anim->anim_shader.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3)
//			+ sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3));
//	}
//
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//	glDepthMask(GL_TRUE);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//}
//
//void Sprite2D::Update(float deltaTime)
//{
//	anim->anim_cursor += deltaTime;
//	if (anim->anim_cursor > anim->speed) {
//		anim->curent_frame_indx = (anim->curent_frame_indx + 1) % anim->frames_count;
//		anim->anim_cursor = 0;
//	}
//	vector<float> frame = anim->frames[anim->curent_frame_indx];
//
//	//nomalization
//	frame[0] /= texture.width;
//	frame[1] /= texture.height;
//	frame[2] /= texture.width;
//	frame[3] /= texture.height;
//	
//	anim->model.vertices[0].uv.x = frame[0] + frame[2]; anim->model.vertices[0].uv.y = 1 - frame[1];
//	anim->model.vertices[1].uv.x = frame[0] + frame[2]; anim->model.vertices[1].uv.y = 1 - (frame[1] + frame[3]);
//	anim->model.vertices[2].uv.x = frame[0]; anim->model.vertices[2].uv.y = 1 - (frame[1] + frame[3]);
//	anim->model.vertices[3].uv.x = frame[0]; anim->model.vertices[3].uv.y = 1 - frame[1];
//	glBindBuffer(GL_ARRAY_BUFFER, anim->model.vboId);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, anim->model.vertices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}
