#include "pch.h"
#include "c_ship.h"


c_ship::c_ship()
{
	//backGround = new c_background();
}


c_ship::~c_ship()
{
}

void c_ship::update()
{
	position[y] = backGround->seaPoints[25][25][y];
	position[x] += moveSpeedX;
	position[z] += moveSpeedZ;
}

void c_ship::drawShip()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, shipTexture[0]);

	//p_Texture->set();
	shipModel();
	glDisable(GL_TEXTURE_2D);
}

void c_ship::shipModel()
{

	glPushMatrix();
	{

		glColor3f(1.0, 1.0, 1.0);
		glTranslated(position[x], position[y], position[z]);

		cube(0, 0, 0, 50);

		//glutSolidCube(100);
	}
	glPopMatrix();
}

void c_ship::init()
{
	textureSetUp();
}

void c_ship::keybard(unsigned char key)
{
	switch (key)
	{
	case 'w':
		moveSpeedZ -= 2;
		break;
	case 'a':
		moveSpeedX -= 2;
		break;
	case 's':
		moveSpeedZ += 2;
		break;
	case 'd':
		moveSpeedX += 2;
		break;
	}
}

void c_ship::cube(float centerX, float centerY, float centerZ, float length)
{
	float left		= centerX - length;
	float right		= centerX + length;
	float top		= centerY + length;
	float bottom	= centerY - length;
	float front		= centerZ - length;
	float back		= centerZ + length;


	//glBindTexture(GL_TEXTURE_2D, p_Texture->texture_object[0]);
	//옆면
	for (int i = 0; i < 4; i++)
	{
		glPushMatrix();//=========================
		{
			glRotatef(90 * i, 0, 1, 0);
			glTranslatef(0.0, 0.0, back);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(right, top, 0);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(left, top, 0);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(left, bottom, 0);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(right, bottom, 0);
			}
			glEnd();
		}
		glPopMatrix();//=========================
	}

//	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	//위아래
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();//=========================
		{
			glRotatef(180 * i, 1, 0, 0);
			glTranslatef(0.0, top, 0.0);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(left, 0, front);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(left, 0, back);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(right, 0, back);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(right, 0, front);
			}
			glEnd();
		}
		glPopMatrix();//=========================
	}

}

void c_ship::textureSetUp()
{
	glGenTextures(2, shipTexture);
	glBindTexture(GL_TEXTURE_2D, shipTexture[0]);

	//2차원상의 텍스처 이미지 정의
	TexBits = Texture.LoadDIBitmap("test.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

}
