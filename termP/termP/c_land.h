#pragma once
class c_land
{
public:
	c_land();
	~c_land();

	void init();
	void drawLand();

public:
	int height;
	int position[3];
private:
	const int x = 0;
	const int y = 1;
	const int z = 2;
};

