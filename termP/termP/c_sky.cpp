#include "pch.h"
#include "c_sky.h"


c_sky::c_sky()
{
}


c_sky::~c_sky()
{
}


void c_sky::drawSky()
{

	
	glEnable(GL_TEXTURE_2D);

	float w = 512;
	float h = 256;

	glBindTexture(GL_TEXTURE_2D, skyTexture[0]);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-w / 2, h, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-w / 2, 0.0, 0.0);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(w / 2, 0.0, 0.0);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(w / 2, h, 0.0);
	}
	glEnd();
}



void c_sky::textureSetUp()
{
	glGenTextures(2, skyTexture);
	glBindTexture(GL_TEXTURE_2D, skyTexture[0]);

	//2차원상의 텍스처 이미지 정의
	TexBits = Texture.LoadDIBitmap("resource/test.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glEnable(GL_TEXTURE_2D);

}

