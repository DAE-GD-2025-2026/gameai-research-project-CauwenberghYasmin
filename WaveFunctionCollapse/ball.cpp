#include "ball.h"
#include "raylib.h"

ball::ball(int posX, int posY, float radius, Color color) :
	m_PosX{ posX },
	m_PosY{ posY },
	m_Radius{radius},
	m_CurrentColor{color},
	m_Velocity{0}
{
}


void ball::SetPos(int posX, int posY)
{
	m_PosX = posX;
	m_PosY = posY;
}

void ball::SetColor(Color newColor)
{
	m_CurrentColor = newColor;
}

void ball::Update(float elapsedSec)
{
	//basic gravity

	m_PosY -= 
}