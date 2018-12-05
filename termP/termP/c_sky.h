#pragma once

#include "texture.h"


class c_sky
{
public:
	c_sky();
	~c_sky();

	void drawSky();
	void textureSetUp();

	c_texture Texture;

public:
	GLuint skyTexture[4];

	GLubyte * TexBits;
	GLubyte *pBytes; // �����͸� ����ų ������
	BITMAPINFO *info; // ��Ʈ�� ��� ������ ��
	BITMAPINFO *texture;
};

