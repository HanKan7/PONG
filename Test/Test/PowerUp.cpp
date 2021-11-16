#include "PowerUp.h"

PowerUp::PowerUp() 
{
	radius = 40.f;
	color = sf::Color::White;
	ball.setRadius(radius);
	ball.setFillColor(color);
}

void PowerUp::SpawnPowerUp() 
{
	srand(time(0));
	int YValue = rand() % 100 + 200;
	int xValue = rand() % 200 + 200;
	ball.setPosition(xValue, YValue);
}
void PowerUp::Init(Paddle* leftPaddle, Paddle* rightPaddle) 
{
	this->leftPaddle = leftPaddle;
	this->rightPaddle = rightPaddle;
	radius = 20.f;
	color = sf::Color::White;
	ball.setRadius(radius);
	ball.setFillColor(color);
}