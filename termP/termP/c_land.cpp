#include "pch.h"
#include "c_land.h"


c_land::c_land()
{
}


c_land::~c_land()
{
}

void c_land::init()
{
	height = rand() % 100 + 100;
	//position[x] = rand() % 50 * 20 - 500;
	//position[z] = rand() % 50 * 20 - 500;

	position[x] = 0;
	position[z] = 0;
}

void c_land::drawLand()
{
	int length = 20;
	float left = position[x] - length;
	float right = position[x] + length;
	float top = position[y] + height;
	float bottom = 0.0;
	float front = position[z] - length;
	float back = position[z] + length;

	glColor3f(0.5, 0.3, 0.1);
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
	//À§
	glPushMatrix();//=========================
	{
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