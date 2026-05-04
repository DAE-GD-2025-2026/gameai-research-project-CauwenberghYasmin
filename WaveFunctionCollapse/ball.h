#pragma once
#include"raylib.h"

class ball
{
public:
	ball(int posX, int posY, float radius, Color color) noexcept;
	void SetPos(int posX, int posY); 
	void SetColor(Color newColor);

	void Update(float elapsedSec);


private:

	int m_PosX;
	int m_PosY;
	float m_Radius;
	Color m_CurrentColor;

	float m_Velocity;
};

