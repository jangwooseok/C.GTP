#pragma once

#include "c_land.h"
#include "c_sky.h"
#include "texture.h"

#define VORDER 5
#define UORDER 5

#define SEA_WIDTH 50
#define SEA_HEIGHT 50
#define SEA_CUBE_SIZE 20

#define SEASIZE 400.0
#define SEASIZE 400.0

#define LAND_AMOUNT 10


class c_background
{
public:
	c_background();
	~c_background();
	
	void init();

	void drawSea();
	void seaUpdate();
	void cube(float centerX, float centerY, float centerZ, float length);

public:
	//왼쪽 위 에서 오른쪽 아래로
	GLfloat seaCtrlpoints[VORDER][UORDER][3];

	bool is_seaUp[VORDER][UORDER];
	float waveSpeed[VORDER][UORDER];


	float seaPoints[SEA_HEIGHT][SEA_WIDTH][3];
	float wavespeed[SEA_HEIGHT][SEA_WIDTH][3];

	float waveWid[SEA_HEIGHT][SEA_WIDTH];
	float waveHei[SEA_HEIGHT][SEA_WIDTH];

	int amplitude = 9;//진폭
	float deltaAmplitude = 0.09*PI;

	c_texture backgroundTexture;
	
	c_land land[LAND_AMOUNT][5];
	c_sky sky;

	GLubyte * TexBits;
	GLubyte *pBytes; // 데이터를 가리킬 포인터
	BITMAPINFO *info; // 비트맵 헤더 저장할 변
	BITMAPINFO *texture;


private:
	const int x = 0;
	const int y = 1;
	const int z = 2;

	//const float seaSize = 1000.0;
};

