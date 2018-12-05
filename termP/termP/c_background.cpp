#include "pch.h"
#include "c_background.h"


c_background::c_background()
{
}


c_background::~c_background()
{
}

void c_background::drawSea()
{
	glMap2f(GL_MAP2_VERTEX_3,
		0.0, 1.0, 3, UORDER,
		0.0, 1.0, 3*UORDER, VORDER,
		&seaCtrlpoints[0][0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	// 그리드를 이용한 곡면 드로잉
	glMapGrid2f(50, 0.0, 1.0, 50, 0.0, 1.0);
	// 선을 이용하여 그리드 연결 
	glEvalMesh2(GL_LINE, 0, 50, 0, 50);


	for (int i = 0; i < SEA_HEIGHT; i++)
	{
		for (int j = 0; j < SEA_WIDTH; j++)
		{
			glPushMatrix();
			{
				glTranslated(seaPoints[i][j][x], seaPoints[i][j][y], seaPoints[i][j][z]);
				glColor3f(0.0, 0.0, 1.0);
				glutSolidCube(SEA_CUBE_SIZE);
				glColor3f(0.0, 0.0, 0.4);
				glutWireCube(SEA_CUBE_SIZE+2);

			}
			glPopMatrix();
		}
	}


	sky.drawSky();

	//for (int i = 0; i < LAND_AMOUNT; i++)
	//	land[i].drawLand();
}

void c_background::seaUpdate()
{


	for (int i = 0; i < SEA_HEIGHT; i++)
	{
		for (int j = 0; j < SEA_WIDTH; j++)
		{
			waveWid[i][j] += deltaAmplitude;
			waveHei[i][j] += deltaAmplitude;
			//waveWid[i][j] = waveWid[i][j] % (2*PI);

			seaPoints[i][j][y] = amplitude *sin(waveWid[i][j]) + amplitude * sin(waveHei[i][j]);
		}
	}


}

void c_background::init()
{

	//for (int i = 0; i < VORDER; i++)
	//{
	//	for (int j = 0; j < UORDER; j++)
	//	{
	//		seaCtrlpoints[i][j][x] = -SEASIZE + 0.5 * SEASIZE * j;
	//		seaCtrlpoints[i][j][z] = SEASIZE - 0.5 * SEASIZE * i;
	//		is_seaUp[i][j] = rand() % 2;
	//		waveSpeed[i][j] = rand() % 5 + 1;
	//		glPushMatrix();
	//		{
	//			seaCtrlpoints[i][j][y]++;
	//		}
	//		glPopMatrix();
	//	}
	//}

	for (int i = 0; i < LAND_AMOUNT; i++)
	{
		land[i].init();
	}

	for (int i = 0; i < SEA_HEIGHT; i++)
	{
		for (int j = 0; j < SEA_WIDTH; j++)
		{
			seaPoints[i][j][x] = SEA_CUBE_SIZE * j - SEA_CUBE_SIZE * SEA_WIDTH/2;
			seaPoints[i][j][z] = SEA_CUBE_SIZE * i - SEA_CUBE_SIZE * SEA_HEIGHT/2;
			waveWid[i][j] = 0.02 * PI * i;
			waveHei[i][j] = 0.01 * PI * j;
			seaPoints[i][j][y] = amplitude * sin(waveWid[i][j]) + amplitude * sin(waveHei[i][j]);
		}
	}


	sky.textureSetUp();
}

void c_background::cube(float centerX, float centerY, float centerZ, float length)
{
	float left = centerX - length;
	float right = centerX + length;
	float top = centerY + length;
	float bottom = centerY - length;
	float front = centerZ - length;
	float back = centerZ + length;


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