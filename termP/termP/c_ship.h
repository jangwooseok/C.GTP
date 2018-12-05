#pragma once
#include "c_background.h"
#include "texture.h"


class c_ship
{
public:
	c_ship();
	~c_ship();

	void update();
	void drawShip();
	void shipModel();
	void init();


	void keybard(unsigned char key);
	void cube(float centerX, float centerY, float centerZ, float height);

public:
	float position[3];
	float moveSpeedZ;
	float moveSpeedX;
	
	c_background* backGround;
	//c_texture* p_Texture;

private:
	const int x = 0;
	const int y = 1;
	const int z = 2;

};

