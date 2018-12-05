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
	//p_Texture->set();
	shipModel();
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
	//¿·¸é
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
	//À§¾Æ·¡
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